Question Can you introduce a little bit about yourself?
What makes you a senior developer?
Do you have any experience working with Scrum model?
Anything else about the Scrum event?

Experience working with customer in different time zone?


---
**Explain the difference between malloc and calloc. When do you use each?**

Both `malloc()` and `calloc()` are used for dynamic memory allocation on the heap, but they differ in how the allocated memory is initialized.

`malloc(size)` allocates a block of memory of the specified size and leaves the contents uninitialized, so the memory may contain garbage values.

`calloc(num_elements, element_size)` allocates memory for an array of elements and initializes all bytes to zero.

I use `malloc()` when I know I'll immediately overwrite the allocated memory, such as reading data from a file, a socket, or a hardware interface. This avoids the overhead of zero-initialization.

I use `calloc()` when I need the memory to start in a known state, especially for structures containing counters, flags, or pointers. It helps reduce bugs caused by uninitialized data.

---

**Compare static variable and global variable in terms of scope and usage?**

Both static variables and global variables have static storage duration, meaning they exist for the entire lifetime of the program. The main difference is their scope and visibility.

A global variable is declared outside any function and can be accessed from other source files using the `extern` keyword.

A static variable can have two different meanings:

1. A static local variable retains its value between function calls but is only accessible within that function.
2. A static global variable is visible only within the source file where it is declared, providing internal linkage.

I typically use global variables when data must be shared across multiple modules, and static variables when I want to limit visibility and improve encapsulation.

---

**What is the difference between #define and const?**

> `#define` is a preprocessor directive that performs text substitution before compilation and has no type information. 
> 
> `const` is a typed variable handled by the compiler and follows normal scope and type-checking rules. 
> 
> I generally prefer `const` for constants because it is safer and easier to debug, while I use `#define` for macros, register definitions, and conditional compilation.

---

**What is typedef used for? Give an example of its usage.**

> `typedef` is used to create an alias, or alternative name, for an existing data type. 
> 
> It helps improve code readability, maintainability, and portability. 
> 
> It does not create a new type; it only gives an existing type a more meaningful name.
> 
> A common use case is with structures, where `typedef` allows us to avoid repeatedly writing the `struct` keyword.

---

**Compare union and struct.**

Both `struct` and `union` are user-defined data types that can contain multiple members. The key difference is how memory is allocated.

In a `struct`, each member has its own storage location, so all members can hold valid values simultaneously.

In a `union`, all members share the same memory location. Therefore, only one member's value is valid at a time, and writing to one member overwrites the others.


---

**Discriminate local and global variable**

> Local variables and global variables differ mainly in their scope, lifetime, and visibility.
> 
> A local variable is declared inside a function or block and can only be accessed within that function or block. It is created when the function is entered and destroyed when the function exits.
>
> A global variable is declared outside all functions and can be accessed by multiple functions. It exists for the entire lifetime of the program.

---

**What are the advantages and disadvantages of union compared to struct?

Both `struct` and `union` are user-defined data types that can contain multiple members. The key difference is how memory is allocated.

In a `struct`, each member has its own storage location, so all members can hold valid values simultaneously.

In a `union`, all members share the same memory location. Therefore, only one member's value is valid at a time, and writing to one member overwrites the others.

I use a `struct` when I need to store multiple related pieces of data at the same time, and I use a `union` when different data representations share the same memory, especially in memory-constrained embedded systems.

---

#### What are the four fundamental concepts of OOP? 

---

### 🔒 Encapsulation

> Encapsulation is the practice of creating meaningful, self‑contained units within a system. It defines clear boundaries between what is private and what is public, and establishes explicit interaction contracts. It is not just a technical mechanism, but a philosophy for structuring and managing complexity in interactive systems.

---

### 🎭 Polymorphism

> Polymorphism is the phenomenon where different entities implement a common concept or contract in distinct ways, depending on their identity and the context in which they operate.

---

### 🧬 Inheritance

> Inheritance represents a structural relationship in which a concept acquires the public attributes and contracts of a higher‑level concept. At the same time, the derived concept maintains its own identity, distinguishing itself from the higher‑level abstraction.

---

### 🌐 Abstraction

> Abstraction is the process of building a new conceptual model at a higher level of understanding. It captures the essence and general rules of operation for different purposes, rather than being just a “less detailed” version of an existing model. It creates a new concept that encompasses and unifies the concepts and conventions under consideration.


---

#### What is the difference between class and struct in C++?

Default access control and inheritance semantics

---

#### Compare virtual function and pure virtual function.

A virtual function in C++ is a function declared with `virtual` that may have a base implementation and can be optionally overridden by derived classes. 

A pure virtual function, declared with `= 0`, has no implementation in the base class and makes the class abstract — it cannot be instantiated and forces derived classes to implement the function. 

Both rely on v‑tables for runtime dispatch, but pure virtual functions enforce abstraction while virtual functions allow default behavior with polymorphic override.”

---

#### What is a friend function?  What are its benefits and drawbacks?

A friend function in C++ is a non-member function that has access to a class’s private and protected members. 

It’s often used for operator overloading or when two classes need close collaboration. 
The benefit is flexibility and controlled access without making members public. 

The drawback is that it breaks encapsulation and can lead to tight coupling if overused, so it should be applied sparingly and only when justified.

---


#### How do you delete a file or directory with rm? 

In Linux, you delete files with `rm filename`. To delete directories, you use `rm -r dirname` for recursive removal. 
If you want to force deletion without prompts, you add `-f`. So `rm -rf dirname` will remove a directory and all its contents. 
The main benefit is simplicity, but the drawback is risk — if you’re not careful, you can accidentally delete critical files.

---

**How do you change directories (cd)? 
How do you go to the parent directory, root directory, or home directory?**

In Linux, you use `cd` to change directories. For example, `cd /path/to/dir` moves into a directory. To go to the parent directory you use `cd ..`, to the root directory you use `cd /`, and to your home directory you use `cd ~` or just `cd`

---

**What command is used to clone a local repository from a remote?
Explain the difference between git fetch and git pull. 
When should each be used?


> “To clone a remote repository locally, we use `git clone <url>`. The difference between `git fetch` and `git pull` is that `fetch` only downloads changes from the remote without merging them, while `pull` both fetches and merges into your current branch. I use `fetch` when I want to inspect changes safely, and `pull` when I’m ready to integrate those changes into my work.”

---

**How do you list all active processes in Linux?**

In Linux, you can list all active processes using `ps aux` or `ps -ef` for a snapshot, or `top`/`htop` for a real‑time interactive view. `ps` is great for scripting and detailed inspection, while `top` is useful for monitoring resource usage live.

---

**How to find out which processes are connected to a port number?

In Linux, you can find which process is connected to a port using commands like `lsof -i :PORT`, `netstat -tulnp`, or `ss -tulnp`. These commands show the process ID and program name bound to that port. For example, `lsof -i :80` will tell you which process is using port 80.

---

**How to find out what a process is doing?**

In Linux, you can find out what a process is doing by inspecting it with tools like `ps` for basic info, `top` or `htop` for resource usage, `lsof` to see which files or sockets it has open, and `strace` to trace its system calls. You can also look in `/proc/<PID>/` to see its command line, status, and file descriptors. Together, these tools let you understand the activity of a running process.

---

**Stack vs Heap memory allocation in C?**

Stack and heap are two different memory regions used for storing data during program execution.

Stack memory is automatically managed by the compiler. Local variables and function call information are typically stored on the stack. Memory is allocated and released automatically when functions are entered and exited.

Heap memory is dynamically allocated during runtime using functions such as `malloc()`, `calloc()`, and `free()`. The programmer is responsible for managing its lifetime.

Stack allocation is generally faster and simpler, while heap allocation provides more flexibility for dynamic-sized data and objects that need to outlive a function call.

---

#### What is a Smart Pointer?**

A smart pointer is a C++ object that manages the lifetime of dynamically allocated memory automatically using the RAII (Resource Acquisition Is Initialization) principle.

It automatically releases the managed resource when it is no longer needed, helping prevent memory leaks and dangling pointers.

*std::unique_ptr*
Only one owner is allowed.

*std::shared_ptr*
Multiple objects can own the same resource.

*std::weak_ptr*
Does NOT increase reference count.


---

#### What are C++ Templates?

Templates are a C++ feature that allows writing generic code that can work with different data types without duplicating the implementation.

The compiler generates the actual code when the template is instantiated with a specific type.

Templates provide static polymorphism and zero-cost abstractions, but the trade-offs are increased compile times, larger binaries due to multiple instantiations, and reduced encapsulation because implementations are typically exposed to users. 

In large codebases, build time and code complexity are usually the biggest concerns.

---

**How is abstraction represented in C++?**

In C++, abstraction is achieved by defining **abstract classes with pure virtual functions**. These act as blueprints for derived classes, ensuring a clear separation between _what_ an object should do and _how_ it does it. This is the foundation for designing scalable, maintainable, and polymorphic systems.

---

**What is the difference between class and struct in C++?**

In C++, `class` and `struct` are almost identical. The main differences are the default access specifier and the default inheritance type.

For a `struct`, members and inheritance are public by default.

For a `class`, members and inheritance are private by default.

Other than that, both can have constructors, destructors, member functions, inheritance, templates, operator overloading, and all other C++ features.

In Philosophy design, use structs to model passive data and classes to model objects with behavior, ownership, or invariants that need to be protected

---

**Why do you need virtual function when you can override function in class parents through child class.**

A derived class can redefine a function even without `virtual`, but the correct derived implementation will only be called when the object's static type is known at compile time. Virtual functions enable runtime polymorphism, allowing calls through a base-class pointer or reference to dispatch to the actual derived object's implementation. This lets us write generic code against a base interface while preserving derived-specific behavior.

---

**What is thrashing in Linux**

Thrashing is a state when the RAM is overlaoded with active process, and the kernel start to do swapping space in order to keep all task running. while the CPU utilization is low while waiting for kernel jobs, revolve it calling more process and make the situation worse.
Thrashing make the kernel perform swapping space so much so 99% of its time is spend to move resources of process in and out of hard drive and leave just 1 % running the task.

---

**Can you name some common software design patterns?**

Singleton, single instance
Factory, Create obj with out expose logic creating.
Observer, for publish and subscribe mechanism
Adapter, for interface adaptation
State machine

---

#### What are the common bottlenecks in Linux system

The most common Linux bottlenecks are CPU, memory, disk I/O, network, and paging/swapping. I usually start with `top` or `htop` for an overall view. 

For CPU issues I check `utilization` and `load average`. For memory I check `free` and `/proc/meminfo`. For disk I/O I use `iostat` and look at `%util` and `await`. For paging issues I monitor swap usage and `vmstat` metrics such as `si` and `so`. In multi-threaded applications, lock contention and excessive context switching can also become major bottlenecks even when CPU usage appears normal.

1. CPU Bottleneck
2. Memory Bottleneck
3. Swap / Paging Bottleneck
4. Disk I/O Bottleneck
5. Network Bottleneck
6. Lock Contention
7. Context Switching
8. Interrupt Bottleneck
9. Interrupt Bottleneck
10. NUMA Bottleneck (Advanced)

---



What is a primary key? 
Why is it important?
What is a foreign key?
What different types of database joins do we have?
What is normalization? 
Why is it important?
When do we use transactions in database?