
> [!abstract]  
> Rất nhiều dev nhầm lẫn giữa hai khái niệm này.  
> Chúng có liên quan với nhau nhưng tồn tại ở **hai tầng trừu tượng hoàn toàn khác nhau**.

---

# 1️⃣ 🎯 Design Pattern là gì?

> [!info]  
> Giải pháp tái sử dụng cho vấn đề thiết kế ở mức **class/object**.

## 📚 Nguồn gốc

- _Design Patterns: Elements of Reusable Object-Oriented Software_
- Erich Gamma và nhóm “Gang of Four”
## 🔍 Đặc điểm chính

- Giải quyết vấn đề ở mức code
- Thường nằm trong 1 module / 1 service
- Tập trung vào:
    - Object creation
    - Object interaction
    - Decoupling class
## 🧩 Ví dụ Design Pattern quen thuộc

- Singleton
- Factory
- Observer
- Strategy
- Decorator
- Adapter
- Repository
- Command

## 💻 Ví dụ đơn giản

```cpp
class PaymentStrategy {
public:
    virtual void pay() = 0;
};

class CreditCardPayment : public PaymentStrategy {};
class CryptoPayment : public PaymentStrategy {};
```

→ Đây là **Strategy Pattern**.

> [!tip]  
> Nó không quyết định hệ thống chạy thế nào.  
> Nó chỉ quyết định object tương tác thế nào.

---

# 2️⃣ 🏛️ Software Architecture Pattern là gì?

> [!important]  
> Mẫu tổ chức hệ thống ở mức cao (**system-level**).

## 🔧 Nó quyết định:

- Cách chia hệ thống
- Cách service giao tiếp
- Cách deploy
- Cách scale
- Cách xử lý dữ liệu

## 🧱 Ví dụ Architecture Pattern

- Layered Architecture
- Clean Architecture
- Hexagonal Architecture
- Microservices
- Event-Driven Architecture
- CQRS
- Monolith

> [!example]  
> Ví dụ: Một hệ thống lớn có thể dùng Microservices + Event Streaming.

---

# 3️⃣ ⚖️ So sánh trực tiếp

|Tiêu chí|Design Pattern|Architecture Pattern|
|---|---|---|
|Phạm vi|Class / Object|Toàn hệ thống|
|Quyết định bởi|Developer|Architect|
|Ảnh hưởng|Local|Global|
|Thay đổi|Dễ|Rất tốn kém|
|Ví dụ|Strategy, Factory|Microservices, Layered|

---

# 4️⃣ 🧠 Ví dụ thực tế (Hệ thống Trading)

## 🏗️ Tầng Architecture

SA quyết định:

- Monolith hay Microservices?
- Event-driven hay synchronous?
- Có dùng CQRS không?

Giả sử chọn:

> **Microservices + Event-Driven**

→ Đây là **Architecture Pattern**.

---

## 🧩 Bên trong mỗi service

Developer implement:

- Repository pattern
- Factory pattern
- Strategy pattern
- Observer pattern

→ Đây là **Design Pattern**.

---

# 5️⃣ 🔗 Mối quan hệ giữa chúng

> [!quote]  
> Architecture Pattern = Bản đồ thành phố  
> Design Pattern = Cách xây từng ngôi nhà

## 🔬 Góc nhìn kỹ thuật

- Architecture pattern tạo ra **constraints**.
- Design pattern vận hành **bên trong constraints đó**.

### Ví dụ:

- Microservices → phải nghĩ về eventual consistency
- Event-driven → dùng Observer pattern rất nhiều
- Clean Architecture → thường dùng Dependency Injection pattern

---

# 6️⃣ ⚙️ Góc nhìn Embedded

Nếu bạn làm embedded:

## 🏛️ Architecture Pattern giống như:

- Chọn RTOS hay bare-metal
- Chọn event loop hay polling
- Chọn modular firmware hay single file

## 🧩 Design Pattern giống như:

- State machine
- Strategy cho driver
- HAL abstraction
- Interface class

---

# 7️⃣ 🚨 Một sự thật quan trọng

Junior dev thường:  
→ Tập trung design pattern

Senior / Architect:  
→ Tập trung architecture pattern

> [!warning]  
> Nếu thiếu design pattern tốt  
> → Architecture đẹp vẫn trở thành “big ball of mud”.

---

# 8️⃣ 🎯 Tóm lại

## Design Pattern

- Giải quyết **micro-level complexity**

## Architecture Pattern

- Giải quyết **macro-level complexity**

> [!success]  
> Chúng không thay thế nhau.  
> Chúng bổ sung cho nhau để kiểm soát độ phức tạp của phần mềm.

---

# 🏷️ Tags

#software-architecture  
#design-pattern  
#system-design  
#clean-architecture  
#engineering-thinking