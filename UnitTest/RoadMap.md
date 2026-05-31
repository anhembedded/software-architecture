
---

Giờ mình định hướng trước để bạn thấy big picture.

## 🎯 Mục tiêu khi học GTest/GMock (đúng cho embedded)

Bạn KHÔNG chỉ học syntax.

Bạn cần đạt 4 level:

1. Viết test cho pure logic module
2. Isolate hardware layer bằng mock
3. Thiết kế code để test được (testable architecture)
4. Integrate test vào CI

---

# 🧭 Roadmap học GTest + GMock cho Embedded Dev

Mình chia thành 5 Phase.

---

# 🥇 Phase 1 – Master Google Test (1–2 tuần)

Framework: **Google Test**

### Mục tiêu:

- Viết test sạch, readable
- Biết fixture, parameterized test
- Biết tổ chức test suite

### Bạn phải nắm chắc:

- TEST vs TEST_F
- ASSERT vs EXPECT
- Test Fixture
- SetUp / TearDown
- Parameterized test
- Test filtering
- Custom matcher cơ bản

---

### 🎯 Bài tập nên làm

- Viết test cho:
    - Circular buffer
    - PID controller
    - State machine đơn giản

💡 Tip embedded mindset:  
Không test private function.  
Chỉ test public behavior.

---

# 🥈 Phase 2 – Google Mock (2 tuần)

Framework: **Google Mock**
Đây mới là phần quan trọng với embedded.

---

## Mục tiêu

- Mock interface hardware
- Verify interaction
- Expect call order
- Simulate error

---

### Bạn phải master:

- MOCK_METHOD
- EXPECT_CALL
- ON_CALL
- Return(), Invoke()
- Times()
- InSequence

---

### Embedded Application

Giả sử bạn có:

```
class IADC {
   virtual int Read() = 0;
};
```

Bạn sẽ mock ADC để test control algorithm.

---

### 🎯 Bài tập thực chiến

1. Mock UART driver
2. Mock Flash storage
3. Mock Sensor interface
4. Mock HAL layer

---

Câu hỏi cho bạn:

👉 Trong firmware của bạn, layer nào là khó test nhất hiện tại?

---

# 🥉 Phase 3 – Design for Testability (Quan trọng nhất)

Đây là phần nâng level kiến trúc.

Bạn phải:

- Bỏ singleton
- Bỏ global
- Dùng dependency injection
- Tách HAL khỏi logic

---

Áp dụng pattern:

- Interface-based design
- Dependency inversion
- Layered architecture

Nếu bạn từng học MVP thì đây chính là mindset tương tự.

---

# 🏗 Phase 4 – Cross-compile & Embedded Integration

Vấn đề thực tế:

- Test chạy trên host
- Firmware chạy trên ARM

Bạn phải hiểu:

- Build test target riêng
- Tách production code và test code
- CMake integration

---

# 🚀 Phase 5 – Advanced

Sau khi vững:

- Death test
- Custom matcher
- Test performance
- Fake vs Mock strategy
- Property-based test

---

# 🧠 Embedded-specific mindset

Đừng biến GMock thành cái bẫy.

Trong embedded:

- Mock hardware → OK
- Mock logic class → thường sai design

---

Giờ mình muốn bạn tự suy nghĩ 1 chút:

👉 Nếu bạn có 1 class `MotorController`  
nó đang gọi trực tiếp `HAL_GPIO_WritePin`

Theo bạn:

- Vấn đề testability nằm ở đâu?
- Bạn sẽ sửa design thế nào để test được?

Trả lời suy nghĩ của bạn trước.  
Mình sẽ dựa vào đó mà build roadmap sát với level của bạn.