
## Khi giải thích một khái niệm

* "In simple terms, ..."
* "Basically, ..."
* "The main idea is that ..."
* "You can think of it as ..."
* "From my understanding, ..."

---
## Khi mô tả cách hoạt động

* "When this happens, ..."
* "At this point, ..."
* "As a result, ..."
* "After that, ..."
* "Eventually, ..."

> The memory is allocated on the heap. After that, the function returns a pointer to the allocated block.

---

## Khi so sánh

* "The difference between A and B is that ..."
* "Unlike A, B ..."
* "Compared to A, B ..."
* "On the other hand, ..."

> Unlike stack memory, heap memory must be managed manually.

---

## Khi nêu ưu điểm

* "One advantage is that ..."
* "The benefit of this approach is ..."
* "This allows us to ..."
* "This improves ..."

> One advantage of using a circular buffer is that it avoids frequent memory allocations.

---

## Khi nêu nhược điểm

* "The downside is that ..."
* "The trade-off is ..."
* "However, this comes at the cost of ..."

> The trade-off is increased memory usage.

---

## Khi nói về kinh nghiệm cá nhân

* "In my previous project, ..."
* "I've worked with ..."
* "I've implemented ..."
* "I've encountered ..."
* "I've dealt with ..."

> I've implemented several UART drivers in Embedded Linux systems.

---

## Khi không chắc chắn 100%

* "If I remember correctly, ..."
* "As far as I know, ..."
* "I believe ..."
* "I'm not completely sure, but ..."

> As far as I know, dereferencing a null pointer results in undefined behavior.

---
## Khi suy nghĩ trong lúc trả lời

* "Let me think for a second."
* "If I understand correctly, ..."
* "Let me walk through it step by step."

> Let me walk through it step by step. First, the pointer is initialized to NULL...

---

## Khi giải thích nguyên nhân lỗi

* "The root cause is ..."
* "This issue occurs because ..."
* "The problem comes from ..."
* "One possible reason is ..."

> This issue occurs because the pointer is being used after the memory has been freed.

---

## Khi mô tả quá trình debug

* "The first thing I would check is ..."
* "To diagnose the issue, ..."

> I would start by checking whether the pointer is valid before it is dereferenced.

---

## Khi trả lời các câu hỏi thiết kế phần mềm

* "My approach would be ..."
* "I would separate the system into ..."
* "I would use ... because ..."
* "The goal is to ..."
* "To make the code maintainable, ..."

> My approach would be to separate the hardware abstraction layer from the application layer.

---

## Các cụm từ rất hay dùng trong Embedded Interview

* Hardware abstraction layer (HAL)
* Device driver layer
* Real-time constraints
* Resource-constrained environment
* Low-level programming
* Bare-metal system
* Interrupt-driven design
* Event-driven architecture
* State machine approach
* Memory footprint
* CPU utilization
* Timing requirements
* Communication protocol
* Synchronization mechanism
* Error handling strategy
* Scalability and maintainability

> The system runs in a resource-constrained environment, so memory footprint is an important consideration.

---

## Mẫu trả lời cực kỳ hữu dụng

> From my understanding, the main difference between stack and heap memory is that stack allocation is managed automatically, while heap allocation is managed manually by the programmer. One advantage of heap memory is flexibility. However, the downside is that it may lead to memory leaks if not handled properly. In my previous project, I used dynamic allocation for large data buffers because the stack size was limited.
