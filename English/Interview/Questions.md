Question Can you introduce a little bit about yourself?
What makes you a senior developer?
Do you have any experience working with Scrum model?
Anything else about the Scrum event?
Experience working with customer in different timezone?


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

> `#define` is a preprocessor directive that performs text substitution before compilation and has no type information. `const` is a typed variable handled by the compiler and follows normal scope and type-checking rules. I generally prefer `const` for constants because it is safer and easier to debug, while I use `#define` for macros, register definitions, and conditional compilation.

---

**What is typedef used for? Give an example of its usage.**

> `typedef` is used to create an alias, or alternative name, for an existing data type. It helps improve code readability, maintainability, and portability. It does not create a new type; it only gives an existing type a more meaningful name.
> 
> A common use case is with structures, where `typedef` allows us to avoid repeatedly writing the `struct` keyword.

---
**Compare union and struct.**

Both `struct` and `union` are user-defined data types that can contain multiple members. The key difference is how memory is allocated.

In a `struct`, each member has its own storage location, so all members can hold valid values simultaneously.

In a `union`, all members share the same memory location. Therefore, only one member's value is valid at a time, and writing to one member overwrites the others.




What are the advantages and disadvantages of union compared to struct?
What are the four fundamental concepts of OOP? 
Explain how each is applied in C++.
What is inheritance in C++? 
Write a simple example to demonstrate inheritance.
How is abstraction represented in C++?
What is the difference between class and struct in C++?
Compare virtual function and pure virtual function.
What is a friend function? 
What are its benefits and drawbacks?
How do you delete a file or directory with rm? 
How do you delete a non-empty directory?
How do you change directories (cd)? 
How do you go to the parent directory, root directory, or home directory?
What command is used to clone a local repository from a remote?
Explain the difference between git fetch and git pull. 
When should each be used?
How do you list all active processes in Linux?
How to find out which processes are connected to a port number?
How to find out what a process is doing?
How to stop a process?
What is a primary key? 
Why is it important?
What is a foreign key?
What different types of database joins do we have?
What is normalization? 
Why is it important?
When do we use transactions in database?