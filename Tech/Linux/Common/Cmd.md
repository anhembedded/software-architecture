# CMD

## 1. `uptime`
**Name meaning:** *“up time”* → how long the system has been up.  
**Description:** Shows system running time, logged-in users, and load average.  
**Options:** None. Just run `uptime`.

---

## 2. `top -bn1 | head -5`
**Name meaning:** *“table of processes”* → shows the “top” resource consumers.  
**Description:** Monitors processes and resources in real time.  
**Options:**  
- `-b` → batch mode (non-interactive).  
- `-n1` → run once.  
- `head -5` → show first 5 lines (summary only).

---

## 3. `mpstat -P ALL 1 5`
**Name meaning:** *“multiprocessor statistics”*.  
**Description:** Reports CPU usage per processor/core.  
**Options:**  
- `-P ALL` → show all cores.  
- `1` → interval in seconds.  
- `5` → number of samples.

---

## 4. `vmstat 1 5`
**Name meaning:** *“virtual memory statistics”*.  
**Description:** Displays CPU, memory, I/O, and swap activity.  
**Options:**  
- `1` → interval in seconds.  
- `5` → number of samples.  
**Key columns:**  
- `r` (run queue), `us` (user CPU), `sy` (system CPU), `id` (idle), `wa` (I/O wait).

---

## 5. `ps aux --sort=-%cpu | head -15`
**Name meaning:** *“process status”*.  
**Description:** Lists all processes with details.  
**Options:**  
- `a` → all users.  
- `u` → user-oriented format.  
- `x` → include processes without a terminal.  
- `--sort=-%cpu` → sort by CPU usage descending.  
- `head -15` → show top 15 processes.

---

## 6. `pidstat 1 5`
**Name meaning:** *“process ID statistics”*.  
**Description:** Monitors CPU usage per process over time.  
**Options:**  
- `1` → interval in seconds.  
- `5` → number of samples.

---

## 7. `pidstat -t -p <PID> 1 5`
**Name meaning:** *“process ID statistics” with threads*.  
**Description:** Monitors CPU usage for a specific process and its threads.  
**Options:**  
- `-p <PID>` → target process ID.  
- `-t` → include threads.  
- `1` → interval in seconds.  
- `5` → number of samples.

---

## Using `perf top -g -p <PID>` to Detect Bottlenecks

## 1. Introduction

`perf` is a powerful Linux profiling tool that leverages hardware performance counters.  
The command `perf top -g -p <PID>` allows you to:

- Attach to a specific process (`-p <PID>`).
- Collect live performance data.
- Display **functions consuming CPU cycles**.
- Show **call graphs** (`-g`) to understand the context of hot functions.

---

## 2. Prerequisites

- Linux system with `perf` installed (`sudo apt install linux-tools-common linux-tools-$(uname -r)` on Ubuntu).
- Root privileges (`sudo`) to access performance counters.
- The PID of the target process (find with `ps aux | grep <program>`).

---

## 3. Command Breakdown

```bash
sudo perf top -g -p 12345
```

- **`sudo`** → required for hardware counter access.
- **`perf top`** → interactive profiler (like `top`, but for functions).
- **`-g`** → enable call graph (stack trace).
- **`-p 12345`** → attach to process with PID 12345.

---

## 4. Step-by-Step Usage

### Step 1: Identify the process

```bash
ps aux | grep myapp
```

→ Note the PID (e.g., 12345).

### Step 2: Run perf

```bash
sudo perf top -g -p 12345
```

### Step 3: Interpret the output

You’ll see a live ncurses interface with columns like:

- **Samples%** → percentage of CPU samples attributed to a function.
- **Function name** → the symbol consuming CPU.
- **Shared object** → binary/library where the function resides.
- **Call graph (with `-g`)** → shows the chain of calls leading to the hot function.

Example (simplified):

```
Samples%  Function
  35.00%  memcpy
   └─ main → process_data → memcpy
  20.00%  read
   └─ main → load_file → read
```

---

## 5. Detecting Bottlenecks

- **High Samples% in user functions** → CPU bottleneck in your code.
- **High Samples% in kernel functions (e.g., `sys_read`, `schedule`)** → bottleneck in system calls or I/O.
- **Call graph analysis** → shows _why_ a function is hot (which caller leads to it).

👉 Example: If `memcpy` is 35% of samples, and the call graph shows it’s called repeatedly in `process_data`, then optimization should focus on reducing memory copies.

---

## 6. Tips & Best Practices

- Use `perf record -g -p <PID>` + `perf report` for offline analysis (longer profiling).
- Combine with `top`, `iotop`, `vmstat` to distinguish CPU vs I/O bottlenecks.
- If symbols are missing, install debug symbols (`apt install libc6-dbg` etc.).
- Narrow scope with `-p` to avoid noise from other processes.

---

## 7. Summary

- `perf top -g -p <PID>` = live profiler for one process.
- Shows **which functions consume CPU** and their **call graphs**.
- Helps distinguish **CPU bottlenecks** (hot functions) vs **I/O bottlenecks** (kernel waits).
- Use call graph output to trace back to the root cause in your code.