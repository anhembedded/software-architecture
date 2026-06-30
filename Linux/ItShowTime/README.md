# Profiling Demo Project

This C CMake project builds two separate executables to demonstrate different kinds of CPU saturation scenarios on Linux:
1. `perf_demo_user`: For demonstrating **User-Mode Saturation** (High `%usr`).
2. `perf_demo_sys`: For demonstrating **Kernel-Mode Saturation** (High `%sys`).

Both executables are compiled with debug symbols (`-g`) and frame pointer preservation (`-fno-omit-frame-pointer`) so that `perf` can accurately construct call stacks.

---

## How to Build

Compile both targets using CMake:

```bash
# Generate build configuration and compile the executables
cmake -B build -S .
cmake --build build
```

This will generate two binaries under the `build/` directory: `perf_demo_user` and `perf_demo_sys`.

---

## Scenario A: User-Mode CPU Saturation (High %usr)

The application spends the majority of its time executing code inside user space (e.g., recursive operations, matrix multiplication, sorting, hashing).

### 1. Run User-Mode Saturation Target
```bash
./build/perf_demo_user
```

### 2. Identify the Hot Process
```bash
ps aux --sort=-%cpu | head -5
```

### 3. Check Live Real-time Call Graph
```bash
sudo perf top -g -p <PID>
```
You will see CPU execution time concentrated in user-defined functions like `fibonacci`, `matrix_multiply`, and `bubble_sort`.

### 4. Generate a Flame Graph
```bash
# Clone the FlameGraph repo if you haven't already
git clone https://github.com/brendangregg/FlameGraph.git ~/FlameGraph

# Record stack samples for 30 seconds
sudo perf record -F 99 -g -p <PID> -- sleep 30

# Collapse stacks and output the flame graph SVG
sudo perf script | ~/FlameGraph/stackcollapse-perf.pl | ~/FlameGraph/flamegraph.pl > flame.svg
```
Open `flame.svg` in any browser to inspect the wide plateaus representing user functions.

---

## Scenario B: Kernel-Mode Saturation (High %sys)

The application saturates the Linux kernel by triggering millions of system calls (syscalls) and thread context switches.

### 1. Run Kernel-Mode Saturation Target
```bash
./build/perf_demo_sys
```

### 2. Observe CPU Saturation with `mpstat`
To view CPU core utilization divided by user (`%usr`) and kernel (`%sys`):
```bash
mpstat -P ALL 1
```
Observe that the `%sys` column is highly saturated (often >70%).

### 3. Trace System Calls with `strace`
To summarize the system calls executed by the target process:
```bash
sudo strace -c -p <PID> -f
```
You will see a heavy skew toward syscalls like:
* `read`/`write` (from the small 1-byte pipe reading/writing)
* `futex` (from intense mutex lock contention)
* `clone`/`exit`/`wait4` (from rapid thread creation/destruction storms)

### 4. Monitor Context Switches with `pidstat`
To monitor context-switching activity:
```bash
pidstat -w -p <PID> 1
```
* **`cswch/s` (Voluntary Context Switches):** Will be high due to threads blocking on the mutex locks and waiting for scheduling (`futex`).
* **`nvcswch/s` (Involuntary Context Switches):** Indicates how often threads are forcibly preempted by the scheduler because their time slices expired.
