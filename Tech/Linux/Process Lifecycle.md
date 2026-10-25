# Process Lifecycle

## Overview
The **process lifecycle** describes the complete journey of a process from its creation to its termination in a Linux system. The kernel manages processes through distinct states, transitions, and metadata structures (Process Control Block - PCB).

A process is **more than just a running program**—it encompasses:
- Executable code (text segment)
- Memory space (stack, heap, data)
- System resources (file descriptors, sockets)
- Execution context (registers, program counter)
- Scheduling attributes (priority, CPU time)

```mermaid
mindmap
  root((Process Lifecycle))
    Creation
      fork() - Clone current process
      execve() - Replace process image
      clone() - Shared resources
    Scheduling
      Ready - Waiting for CPU
      Running - On CPU
      Waiting - Blocked on I/O
    Termination
      Normal exit - exit()
      Abnormal - Signal/Exception
      Zombie - Awaiting wait()
      Orphan - Adopted by init
```

---

## What is a Process?
A process is an **instance of a program in execution**. It's the fundamental unit of work in a Linux system, identified by a unique **PID (Process ID)**.

The kernel represents each process using a **task_struct** (Process Control Block) containing:
- Process state
- PID and parent PID
- Memory mappings
- File descriptor table
- Signal information
- Scheduling parameters

---

## How the Process Lifecycle Works: The Mechanism

### 1. Process States

```mermaid
stateDiagram-v2
    [*] --> Created: fork() / clone()
    Created --> Ready: Admitted to scheduler
    Ready --> Running: Scheduler dispatches
    Running --> Ready: Time slice expired
    Running --> Waiting: Block on I/O / event
    Waiting --> Ready: I/O complete / event occurs
    Running --> Terminated: exit() / signal / exception
    Terminated --> Zombie: wait() not yet called
    Zombie --> [*]: wait() by parent<br/>(process reaped)
    
    note right of Created
        Process allocated PID
        task_struct created
        Waiting for admission
    end note
    
    note right of Zombie
        Process exited but
        parent hasn't wait()'d
        PCB partially retained
    end note
```

### 2. Complete Lifecycle Flow

```mermaid
sequenceDiagram
    participant Parent
    participant Kernel
    participant New Process
    participant Scheduler
    participant Resource

    Parent->>Kernel: fork() syscall
    Kernel->>Kernel: Create task_struct
    Kernel->>Kernel: Copy parent's address space (COW)
    Kernel->>New Process: Assign new PID
    Kernel->>Parent: Return child PID
    Kernel->>New Process: Return 0 (child knows it's child)
    
    Note over New Process: State: READY
    
    alt execve() called
        New Process->>Kernel: execve("/bin/program", ...)
        Kernel->>New Process: Replace memory image
        Kernel->>New Process: Reset signal handlers
        Kernel->>New Process: Keep same PID, FD table
    end
    
    Scheduler->>New Process: Dispatch to CPU
    Note over New Process: State: RUNNING
    
    New Process->>Resource: read() - Request I/O
    Note over New Process: State: WAITING
    Resource->>Kernel: I/O complete interrupt
    Note over New Process: State: READY
    
    Scheduler->>New Process: Dispatch again
    New Process->>Kernel: exit(0)
    Note over New Process: State: ZOMBIE
    
    Parent->>Kernel: waitpid(child_pid, ...)
    Kernel->>New Process: Reap process (free PCB)
    Note over New Process: Process removed
```

### 3. The Fork-Exec Mechanism

---

## Similar Abstraction Mechanisms (Same Level)

The process lifecycle shares the same **entity management** abstraction level with these mechanisms:

```mermaid
graph TD
    A[Entity Lifecycle Management]
    A --> B[Process Lifecycle]
    A --> C[Thread Lifecycle]
    A --> D[Container Lifecycle]
    A --> E[Service/Unit Lifecycle]
    
    B --> B1["Heavyweight<br/>Own address space<br/>fork-exec paradigm"]
    C --> C1["Lightweight<br/>Shared address space<br/>pthread_create"]
    D --> D1["OS-level virtualization<br/>Namespaces + cgroups<br/>OCI runtime spec"]
    E --> E1["systemd units<br/>Dependencies<br/>Socket activation"]
```

### Comparison Table

| Mechanism | Isolation Level | Creation Cost | Address Space | Linux Primitive |
|-----------|----------------|---------------|---------------|-----------------|
| **Process** | Full (own memory, FDs) | High (fork + COW) | Independent | `fork()` + `execve()` |
| **Thread** | Partial (shared memory) | Low | Shared | `clone()` with `CLONE_THREAD` |
| **Container** | Namespace-level | Medium | Independent | `clone()` + namespaces |
| **vCPU (KVM)** | Hardware VM | Very High | Hypervisor-managed | `KVM_CREATE_VCPU` |
| **Task (kernel)** | Kernel space | Very Low | Kernel address space | `kthread_create()` |
| **systemd Service** | Process group | Medium (exec) | Per-process | `fork()` + cgroups |

### Key Differences from Threads

```mermaid
graph LR
    subgraph "Process (Heavyweight)"
        P1[Text Segment]
        P2[Data Segment]
        P3[Stack]
        P4[File Descriptors]
    end
    
    subgraph "Threads (Lightweight)"
        T1[Shared Text]
        T2[Shared Data]
        T3[Thread 1 Stack]
        T4[Thread 2 Stack]
        T5[Thread 3 Stack]
        T6[Shared FDs]
    end
    
    P1 -.- T1
    P2 -.- T2
    P3 -.- T3
    P4 -.- T6
```

---

## Code Example: Full Lifecycle Demonstration

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void print_state(const char *state) {
    printf("[PID %d] State: %s\n", getpid(), state);
}

int main() {
    pid_t pid;
    int status;
    
    print_state("RUNNING - Parent starting");
    
    pid = fork();  // Child created → READY
    
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }
    
    if (pid == 0) {
        // ===== CHILD PROCESS =====
        print_state("READY → RUNNING - Child executing");
        
        // Simulate work
        sleep(2);
        
        print_state("WAITING - Child sleeping (blocked on I/O)");
        printf("Child doing work...\n");
        
        print_state("RUNNING - Child completing");
        
        // Replace with new program? No, just exit
        exit(42);  // Child → ZOMBIE
        
    } else {
        // ===== PARENT PROCESS =====
        printf("Parent: Child PID is %d\n", pid);
        
        // Child is RUNNING/WAITING/ZOMBIE during this time
        sleep(1);
        printf("Parent: Waiting for child...\n");
        
        // wait() reaps zombie child
        pid_t waited = waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Parent: Child %d exited with status %d\n",
                   waited, WEXITSTATUS(status));
        }
        
        printf("Parent: Child reaped → Process removed from system\n");
    }
    
    return 0;
}
```

**Output trace:**
```
[PID 1234] State: RUNNING - Parent starting
Parent: Child PID is 1235
[PID 1235] State: READY → RUNNING - Child executing
[PID 1235] State: WAITING - Child sleeping (blocked on I/O)
Parent: Waiting for child...
Child doing work...
[PID 1235] State: RUNNING - Child completing
Parent: Child 1235 exited with status 42
Parent: Child reaped → Process removed from system
```

---

## Important Notes

| Concept | Description |
|---------|-------------|
| **Copy-On-Write (COW)** | fork() doesn't immediately copy memory; pages shared until modified |
| **Zombie Prevention** | Parent must `wait()` to reap children; otherwise zombies accumulate |
| **Orphan Processes** | If parent dies first, child reparented to `init` (PID 1) |
| **execve() Preservation** | PID, FD table, process group, and signal mask survive exec |
| **vfork() Legacy** | Historic variant; parent blocked until child exec'd/exited (avoid) |
| **Process Groups** | Related processes grouped for job control (shell pipelines) |
| **Daemonization** | Double-fork pattern to detach from terminal and session |

### Zombie vs Orphan States

```mermaid
flowchart LR
    A[Parent alive?] -->|Yes| B[wait() called?]
    A -->|No| C[Orphan Process]
    B -->|Yes| D[Clean termination]
    B -->|No| E[Zombie Process]
    C --> F[Adopted by init/PID 1]
    F --> G[init calls wait()]
    G --> D
    E --> H[wait() eventually called]
    H --> D
```

---

## Related Notes
- [[Linux Signals]]
- [[Kernel Process Scheduler]]
- [[Copy-On-Write Mechanism]]
- [[Thread vs Process]]
- [[Daemon Processes]]
- [[PID Namespaces]]
- [[Process Memory Layout]]
- [[Process State]]

---

This note covers the complete lifecycle of a Linux process, from creation through scheduling to termination, with the kernel's role visualized through state machines and sequence diagrams.