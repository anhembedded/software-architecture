# Linux Performance Bottlenecks: Diagnosis & Debugging

## Overview

A **bottleneck** is a resource constraint that limits overall system performance. In Linux systems, bottlenecks can occur at multiple layers—hardware, kernel, application—and require systematic diagnosis using appropriate tools and methodologies.

Diagnosis follows a structured approach:
1. **Observe** system behavior (monitoring)
2. **Identify** the constrained resource (bottleneck detection)
3. **Analyze** root cause (profiling/tracing)
4. **Resolve** or mitigate (tuning/fixing)

```mermaid
mindmap
  root((Linux Bottlenecks))
    CPU
      High utilization
      Run queue length
      Context switching
      Cache misses
    Memory
      RAM exhaustion
      Swap thrashing
      Page faults
      OOM killer
    Disk I/O
      High iowait
      Queue depth
      Throughput saturation
      Fragmentation
    Network
      Bandwidth saturation
      Packet loss
      Connection backlog
      Socket buffer overflow
    Application
      Lock contention
      Memory leaks
      Inefficient algorithms
      Blocking syscalls
```

---

## What is a Bottleneck?
A bottleneck occurs when a **resource reaches its capacity limit**, causing requests to queue up and response times to increase. It's the **slowest component** in a pipeline that determines overall throughput.

**Key insight:** Optimizing a non-bottleneck resource yields **zero performance improvement**. You must find and address the actual constraint.

```mermaid
flowchart LR
    A[Request] --> B[CPU]
    B --> C[Memory]
    C --> D[Disk I/O]
    D --> E[Network]
    E --> F[Response]
    
    D -.- G((Bottleneck!<br/>High iowait))
    
    style D fill:#ff6b6b,stroke:#c92a2a,color:#fff
    style G fill:#fff,stroke:#ff6b6b,color:#c92a2a
```

---

## How Diagnosis Works: The Mechanism

### 1. The Diagnostic Methodology

```mermaid
sequenceDiagram
    participant Admin
    participant Monitoring Tools
    participant Kernel
    participant Application
    
    Admin->>Monitoring Tools: Observe system metrics
    Monitoring Tools->>Kernel: Read /proc, /sys, tracepoints
    Kernel->>Monitoring Tools: Return counters, stats
    
    Note over Admin: USE Method check<br/>(Utilization, Saturation, Errors)
    
    alt High CPU Utilization
        Admin->>Application: perf top / flamegraph
        Application->>Admin: Hot functions identified
    else High Memory Pressure
        Admin->>Kernel: Check /proc/meminfo, slabtop
        Kernel->>Admin: Memory breakdown
    else High I/O Wait
        Admin->>Kernel: iostat, iotop, blktrace
        Kernel->>Admin: Disk latency, queue depth
    else Network Bottleneck
        Admin->>Kernel: ss, netstat, tcpdump
        Kernel->>Admin: Connection stats, drops
    end
    
    Admin->>Application: Deep dive with tracing (strace, bpftrace)
    Application->>Admin: Syscall patterns, latency breakdown
    Admin->>Admin: Identify root cause
    Admin->>Application: Apply fix or tuning
```

### 2. The USE Method (Utilization, Saturation, Errors)

```mermaid
stateDiagram-v2
    [*] --> Check_Utilization: For each resource
    Check_Utilization --> Check_Saturation
    Check_Saturation --> Check_Errors
    
    Check_Utilization --> High_Util: >80% utilized
    Check_Saturation --> Queue_Building: Queue/backlog growing
    Check_Errors --> Errors_Found: Error count increasing
    
    High_Util --> Investigate: Possible bottleneck
    Queue_Building --> Investigate: Definite bottleneck
    Errors_Found --> Investigate: Fault investigation
    
    Investigate --> Resource_Identified
    Resource_Identified --> Apply_Fix
    Apply_Fix --> [*]
    
    Check_Errors --> All_Clear: No issues
    All_Clear --> [*]: Continue monitoring
```

---

## Diagnostic Tools by Layer

```mermaid
graph TD
    subgraph "Application Layer"
        A1[strace - Syscall tracing]
        A2[ltrace - Library call tracing]
        A3[gdb - Debugger]
        A4[valgrind - Memory profiler]
        A5[perf record - CPU sampling]
    end
    
    subgraph "Kernel Layer"
        K1[ftrace - Function tracer]
        K2[bpftrace - Dynamic tracing]
        K3[eBPF - Programmable tracing]
        K4[SystemTap - Kernel probing]
    end
    
    subgraph "System Layer"
        S1[top/htop - Process monitor]
        S2[vmstat - Virtual memory stats]
        S3[iostat - I/O statistics]
        S4[sar - System activity reporter]
        S5[dstat - Versatile stats]
    end
    
    subgraph "Network Layer"
        N1[ss/netstat - Socket stats]
        N2[tcpdump - Packet capture]
        N3[iperf3 - Bandwidth test]
        N4[ping/traceroute - Connectivity]
    end
    
    A1 --> A2 --> A3 --> A4 --> A5
    K1 --> K2 --> K3 --> K4
    S1 --> S2 --> S3 --> S4 --> S5
    N1 --> N2 --> N3 --> N4
```

---

## Similar Mechanisms (Same Level of Abstraction)

Diagnosis and debugging in Linux share the same **observability and introspection** level with these mechanisms:

```mermaid
graph TD
    O[System Observability]
    O --> B[Performance Diagnosis]
    O --> C[Crash Debugging]
    O --> D[Security Auditing]
    O --> E[Capacity Planning]
    
    B --> B1["Bottleneck detection<br/>Profiling & tracing<br/>USE/RED methods"]
    C --> C1["Core dumps<br/>Kdump/Kexec<br/>Live debugging with gdb"]
    D --> D1["Audit subsystem<br/>SELinux alerts<br/>System call filtering"]
    E --> E1["Trending metrics<br/>Load forecasting<br/>Resource modeling"]
```

### Comparison Table

| Mechanism | Primary Goal | Key Tools | Data Source | Analysis Type |
|-----------|-------------|-----------|-------------|---------------|
| **Performance Diagnosis** | Find bottlenecks | `perf`, `bcc/bpftrace`, `iostat` | Counters, tracepoints | Real-time, historical |
| **Crash Debugging** | Root cause of failure | `gdb`, `crash`, `kdump` | Core dumps, vmcore | Post-mortem |
| **Security Auditing** | Detect intrusions | `auditd`, `osquery`, `falco` | Audit logs, syscalls | Policy-based, real-time |
| **Capacity Planning** | Predict resource needs | `prometheus`, `grafana`, `sar` | Time-series metrics | Trend analysis |
| **Application Debugging** | Fix logic errors | `gdb`, `strace`, `valgrind` | Process state, memory | Interactive |
| **Tracing/Profiling** | Understand execution flow | `bpftrace`, `perf`, `LTTng` | Events, stack traces | Dynamic, low-overhead |

---

## Step-by-Step Debugging Guide

### Common Bottleneck Debugging Steps

```mermaid
flowchart TD
    START([Performance Issue Reported]) --> CHECK{What is slow?}
    
    CHECK -->|High CPU| CPU[CPU Investigation]
    CHECK -->|High Memory| MEM[Memory Investigation]
    CHECK -->|Slow I/O| IO[I/O Investigation]
    CHECK -->|Network Issues| NET[Network Investigation]
    
    CPU --> CPU1[1. top: Check CPU utilization]
    CPU1 --> CPU2{CPU > 80%?}
    CPU2 -->|Yes| CPU3[2. perf top: Find hot functions]
    CPU2 -->|No| CPU4[Check run queue length]
    CPU3 --> CPU5[3. Flamegraph: Visualize callstack]
    CPU4 --> CPU6[4. mpstat: Check per-CPU distribution]
    CPU5 --> CPU7[5. Fix: Optimize code or add CPUs]
    CPU6 --> CPU7
    
    MEM --> MEM1[1. free -h: Check memory usage]
    MEM1 --> MEM2{Swap used > 0?}
    MEM2 -->|Yes| MEM3[2. vmstat 1: Watch si/so columns]
    MEM2 -->|No| MEM4[3. smem/ps: Find memory hogs]
    MEM3 --> MEM5[System thrashing!]
    MEM5 --> MEM6[4. Identify leaking process]
    MEM4 --> MEM7[5. Check /proc/meminfo for details]
    MEM6 --> MEM8[6. Fix: Kill/restart, increase RAM, fix leak]
    MEM7 --> MEM8
    
    IO --> IO1[1. iostat -x 1: Check %util, await]
    IO1 --> IO2{await > 10ms?}
    IO2 -->|Yes| IO3[2. iotop: Find heavy I/O process]
    IO2 -->|No| IO4[3. Check filesystem/block layer]
    IO3 --> IO5[4. strace -p PID: See syscall pattern]
    IO4 --> IO6[5. blktrace: Block-level analysis]
    IO5 --> IO7[6. Fix: Optimize queries, add cache, faster disk]
    IO6 --> IO7
    
    NET --> NET1[1. ss -s: Socket statistics]
    NET1 --> NET2[2. nload/iftop: Bandwidth usage]
    NET2 --> NET3{Retransmissions?}
    NET3 -->|Yes| NET4[3. ss -ti: TCP detail with retrans]
    NET3 -->|No| NET5[4. Check application logs]
    NET4 --> NET6[5. tcpdump: Capture and analyze]
    NET5 --> NET7[6. Fix: NIC, kernel params, app config]
    NET6 --> NET7
    
    CPU7 --> RESOLVE([Issue Resolved])
    MEM8 --> RESOLVE
    IO7 --> RESOLVE
    NET7 --> RESOLVE
```

---

## Key Diagnostic Commands Quick Reference

### CPU Bottleneck
```bash
# Check overall CPU usage
top -bn1 | head -20

# Per-CPU usage
mpstat -P ALL 1

# Find hot functions (sampling profiler)
perf top -g

# Generate flamegraph
perf record -F 99 -g -p <PID> -- sleep 30
perf script | FlameGraph/stackcollapse-perf.pl | FlameGraph/flamegraph.pl > flame.svg

# Check run queue / load average
uptime
cat /proc/loadavg

# Context switching rate
vmstat 1 5
```

### Memory Bottleneck
```bash
# Memory overview
free -h

# Memory pressure stats
cat /proc/pressure/memory

# Detailed memory info
cat /proc/meminfo

# Top memory consumers (RSS)
ps aux --sort=-%mem | head -10

# Slab memory (kernel objects)
slabtop -o

# Check for swapping
vmstat 1
# Watch si (swap in) and so (swap out) columns

# OOM killer history
dmesg | grep -i "out of memory"
```

### I/O Bottleneck
```bash
# Disk utilization and latency
iostat -x 1

# Per-process I/O
iotop -o

# Files opened by process
lsof -p <PID>

# Trace syscalls with timing
strace -c -p <PID>  # Summary
strace -T -p <PID>  # With timestamps

# Block layer tracing
btrace /dev/sda

# Check I/O pressure
cat /proc/pressure/io
```

### Network Bottleneck
```bash
# Socket statistics
ss -s
ss -tlnp  # Listening TCP sockets
ss -tan state time-wait | wc -l  # Count TIME_WAIT

# TCP retransmissions
ss -ti

# Bandwidth per process
nethogs eth0

# Packet capture
tcpdump -i eth0 -nn -c 1000 -w capture.pcap

# Network errors
netstat -i
ip -s link show
```

---

## Code Example: Programmatic Bottleneck Detection

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct {
    double cpu_util;
    long mem_free_mb;
    double load_1min;
    int io_wait_pct;
} SystemHealth;

SystemHealth get_system_health() {
    SystemHealth health = {0};
    FILE *fp;
    char line[256];
    
    // Read load average
    fp = fopen("/proc/loadavg", "r");
    if (fp) {
        fscanf(fp, "%lf", &health.load_1min);
        fclose(fp);
    }
    
    // Read memory info
    fp = fopen("/proc/meminfo", "r");
    if (fp) {
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "MemAvailable:", 13) == 0) {
                sscanf(line + 14, "%ld", &health.mem_free_mb);
                health.mem_free_mb /= 1024;  // Convert kB to MB
                break;
            }
        }
        fclose(fp);
    }
    
    // Read CPU stats (simplified)
    fp = fopen("/proc/stat", "r");
    if (fp) {
        long user, nice, system, idle, iowait;
        fgets(line, sizeof(line), fp);
        sscanf(line, "cpu %ld %ld %ld %ld %ld", 
               &user, &nice, &system, &idle, &iowait);
        long total = user + nice + system + idle + iowait;
        health.cpu_util = 100.0 * (total - idle) / total;
        health.io_wait_pct = (int)(100.0 * iowait / total);
        fclose(fp);
    }
    
    return health;
}

void diagnose_bottleneck(SystemHealth h) {
    printf("\n=== System Health Diagnostic ===\n");
    printf("Load Average (1min): %.2f\n", h.load_1min);
    printf("CPU Utilization:    %.1f%%\n", h.cpu_util);
    printf("I/O Wait:           %d%%\n", h.io_wait_pct);
    printf("Available Memory:   %ld MB\n", h.mem_free_mb);
    
    printf("\n=== Bottleneck Analysis ===\n");
    
    if (h.io_wait_pct > 20) {
        printf("⚠️  I/O BOTTLENECK: High iowait (%d%%)\n", h.io_wait_pct);
        printf("   → Check: iostat -x 1, iotop\n");
    }
    
    if (h.cpu_util > 90 && h.io_wait_pct < 10) {
        printf("⚠️  CPU BOTTLENECK: High utilization (%.1f%%)\n", h.cpu_util);
        printf("   → Check: perf top, mpstat -P ALL\n");
    }
    
    if (h.mem_free_mb < 512) {
        printf("⚠️  MEMORY PRESSURE: Low available memory (%ld MB)\n", 
               h.mem_free_mb);
        printf("   → Check: ps aux --sort=-%mem, vmstat 1\n");
    }
    
    int cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
    if (h.load_1min > cpu_count * 1.5) {
        printf("⚠️  CPU SATURATION: Load (%.2f) exceeds CPU cores (%d)\n", 
               h.load_1min, cpu_count);
        printf("   → Check: vmstat 1 (watch 'r' column)\n");
    }
    
    if (h.io_wait_pct < 10 && h.cpu_util < 70 && h.mem_free_mb > 1024) {
        printf("✅ No obvious resource bottleneck detected.\n");
        printf("   → Consider application-level profiling: strace, perf\n");
    }
    
    printf("===============================\n");
}

int main() {
    printf("System Bottleneck Detector\n");
    printf("Collecting system health...\n");
    sleep(1);
    
    SystemHealth health = get_system_health();
    diagnose_bottleneck(health);
    
    return 0;
}
```

**Compile and run:**
```bash
gcc -o bottleneck_detect bottleneck_detect.c
./bottleneck_detect
```

---

## Important Notes

| Concept | Description |
|---------|-------------|
| **USE Method** | Check Utilization, Saturation, Errors for every resource |
| **RED Method** | Rate, Errors, Duration (for services/endpoints) |
| **90th Percentile** | Focus on P90/P99 latency, not averages |
| **The Tuning Cycle** | Monitor → Analyze → Tune → Monitor again |
| **eBPF Revolution** | Modern tracing without kernel modules (bpftrace, Cilium) |
| **Overhead Awareness** | Tracing tools have overhead; production-safe: perf, eBPF |
| **Baseline First** | Always establish normal metrics before troubleshooting |

### The Linux Observability Stack

```mermaid
graph TB
    subgraph "Data Sources"
        DS1[proc filesystem]
        DS2[sys filesystem]
        DS3[Tracepoints]
        DS4[kprobes/uprobes]
        DS5[perf events]
    end
    
    subgraph "Collection"
        C1[Monitoring Agents<br/>node_exporter, telegraf]
        C2[Tracing Tools<br/>bpftrace, perf]
        C3[Logging<br/>journald, rsyslog]
    end
    
    subgraph "Storage & Visualization"
        V1[Prometheus / InfluxDB]
        V2[Grafana Dashboards]
        V3[FlameGraph / FlameScope]
    end
    
    DS1 --> C1
    DS2 --> C1
    DS3 --> C2
    DS4 --> C2
    DS5 --> C2
    
    C1 --> V1
    C2 --> V3
    C3 --> V2
    
    V1 --> V2
```

---

## Related Notes
- [[Linux Signals]]
- [[Process Lifecycle]]
- [[Kernel Tracing with eBPF]]
- [[Linux Memory Management]]
- [[I/O Scheduler and Block Layer]]
- [[TCP Tuning and Network Stack]]
- [[Flame Graphs and Visualization]]

---

This note covers the systematic approach to identifying, diagnosing, and resolving Linux performance bottlenecks, with a focus on practical tools and step-by-step debugging flows using structured methodologies like USE and RED.