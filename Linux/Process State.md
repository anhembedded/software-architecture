## 📊 Linux Process States

### **R — Running / Runnable**

- **Meaning:** Process is either executing on a CPU or waiting in the run queue to be scheduled.
- **Represents:** _Real CPU demand_.
- **Seen in tools:** `ps` shows `R`.

---

### **D — Uninterruptible Sleep**

- **Meaning:** Process is blocked, usually waiting for I/O (disk, network, NFS).
- **Uninterruptible:** Cannot be killed or interrupted until the I/O completes.
- **Represents:** _I/O bottleneck_.
- **Seen in tools:** `ps` shows `D`.

---

### **S — Sleeping (Interruptible)**

- **Meaning:** Process is idle, waiting for an event (like input or a signal).
- **Interruptible:** Can be woken up by signals.
- **Represents:** _Normal idle state_.
- **Seen in tools:** `ps` shows `S`.

---

### **T — Stopped / Traced**

- **Meaning:** Process has been stopped (e.g., via `SIGSTOP`) or is being debugged (`ptrace`).
- **Represents:** _Paused execution_.
- **Seen in tools:** `ps` shows `T`.

---

### **Z — Zombie**

- **Meaning:** Process has finished execution but still has an entry in the process table because the parent hasn’t collected its exit status.
- **Represents:** _Dead process not cleaned up_.
- **Seen in tools:** `ps` shows `Z`.

---

### **I — Idle (Kernel threads)**

- **Meaning:** Kernel thread is idle.
- **Represents:** _Kernel housekeeping_.
- **Seen in tools:** `ps` shows `I`.

---

## ✅ Why This Matters

- **Load average = R + D.**
- High load could mean many processes in **R state** (true CPU demand) or many in **D state** (I/O wait).
- Always check both CPU utilization (`%usr/%sys`) and I/O wait (`%wa`) before declaring a CPU bottleneck.

---

## 📌 Quick Mnemonic

- **R → Running (CPU demand)**
- **D → Disk wait (I/O blocked)**
- **S → Sleeping (waiting for event)**
- **T → Traced/Stopped**
- **Z → Zombie (dead but not reaped)**
- **I → Idle kernel thread**
