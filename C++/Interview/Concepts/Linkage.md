# 🔗 Linkage in C

## Overview
In C, *linkage* determines whether a name (variable or function) can be referred to from other translation units (source files).  
It defines the visibility of identifiers across files.

---
## 📂 Types of Linkage

### 1. External Linkage
- Names are accessible from other translation units.
- Default for global variables and functions (unless marked `static`).
```c
// file1.c
int globalVar = 42;   // external linkage

// file2.c
extern int globalVar; // refers to the same variable
````

### 2. Internal Linkage

- Names are only visible within the same translation unit.
- Declared with `static` at file scope.

```c
// file1.c
static int fileVar = 0;   // internal linkage
static void helper() {    // internal linkage function
    fileVar++;
}
```

### 3. No Linkage

- Names are confined to their scope (e.g., local variables).

```c
void func() {
    int localVar = 10; // no linkage
}
```

---

## ⚠️ Notes

- In **C**, `const` does _not_ imply internal linkage; you must explicitly use `static`.
- Functions without `static` at file scope have external linkage by default.
- Linkage is distinct from **storage duration** (how long memory exists). For example:
    - `static int x;` at file scope → **static storage duration + internal linkage**.

---

## 📎 Related Topics

- [[Storage Duration in C]]
- [[Scope in C]]
- [[Translation Units]]

---

## 🔗 References

- ISO C Standard (C11 §6.2.2)
- C Programming Linkage Explanation [(en.cppreference.com in Bing)](https://www.bing.com/search?q=%22https%3A%2F%2Fen.cppreference.com%2Fw%2Fc%2Flanguage%2Flinkage%22)