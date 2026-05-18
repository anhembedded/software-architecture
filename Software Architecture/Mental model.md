## Hầu hết phần mềm đều có bốn loại mối quan tâm cơ bản:

|Concern|Bản chất|
|---|---|
|Tương tác với người dùng|Presentation|
|Điều phối use case|Application|
|Rule nghiệp vụ|Domain|
|Giao tiếp thế giới ngoài|Infrastructure|

## Bước 1 — Nhìn system pressure trước

Hệ thống này chủ yếu bị chi phối bởi cái gì?

- UI complexity?
- concurrency?
- data throughput?
- real-time constraint?
- hardware coupling?
- distributed consistency?

---

## Bước 2 — Chọn lens phù hợp

Không phải lúc nào cũng dùng Clean Architecture lens.

### Nếu là business app

→ 4-layer lens rất mạnh
### Nếu là real-time embedded

→ thường dùng:

- control loop lens
- timing lens
- ISR/task model

### Nếu là data platform

→ thường dùng
- pipeline lens
- streaming/batch lens
    

---

🔥 **Insight quan trọng:**

> Architect giỏi không có một framework nhìn đời.  
> Họ có nhiều “lens” và chọn đúng cái cho bài toán.