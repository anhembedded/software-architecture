## 🗂 Types of Storage Duration

| Storage duration type | Language   | Characteristics                                                                                              | Example                        |
| --------------------- | ---------- | ------------------------------------------------------------------------------------------------------------ | ------------------------------ |
| **Automatic**         | C & C++    | Variables are created when entering a block scope (function, code block) and destroyed when leaving it.      | `int x = 5;` inside a function |
| **Static**            | C & C++    | Variables exist for the entire lifetime of the program. Allocated once, retain value between function calls. | `static int counter = 0;`      |
| **Thread**            | C11, C++11 | Variables exist for the lifetime of a thread. Each thread has its own copy.                                  | `thread_local int id;`         |
| **Dynamic**           | C & C++    | Memory is manually allocated with `malloc/free` (C) or `new/delete` (C++). Exists until explicitly freed.    | `int* p = new int;`            |

---

## 🔑 Differences between C and C++

- **C (from C11)**: supports `_Thread_local` for thread storage duration.
- **C++ (from C++11)**: uses `thread_local` for thread storage duration, and also has temporary objects with automatic storage duration.
- **Specifiers**:
    - `auto` (old C/C++): meant automatic storage, but in modern C++ it means _type deduction_.
    - `register`: suggested storing a variable in CPU registers (deprecated in C++17).
    - `static`: creates static storage duration.
    - `extern`: declares a global variable with static storage duration but external linkage.

---

## ⚠️ Programming Notes

- **Automatic variables**: don’t return addresses of local variables, they become invalid after scope ends.
- **Static variables**: useful for keeping state, but can complicate testing and multithreading.
- **Dynamic memory**: must be managed carefully to avoid leaks or double frees.
- **Thread-local variables**: each thread has its own copy, so they don’t share data.

---

👉 In short: **C and C++ both have 4 storage durations: automatic, static, thread, and dynamic.** C++ adds `thread_local` and changes the meaning of `auto`.

Would you like me to show you a short **C++ code snippet** that demonstrates all four storage durations side by side?