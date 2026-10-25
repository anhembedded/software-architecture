**

# Book Report  
# C++ Revision

![](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAC8AAAAGCAYAAABThMdSAAAAKklEQVR4AeyRQQkAAAwCh0HWn7VbAo0hgoL/4w57z9Rjgld4V7yad5kXAAAA///ok/kLAAAABklEQVQDANnrf9UWl+FeAAAAAElFTkSuQmCC "short line")

Anh.Embedded  
4th September, 20XX

  

# I. CLASS / OOP

  

## a. Fundamental Knowledge

### The 4 Pillars of OOP

**What is Encapsulation?**

It is the creation of meaningful, autonomous, and responsible entities within a system by explicitly defining boundaries between private and public members, while establishing a clear contract for interaction. It is not merely a coding technique, but a software design philosophy for structuring and managing complexity in interactive systems.

**What is Polymorphism?**

Polymorphism is the phenomenon where different entities execute a broadly defined concept or interface in their own distinct ways, based on the specific identity of each entity and the runtime context.

**What is Inheritance?**

It is a conceptual structural relationship where a derived concept or contract inherits the public characteristics of a higher-level concept/contract. The derived concept must also possess its own unique characteristics to distinguish itself from the higher-level concept it inherits from.

**What is Abstraction?**

It is the process of building a new conceptual model at a higher level of awareness—a model that captures the essential nature and general operating principles based on different goals, rather than just being a "less detailed" version of the original. It involves creating a new concept that encompasses the existing concepts and conventions under consideration.

  
  

### The Five Default Member Functions of a Class

Whether you need to manually implement them depends on whether the Class intentionally manages resources directly (e.g., heap memory, file handles, network sockets).

**Default Constructor:**

• Called automatically when an object is instantiated without any arguments.

• The compiler automatically generates a default constructor if no user-defined constructor is declared.

**Destructor:**

• Called automatically when an object is destroyed to release resources.

• The compiler generates a default destructor if one is not defined.

**Copy Constructor:**

• Called when a new object is initialized by copying an existing object of the same class.

• The compiler generates a default copy constructor if no user-defined copy constructor exists.

**Copy Assignment Operator:**

• Called when assigning a value from one object to another existing object using the `=` operator.

**Move Constructor and Move Assignment Operator (C++11 and later):**

• **Move Constructor:** Transfers ownership of resources from a source object (rvalue) to a new object.

• **Move Assignment Operator:** Assigns an object by transferring resource ownership from a source object.

  

---------------------------------------------------------------------

## b. Questions

### 1. Distinguish between a class and an object?

From a developer's perspective:

**Class:**

A Class is an abstract template that exists at compile-time. Based on the Class definition, the compiler will:

+ Determine the Memory Layout

+ Generate Machine Executable Code

+ Generate Metadata (V-table)

**Object:**

An Object is a concrete entity, an instantiation of a Class at runtime:

+ Consumes Resources: Occupies memory address space

+ Holds State: Maintains data member states

+ Contains V-ptr (Virtual Pointer, if the class contains virtual functions)

### 2. What is a Constructor?

• A Constructor is a special member function called automatically when an object is instantiated, or it can be called explicitly in specific patterns.

• Purpose: To initialize an object by:

  Querying/allocating resources (RAII)

  Initializing default values

### 3. What is a Copy Constructor?

• A Copy Constructor is a special constructor used to initialize a new object using an existing object of the same class.

### 4. What is an Access Specifier?

Access Specifiers in C++ define the accessibility level of class members. There are 3 types:

1. **Public:** Members can be accessed from anywhere in the program.

2. **Private:** Members can only be accessed from within the class itself.

3. **Protected:** Members can be accessed from within the base class and derived (child) classes.

*Note on "Anywhere": Inside/outside the class, from other classes, and from derived classes.*

### 5. Distinguish between Overloading and Overriding in C++

Both are techniques in C++ to achieve polymorphism.

One is static polymorphism (compile-time), and the other is dynamic polymorphism (runtime).

**Overloading (Static Polymorphism):** Relies entirely on explicit naming identification and signature matching. Function calls are bound to specific symbol mangled names right during the compilation/linking process.

**Overriding (Dynamic Polymorphism):** Relies entirely on runtime metadata—specifically the pairing of V-Table (Class-level data) and V-Ptr (Object-level pointer)—to look up and invoke the correct function version at runtime.

### 6. Explain why destructors must be declared as `virtual` in base classes when working with polymorphism?

When a base class has a non-virtual destructor, deleting a derived object through a pointer to the base class will only invoke the base class destructor. The derived class destructor will not be called, leading to resource leaks and undefined behavior.

### 7. When is a virtual destructor needed?

• **Needed:** When a base class is intended to serve as an interface or has derived classes used polymorphically, AND the derived/base classes manage resources explicitly.

*Note: Making base class destructors virtual when polymorphism is involved is a standard C++ idiom.*

### 8. What is a Friend Class?

• A friend class is a class granted direct access to `private` and `protected` methods and properties of another class.

• Declared using the `friend` keyword inside the class granting access.

### 9. What is a Friend Function?

• A friend function is a non-member function that is granted direct access to `private` and `protected` methods and properties of a class.

• Declared using the `friend` keyword inside the target class.

• Purpose: Used when a function needs tight integration with internal class data without logically being a member of that class (e.g., operator overloading).

### 10. Two main types of polymorphism:

• **Compile-time polymorphism:**

Ex: Function overloading, operator overloading, templates.

• **Runtime polymorphism:**

Ex: Achieved through inheritance and `virtual` functions.

### 11. How does the compiler know if a derived class has not overridden a pure virtual function?

The `virtual` keyword enables dynamic polymorphism, requiring the compiler to build a V-table mapping virtual functions to their corresponding class overrides.

For a pure virtual function (`= 0`), the compiler checks whether derived classes provide an implementation:

-> If not overridden, the compiler flags the derived class as an abstract class and generates a compilation error if an attempt is made to instantiate an object from it.

### 12. What are static data members and static member functions?

In a C++ class, the `static` keyword changes the binding of a member from belonging to a specific object instance to belonging to the class itself.

+ **Static data members:** Shared across all instances of the class, defined outside the class header in a source file.

+ **Static member functions:** Belong to the class and can be invoked directly using the class name (`Class::Method()`) without instantiating an object.

*Note: Only one translation unit should define a static variable; other files should declare it using the `extern` keyword if accessed globally.*

### 13. When should multiple inheritance be used?

+ When you need to combine attributes and behaviors from multiple distinct classes.

+ When you want a subclass to utilize methods and properties from multiple parent classes.

+ When you want to organize code such that a class inherits from multiple sources.

+ *When you want to increase design coupling (irony).*

+ *When you want a very poor design (irony).*

+ *When you want to make future maintenance difficult (irony).*

+ *And please forget multiple inheritance, redesign your code for clean principles instead (irony).*

Instead of a class being many things (e.g., `class ActiveStudent : public Student, public Athlete`), it is much better if that class HAS those things via composition (e.g., `class Student` containing an `Athlete` role object).

### 14. What is Virtual Inheritance?

• Virtual inheritance is a technique in C++ used to solve the "Diamond Problem" in multiple inheritance.

• When a child class inherits from two parent classes that both inherit from the same grandparent class, two copies of the grandparent class would normally exist inside the child class.

• Virtual inheritance ensures that only one shared instance of the grandparent class is created within the child class, eliminating ambiguity and collision when accessing grandparent members.

### 15. Can destructors be overloaded?

• Destructors **cannot** be overloaded in C++.

• Destructors cannot accept any parameters, as they are invoked automatically when an object is destroyed.

• If you need different destruction behaviors, you can pass flags to constructors or use helper cleanup methods.

### 16. What are shallow copy and deep copy?

**Shallow Copy:** Creates a new object and copies member field values from the original object bit-by-bit without allocating new external resources for the new object.

Resources can be:

  An open file on disk.

  A network socket connection.

  A Mutex / lock.

  Hardware SPI, UART handles, etc.

**Deep Copy:** Allocates new memory/resources for the new object and copies the actual underlying data, ensuring complete resource independence between objects.

### 17. Compare `struct`, `class`, and `union`?

These are 3 keywords in C++ used to construct user-defined types. Each keyword produces a type with unique identity and applications:

At technical, design philosophy, and usage levels:

- **Struct:**

  Passive data encapsulation.

  Size is the sum of member sizes (plus padding bytes).

  Philosophy: *"This is a data container."* (Default access: `public`)

- **Class:**

  Creation of autonomous entities with behavior and encapsulation.

  Size is the sum of member sizes (plus padding). If the class has virtual functions, object size adds the size of a v-pointer (`vptr`).

  Philosophy: *"This is a living entity with independent state and behavior."* (Default access: `private`)

- **Union:**

  Memory optimization & data reinterpretation.

  All members share the exact same memory space. Size equals the size of its largest member.

  Philosophy: *"This is a memory region optimized for multiple mutually exclusive purposes."*

  

# II. MEMORY AND SYSTEM

## a. Fundamental Knowledge

### Memory Segments:

#### 1. Code Segment (Text Segment)

Physical memory region requiring memory mapping.

The CPU uses instruction sets to directly execute instructions from this memory (Embedded/Firmware).

• **Purpose:** Stores compiled executable binary instructions.

• **Characteristics:**

  Read-only memory to protect code from runtime modification.

  Fixed size determined during compilation and linking.

#### 2. Static/Global Segment (Data Segment)

**Initialized Data Segment (`.data`):**

Requires memory mapping.

CPU can directly access this memory via instructions.

Requires bootloader or assembly startup code to initialize data from Flash to RAM based on linker script sections (Embedded/Firmware).

• **Purpose:** Stores initialized global and static variables.

• **Characteristics:** Memory allocated when the program launches and freed upon program termination.

**Uninitialized Data Segment (`.bss` - Block Started by Symbol):**

• **Purpose:** Stores uninitialized global and static variables.

• **Characteristics:** Zero-initialized by default by startup code before `main()` executes.

#### 3. Stack

• **Purpose:** Stores local variables, function execution call frames, return addresses, and parameter values.

• **Characteristics:**

  Automatic allocation/deallocation when functions are called and return.

  Limited size (system-dependent).

  Grows and shrinks following LIFO (Last In, First Out) stack order.

#### 4. Heap

• **Purpose:** Stores dynamically allocated memory managed via `new`/`delete` or `malloc()`/`free()`.

• **Characteristics:**

  Requires manual memory management; otherwise, memory leaks occur.

  Much larger capacity than the stack, but access speed is slower.

#### 5. CPU Registers

Variables stored directly inside CPU registers, typically managed by compiler optimization. Keywords like `register` can hint to the compiler, though MISRA rules discourage its explicit use.

These locations are not memory-mapped addresses.

### Program Build Process in C/C++:

#### 1. Preprocessing

• Processes directives starting with `#` (e.g., `#include`, `#define`, `#ifdef`).

• Generates intermediate source files containing clean C/C++ code stripped of preprocessor directives.

#### 2. Compiling

• Translates preprocessed source code into CPU architecture-specific assembly code.

• Output files typically have `.s` extension.

#### 3. Assembling

• Translates assembly code into binary machine code object files.

• Generates object files with `.o` (Linux) or `.obj` (Windows) extensions.

#### 4. Linking

• Combines object files and library files into a final executable (`.exe` or `.elf` / `.out`).

• Resolves undefined symbol references (e.g., calls to library functions like `printf`, `std::cout`).

  

## b. Questions

### 1. Compare `new` vs `malloc()`?

+ `new` is a C++ operator that performs a two-step object creation process: first allocating memory, then calling the object constructor to initialize the memory into a valid object instance. It is type-safe, handles errors via exceptions (`std::bad_alloc`), and can be overloaded.

+ `malloc()` is a function inherited from C that performs a single task: requesting raw, uninitialized memory allocation of a specified byte size. It is type-agnostic, does not call constructors, and signals failure by returning a `NULL` pointer.

In short: `new` creates a living **Object**, whereas `malloc()` merely returns a raw **Memory Region**.

### 2. Compare `delete` vs `free()`?

• `delete`: Frees memory AND calls the object's destructor.

• `free()`: Only deallocates memory without calling destructors.

• `delete`: Used exclusively for memory allocated via `new`.

• `free()`: Used exclusively for memory allocated via `malloc()`.

• `delete`: Can be overloaded for custom memory management.

• `free()`: Cannot be overloaded.

### 3. Compare Static and Dynamic Memory Allocation

**Allocation Timing:**

• **Static:** Allocated before `main()` starts running (at build/load time).

• **Dynamic:** Allocated at runtime dynamically.

**Memory Location:**

• **Static:** Occupies memory mapped sections based on variable attributes and compiler output:

  Initialized static variables (`int a = 10;`) reside in `.data` (RAM).

  Uninitialized static variables (`int b;`) reside in `.bss` (RAM).

  Const static constants (`const static int c = 20;`) can be placed in `.rodata` (Read-only data / Flash).

• **Dynamic:** Resides on the Heap memory region.

**Memory Management:**

• **Static:** Managed automatically by program execution lifecycle.

• **Dynamic:** Managed manually via `new`/`delete` or `malloc()`/`free()`.

*NOTE: Memory allocated on the Stack is NOT Static Allocation. Stack allocation is Automatic Storage Duration tied to function scope lifecycle.*

Storage Durations in C++:
1. Static Storage Duration
2. Automatic Storage Duration
3. Dynamic Storage Duration
4. Thread Storage Duration

### 4. Differences between C and C++

C philosophy focuses on providing a "high-level assembly language", allowing developers direct, raw memory manipulation. C++ philosophy focuses on building powerful, type-safe abstractions without sacrificing low-level performance.

In terms of paradigm, C++ supports Object-Oriented Programming (OOP) among others, while C is purely procedural.

-> **Rebuttal:** C++ is a multi-paradigm language. A skilled C++ developer can write procedural code, object-oriented code, generic code (templates), and functional code. Viewing C++ solely as OOP is an incomplete perspective.

C supports manual memory management via `malloc`/`free`, while C++ provides both manual and automatic mechanisms (`new`, `delete`, RAII, smart pointers). C++ adds classes, exceptions, overloading, templates, and the STL.

### 5. Compare C++ standards evolution

• **C++98 to C++11:** Introduced smart pointers (`unique_ptr`, `shared_ptr`), lambda functions, `unordered_map`, `std::array`, move semantics, `std::thread`, and `std::mutex`.

• **C++11 to C++14/C++17:** Added `std::make_unique`, expanded lambda features, `std::optional`, `std::variant`, `std::string_view`, structured bindings, and `filesystem`.

### 6. What is a Stack Overflow error?

Stack Overflow is a runtime error occurring when a program attempts to use more stack memory space than allocated by the OS for that thread.

Main causes include:

+ **Deep or infinite recursion:** Each recursive call creates a new stack frame, exhausting stack memory rapidly.

+ **Very large local variables:** Declaring large arrays on the stack (e.g., `int large_array[1000000];`) instantly exceeds stack limits.

Detection Mechanism: The stack pointer accesses a guarded memory page (`guard page`) located at the stack boundary, triggering a hardware fault handled by the OS to terminate the process cleanly.

### 7. Difference between `delete` and `delete[]`?

**`delete`:**

Used to free memory allocated for a single object created with `new`.

-> Execution flow:

  Calls the destructor of the object (if any).

  Frees allocated memory block.

-> Syntax:
```cpp
int* ptr = new int(42);
delete ptr; // Frees single integer memory
```

**`delete[]`:**

Used to free memory allocated for an array of objects created with `new[]`.

-> Execution flow:

  Calls the destructor for every element in the array in reverse order.

  Frees the entire allocated memory block for the array.

-> Syntax:
```cpp
int* arr = new int[5]; // Allocates array of 5 elements
delete[] arr; // Frees whole array
```

### 8. What are Mutex and Semaphore?

Both are synchronization mechanisms in multithreaded programming, but serve different purposes:

**Mutex:**

• A locking mechanism used to protect a shared resource from simultaneous concurrent access by multiple threads.

• Allows only ONE thread ownership of the mutex at any given time; other threads must wait until released.

• Example usage:
```cpp
std::mutex mtx;
mtx.lock(); // Acquire mutex lock
// Perform operations on shared resource
mtx.unlock(); // Release mutex lock
```

**Semaphore:**

• A signaling counting variable used to manage concurrent access to one or more shared resource units.

• Allows multiple threads access simultaneously depending on the semaphore counter value.

• Example usage:
```cpp
std::counting_semaphore<5> sem(5); // Initial counter value = 5
sem.acquire(); // Decrement counter, wait if count <= 0
// Operations on shared resource
sem.release(); // Increment counter
```

### 9. What is Shared Memory?

- Shared memory is a memory region shared between multiple processes or threads, allowing them to exchange data directly without kernel copy overhead.

- **Advantages:**

  Fastest IPC method because it avoids kernel boundary data copying.

  Low system overhead compared to pipes or sockets.

- **Disadvantages:**

  Requires explicit user synchronization mechanisms (mutexes, semaphores) to prevent race conditions.

- POSIX Shared Memory Example:
```cpp
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = shm_open("/my_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(int));
    int* shared_data = (int*)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    *shared_data = 42; // Write data to shared memory

    munmap(shared_data, sizeof(int));
    close(fd);
    shm_unlink("/my_shm"); // Unlink shared memory object
    return 0;
}
```

### 10. What is the OS Boot Process?

• The boot process brings a computer system from powered-off state to an operational OS ready state.

• Main stages:

  1. **Power-On Self Test (POST):** Hardware check (RAM, CPU, storage).

  2. **Bootloader Loading:** Finds and executes bootloader from storage media.

  3. **Kernel Loading:** Bootloader loads OS kernel into RAM.

  4. **OS Initialization:** Kernel initializes system architecture components, drivers, memory management.

  5. **Services & App Launch:** Starts system daemons and user interface.

### 11. What is a Bootloader?

• A Bootloader is a small program stored in non-volatile memory or storage sectors responsible for loading the main OS kernel into RAM upon system boot.

• Functions:

  1. Locates and loads OS kernel binary.

  2. Configures kernel command line parameters and hardware state.

  3. Transfers execution control to kernel entry point.

### 12. What is U-Boot?

• U-Boot (Universal Bootloader) is a widespread open-source bootloader used in embedded systems (ARM, MIPS, RISC-V) powering smartphones, IoT routers, automotive units.

• Supports loading kernels across diverse mediums (Flash memory, Ethernet network TFTP, SD card).

• Provides CLI interface for configuration and low-level debugging.

### 13. What is a Device Driver?

• A device driver is software bridging the kernel and hardware peripherals, allowing the OS to command hardware.

• Exposes abstract standard APIs so OS services interact uniformally without hardware implementation specifics.

### 14. What is a Device Tree?

• A Device Tree (DT) is a data structure describing system hardware topologies, extensively used in Embedded Linux.

• Provides hardware component layout descriptions (addresses, interrupts, clocks) without hardcoding into kernel source code binaries.

📌 Summary:

➡️ Device Tree defines:

- What components exist (e.g., UART peripheral)

- Where it is mapped (`reg` base address)

- Compatibility string (`compatible`)

➡️ Driver:

- Contains logic to configure that specific UART peripheral

- Accesses mapped memory registers

- Provides OS APIs (e.g., serial print logging)

### 15. What is a Cross Compiler?

A cross compiler runs on one build architecture (e.g., x86_64 host PC) and generates executable machine code for a different target architecture (e.g., ARM64 embedded board).

### 16. Distinguish between Process and Thread?

🧠 **Process:**

- Independent execution program unit with dedicated address space (private memory).

- Heavyweight creation (high system memory & CPU overhead).

- Inter-Process Communication (IPC) requires explicit mechanisms (shared memory, sockets, pipes).

⚡ **Thread:**

- Smallest execution scheduling unit contained inside a parent process.

- Shares address space, heap, globals, and file descriptors with sibling threads in the process.

- Lightweight creation and fast context switching.

- Communication between threads is effortless due to shared memory space.

🔧 **System Internals Perspective:**

✅ **Process:**

- Managed by OS kernel with unique PID, page table hierarchy, file descriptor tables.

- Used for system process isolation (e.g., web server daemon vs database process).

- Direct memory access across processes is strictly prohibited without IPC.

✅ **Thread (within process):**

- Possesses unique Thread ID (TID) sharing parent PID space.

- Shares heap, static globals, file descriptors -> risk of race conditions if unguarded.

- Possesses individual stack frame and register context (program counter, stack pointer).

🛠 **In Embedded C++ Systems:**

- RTOS environments (FreeRTOS, ThreadX, Zephyr) run single address space thread/task architectures.

- Embedded Linux utilizes processes for service sandboxing and threads for internal application concurrency.

🎯 **Interview Highlights:**

- *Concurrent write risk:* Concurrent un-synchronized writes cause data races; require mutexes, semaphores, or atomic operations.

- *Crash impact:* A thread segmentation fault kills the entire host process.

- *Why embedded prefers threads:* Threads conserve precious memory RAM footprint and execute fast real-time context switches.

Note:

📖 **Page Table:** Maps virtual memory addresses used by processes into physical RAM addresses.

📝 **Descriptor:** Process Descriptor stores process control blocks (PCB); File Descriptor is an integer index representing open system files/sockets.

### 17. System Calls

System Calls provide controlled gate entry points into the kernel space, allowing user-space applications to request privileged hardware and kernel operations.

⚙ **System Call Execution Flow:**

- OS maintains syscall table (e.g., `sys_open` on Linux).

- CPU executes trap instruction (`syscall`), switching execution from user mode to kernel mode.

- Kernel validates input arguments, executes action, returns result, and transitions CPU back to user mode.

### 18. Big Endian vs Little Endian

Describes byte ordering of multibyte numbers in RAM:

- **Big Endian:** Most Significant Byte (MSB) stored at lowest memory address.

- **Little Endian:** Least Significant Byte (LSB) stored at lowest memory address (standard on x86 & ARM default).

### 19. Android AOSP

Android Open Source Project (AOSP) is Google's open source Android OS core repository providing framework code, HAL definitions, system daemons, and base applications.

### 20. Android HAL

Hardware Abstraction Layer (HAL) defines standard C/C++ interface hooks allowing Android Java/Native frameworks to communicate with vendor hardware drivers seamlessly.

### 21. Android vs Standard Linux

Android utilizes the Linux Kernel but replaces standard GNU userspace components with Bionic libc, custom init scripts, surface flinger, and Binder IPC instead of standard System V IPC.

### 22. Android Binder

Binder is Android's specialized high-performance IPC mechanism operating as a Linux kernel driver. It provides object-oriented IPC calls with single-copy memory efficiency.

### 23. MQTT (Message Queue Telemetry Transport)

MQTT is a lightweight publish/subscribe messaging protocol designed for low-bandwidth, high-latency IoT device communication over TCP/IP.

⚙ **MQTT Operation:**

1. Clients establish connection to a central Broker via TCP/IP.

2. Client subscribes to specific topics (`/sensors/temp`).

3. Another client publishes data to `/sensors/temp`.

4. Broker routes and forwards published data to all subscribed clients.

🔥 **Interview FAQs:**

1. *MQTT vs HTTP:* MQTT is ultra-lightweight binary protocol (headers ~2 bytes), ideal for constrained IoT devices compared to verbose HTTP.

2. *Why Pub/Sub over Req/Res:* Decouples sender and receiver in space and time; clients do not need to know direct IPs.

3. *Security:* Supports TLS/SSL encryption and username/password or X.509 client certificate authentication.

### 24. What is SPI?

SPI (Serial Peripheral Interface) is a synchronous 4-wire full-duplex serial interface for short-distance chip communication.

Wires:

1. **MOSI (Master Out Slave In):** Data line Master to Slave.

2. **MISO (Master In Slave Out):** Data line Slave to Master.

3. **SCLK (Serial Clock):** Clock signal generated by Master.

4. **CS / SS (Chip Select / Slave Select):** Select line activating target slave.

### 25. Static Library vs Shared Library

🔹 **Static Library (`.a` / `.lib`):**

- Archive of compiled object files linked directly into program executable at build time.

- Binary image self-contained; no external library dependencies needed at runtime.

- Pros: Fast execution, simple deployment.

- Cons: Larger binary size, re-compilation required upon library updates.

🔹 **Shared Library (`.so` / `.dll`):**

- Dynamic library loaded into memory at launch or runtime.

- Multiple processes share single dynamic library instance in RAM.

- Pros: Small binary footprint, modular runtime updates without app re-compilation.

- Cons: External dependency management (DLL hell), slight startup symbol binding overhead.

### 26. Why split large software into multiple processes?

1. **Fault Isolation:** Crash in one process does not crash other system services.

2. **Scalability:** Processes scale across CPU cores or remote microservices network nodes.

3. **Resource Management:** Independent memory allocation and priority tuning per process.

4. **Maintainability & Deployment:** Individual services updated without restarting full system stack.

5. **Security Isolation:** Services run under restricted user access privilege levels (sandboxing).

### 27. Process States

1. **New:** Process being initialized.

2. **Ready:** Process in RAM waiting for CPU scheduler assignment.

3. **Running:** Instructions currently executing on CPU.

4. **Blocked / Waiting:** Process waiting for I/O completion or signal event.

5. **Terminated:** Execution finished or stopped by OS.

6. **Suspended:** Swapped out of main RAM memory to secondary storage.

### 28. IPC Classifications

- **Shared Memory:** Zero-copy, fastest IPC, requires explicit synchronization.

- **Message Passing:** Sockets, Pipes, Message Queues, Binder:

  *Direct vs Indirect:* Named target process vs mailbox/queue endpoint.

  *Synchronous vs Asynchronous:* Blocking sender until receiver responds vs non-blocking buffered delivery.

  *Automatic vs Explicit Buffering:* OS kernel auto-managed buffer vs application-managed ring buffers.

### 29. Binder on Android

Android Binder IPC provides low overhead inter-process RPC calls passing objects across process boundaries via shared memory mapped buffer IPC kernel driver space.

### 30. Software Development Life Cycle (SDLC)

SDLC defines stages for engineering quality software products:

1. **Requirement Analysis:** SRS documentation.

2. **Design:** Architecture, class diagrams, database schemas.

3. **Development / Coding:** Implementation according to design specs.

4. **Testing:** Unit, Integration, System, and Acceptance testing.

5. **Deployment:** Production release.

6. **Maintenance:** Bug fixes, security updates, feature enhancements.

### SDLC vs OOAD

| Criteria | SDLC (Software Development Life Cycle) | OOAD (Object-Oriented Analysis & Design) |
|---|---|---|
| **Goal** | Manage complete software development lifecycle | Design software architecture using object-oriented principles |
| **Scope** | Covers all phases from requirements to maintenance | Focused strictly on analysis and design models |
| **Approach** | Agile, Scrum, Waterfall methodologies | UML diagrams, Use Cases, Class design patterns |
| **Usage** | Project management across teams | Architectural technical design prior to coding |

### 31. What is the V-Model?

V-Model is a software development workflow expanding on Waterfall where testing verification phases execute in parallel alignment with development design stages:

| Development Stage | Corresponding Verification Test Stage |
|---|---|
| Requirements Gathering | Acceptance Testing |
| System Design | System Testing |
| Architecture Design | Integration Testing |
| Module Design | Unit Testing |
| Coding | Test Execution |

### 32. What is Agile?

Agile is an iterative software development methodology prioritizing team interaction, rapid feedback, and adaptable evolution over rigid documentation.

Agile Core Values:

✅ Individuals and interactions over processes and tools.

✅ Working software over comprehensive documentation.

✅ Customer collaboration over contract negotiation.

✅ Responding to change over following a plan.

  

# III. VARIABLES

## a. Fundamental Knowledge

-------------------------------------------------------------------------------

### Types of Variables in C++

+ **Local Variable:** Declared within block/function scope; lives on Stack frame during function execution.

+ **Global Variable:** Declared outside functions; lives in static memory (`.data`/`.bss`) throughout program execution lifecycle.

+ **Static Variable:** Retains state across invocations; allocated in static memory. Scope bound to function, class, or translation unit depending on declaration.

+ **Member Variable:** Declared within class body; lifetime bound to parent object instance.

+ **Static Member Variable:** Shared single variable across all class instances; resides in static memory.

+ **Temporary Variable:** Rvalue object generated implicitly by compiler during expressions or implicit type conversions.

+ **Register Variable:** Hint keyword (`register`) requesting CPU register allocation.

+ **Dynamic Variable:** Allocated manually on Heap via `new`/`malloc`; lifetime persists until explicit `delete`/`free`.

+ **Constexpr Variable:** Value evaluated at compile-time; stored in code/rodata static memory.

+ **Thread-local Variable:** Declared with `thread_local`; separate variable instance allocated per thread execution lifecycle.

+ **Extern Variable:** Declares variable symbol defined in another translation unit without allocation.

+ **Mutable Variable:** Keyword `mutable` allows member variable modification inside `const` member functions.

+ **Const Variable:** Immutable variable after initialization.

+ **Volatile Variable:** Prevents compiler optimization caching, enforcing fresh reads from memory address directly on every access.

+ **Auto Variable:** Instructs compiler to automatically deduce type at compile-time based on initialization expression.

  

# IV. POINTERS

## a. Fundamental Knowledge

-------------------------------------------------------------------------------

### 1. Constant Pointer (`int* const ptr`)

• Address stored in pointer cannot change after initialization, but data at target address can be modified.

### 2. Pointer to Constant (`const int* ptr`)

• Data at target address cannot be modified via this pointer, but pointer can be reassigned to another memory address.

### 3. Constant Pointer to Constant (`const int* const ptr`)

• Neither target memory address nor target memory value can be changed.

  

### Main Smart Pointer Types in C++:

1. **`std::unique_ptr`:** Exclusive ownership model; non-copyable, move-only via `std::move`. Automatically deallocates object upon leaving scope. Zero memory overhead.

2. **`std::shared_ptr`:** Shared ownership model using atomic reference counting control block. Deallocates target object when ref-count hits 0.

3. **`std::weak_ptr`:** Non-owning observer reference to `std::shared_ptr` object. Solves cyclic reference memory leaks. Must call `.lock()` to acquire temporary `std::shared_ptr`.

*Best Practice:* Prefer `std::make_unique` and `std::make_shared` for exception safety and allocation efficiency.

  

### Type Casting Types in C++

1. **C-style Cast `(type)value`:** Legacy C cast; performs unsafe brute force cast conversions without safety checks.

2. **`static_cast<>`:** Compile-time checked conversion between compatible types (e.g., numeric types, implicit upcasts).

3. **`dynamic_cast<>`:** Runtime safe downcasting in polymorphic inheritance hierarchies using RTTI metadata. Returns `nullptr` on pointer failure.

4. **`const_cast<>`:** Adds or removes `const` or `volatile` qualifiers.

5. **`reinterpret_cast<>`:** Unsafe low-level bit reinterpretation between unrelated pointer types.

  

## b. Questions

### 1. What is the `this` pointer?

The `this` pointer is an implicit constant pointer available inside non-static class member functions pointing to the calling object instance.

📌 Key Notes:

- `this` is unavailable in static member functions and friend functions.

- Facilitates method chaining by returning `*this`.

- Cannot be reassigned to point to another object.

### 2. Common Pointer Errors in C++:

- **Null Pointer Dereference:** Dereferencing an uninitialized or null pointer (`nullptr`).
```cpp
int* ptr = nullptr;
*ptr = 10; // Crash: Null dereference
```

- **Dangling Pointer:** Accessing memory after it has been deallocated.
```cpp
int* ptr = new int(10);
delete ptr;
*ptr = 20; // Error: Dangling pointer usage
```

- **Memory Leak:** Allocating dynamic dynamic memory without freeing it.
```cpp
int* ptr = new int(10);
ptr = new int(20); // Leak: Previous allocation lost
```

- **Double Delete:** Calling `delete` twice on the same memory pointer address.
```cpp
int* ptr = new int(10);
delete ptr;
delete ptr; // Error: Double free
```

- **Wild Pointer:** Using an uninitialized pointer holding garbage memory address.
```cpp
int* ptr; // Uninitialized
*ptr = 10; // Undefined Behavior
```

- **Accessing Out-Of-Bounds Memory:** Indexing pointer memory beyond allocated buffer size.
```cpp
int arr[3] = {1, 2, 3};
int* ptr = arr;
ptr[3] = 10; // Undefined Behavior
```

### 3. What is a `void` pointer?

A `void*` is a generic pointer pointing to raw memory without concrete type binding. Cannot be dereferenced directly without casting to a concrete pointer type (e.g., via `static_cast<int*>(ptr)`).

### 4. Difference between Reference and Pointer?

- **Pointer:** Variable storing address of another variable; can be null; reassignable; requires `*` operator for dereferencing.

- **Reference:** Immutable alias for existing variable; must be initialized at creation; cannot be null; accessed directly without dereference syntax.

  

# V. STL (STANDARD TEMPLATE LIBRARY)

## a. Fundamental Knowledge

-------------------------------------------------------------------------------

### Main Components of STL:

1. **Containers:** Sequence (`vector`, `deque`, `list`), Associative (`set`, `map`), Unordered (`unordered_set`, `unordered_map`), Adaptors (`stack`, `queue`, `priority_queue`).

2. **Algorithms:** High-performance algorithms (`std::sort`, `std::find`, `std::accumulate`, `std::remove`).

3. **Iterators:** Generalized pointer interface traversing container elements (`input_iterator`, `random_access_iterator`).

4. **Numeric Library:** Mathematical utilities (`accumulate`, `inner_product`).

  

### Container Categories:

- **Sequence Containers:**

  `vector`: Dynamic array, fast random access ($O(1)$).

  `list`: Doubly linked list, fast node insert/delete ($O(1)$).

  `deque`: Double-ended queue.

  `array`: Fixed size array container.

- **Associative Containers:**

  `set`: Unique sorted keys (Red-Black tree, $O(\log N)$).

  `map`: Unique sorted key-value pairs.

- **Unordered Containers:**

  `unordered_set`: Hash table set ($O(1)$ average lookup).

  `unordered_map`: Hash table key-value map.

- **Container Adaptors:**

  `stack` (LIFO), `queue` (FIFO), `priority_queue` (Heap). Adaptors do not expose iterators.

  

## b. Questions

### 1. Compare Array vs Vector?

- **Array:** Fixed size; allocated on stack or statically; zero memory management overhead; no utility methods.

- **Vector:** Dynamic size; heap-allocated buffer; provides rich manipulation APIs (`push_back`, `erase`); capacity reallocation overhead.

### 2. Why use Vector over Array?

Provides dynamic sizing flexibility, safer memory management, automated cleanup, and built-in STL algorithm compatibility.

### 3. Compare Array vs List?

- **Array:** Contiguous memory layout; instant $O(1)$ index access; expensive $O(N)$ insertion/deletion.

- **List:** Non-contiguous linked node memory layout; $O(N)$ sequential search access; fast $O(1)$ node insertion/deletion once target position is reached.

  

======================================================================================

# VII. KEYWORDS & ADVANCED CONCEPTS

## a. Fundamental Knowledge

-------------------------------------------------------------------------------

1. **`static` Keyword:**

   In function: Retains state across invocations.

   In class: Shared single member across all class instances.

   In file scope: Restricts internal linkage to current translation unit.

2. **`const` Keyword:**

   Const variable: Value immutable after initialization.

   Const method: Promises not to modify class member data.

   Const pointer: Protects target data or pointer address from modification.

3. **`volatile` Keyword:**

   Enforces direct memory read/write instructions on every access, disabling compiler optimizations (essential for hardware registers/interrupt flags).

4. **`auto` Keyword:**

   Automatic compile-time type deduction based on initializer expression.

5. **`inline` Keyword:**

   Hints compiler to replace function call site with inline function code body to eliminate call stack frame overhead.

6. **`mutable` Keyword:**

   Allows modifying member variables within `const` member methods.

  

-------------------------------------------------------------------------------

## b. Questions

### 1. What does the Scope Resolution Operator `::` do?

Used to access class static members, namespace members, or explicitly select global scope variables (`::globalVar`).

### 2. What does `volatile` do?

Informs compiler that variable value can change externally outside program control (e.g., hardware sensor, signal handler), preventing optimization caching. Example: `volatile int sensorValue;`.

### 3. What is an Inline function?

A function where the compiler substitutes the function definition directly at every invocation site to save function call stack frame overhead.

### 4. RAII (Resource Acquisition Is Initialization)

RAII is a fundamental C++ idiom tying system resource lifecycles (heap RAM, mutex locks, file descriptors) to object lifecycles. Resources are acquired inside object constructors and guaranteed released inside object destructors even under thrown exceptions.

### 5. Stack Unwinding

Stack Unwinding is the process where the C++ exception handling runtime unwinds stack call frames searching for matching `catch` blocks. During unwinding, destructors of all automatic stack objects in popped frames execute automatically in reverse order of creation (LIFO).

### 6. Preventing Hidden Bugs

Key categories of hidden software bugs:

- **Concurrency & Multithreading Errors:** Race conditions, deadlocks (Rank 1).

- **Resource Management Errors:** Memory leaks, dangling pointers, double frees (Rank 2).

- **Undefined Behavior (UB):** Uninitialized memory access, buffer overflows (Rank 3).

- **Side Effect & Logic Errors** (Rank 4 & 5).

Primary Defensive Lines:

- Clean Code & SOLID principles.

- Static Analysis (Highest compiler warning levels `-Wall -Wextra -Werror`, Clang-Tidy).

- C++ Idioms / Patterns (RAII, Smart Pointers, Thread locks).

- Strict Code Reviews.

- Robust Logging & Stress Load Testing.

  

**