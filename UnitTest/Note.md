## 1️⃣ Google Mock có mock được static function không?

Câu trả lời ngắn gọn:

👉 **Không.**

Framework như  
**Google Mock**  
chỉ mock được:

- virtual method
- interface method

Nó **không intercept được static function** vì static không polymorphic.


---

## Vậy singleton có thật sự phá testability không?

Câu trả lời tinh tế là:

🔹 Nếu singleton bị gọi bên trong business logic → phá testability  
🔹 Nếu singleton chỉ nằm ở system wiring (composition root) → không sao


---

Trong clean architecture (áp dụng cho embedded luôn), ta có khái niệm:

> Composition Root  
> → nơi duy nhất tạo object và nối dependency

Trong firmware, chỗ đó thường là:

- `main()`
- hoặc một hàm như `SystemInit()`
- hoặc một AppBuilder
---
# 🧠 Giờ mình giúp bạn hoàn thiện 3 flow bạn chưa từng nghĩ tới

Bạn nói chưa từng biết “wiring flow”.  
Giờ mình build cho bạn rõ ràng.

---

## ✅ 1️⃣ Production Wiring Flow

Trong production:

1. `main()` (composition root) tạo **real hardware instance**
2. `main()` inject dependency vào module
3. System bắt đầu chạy loop

Ví dụ tư duy:

main()  
 ├── create GpioSTM32  
 ├── create MotorController(gpio)  
 └── start system

Không có factory trong business logic.  
Factory (nếu có) chỉ được gọi ở main.

---

## ✅ 2️⃣ Test Wiring Flow

Trong test:

1. Test tạo **MockGpio** (Google Mock)
2. Inject vào MotorController
3. Verify interaction

test()  
 ├── create MockGpio  
 ├── create MotorController(mock)  
 └── EXPECT_CALL(...)

Production wiring và test wiring **khác nhau hoàn toàn**,  
nhưng MotorController không thay đổi 1 dòng code.

---

## ✅ 3️⃣ Vai trò thật sự của Factory

Factory chỉ nên dùng để:

- Tạo concrete implementation
- Ẩn chi tiết platform (STM32, Linux, Fake, v.v.)

Nhưng:

🚨 Factory không được:

- Được gọi bên trong business logic
- Biến thành service locator
- Trở thành singleton toàn hệ thống

---

Class nào nên được unit test? 
	Đó là các class chưa business logic
Class nào chỉ cần integration test?
	Là các class config và init.

---
Vậy là sao phân biệt cái nào là business logic cái nào chỉ là wiring

---
Nếu wiring chứa logic:

- Nó trở thành **application layer**
- Nhưng lại thường **không được test kỹ**
- Và đó là nơi bug nguy hiểm nhất xuất hiện

---

## Tổng kết kiến trúc testable embedded ở mức senior

## 1️⃣ Business logic module

- Unit test bằng **Google Test**
- Mock dependency bằng **Google Mock**
- Không biết hardware concrete tồn tại

## 2️⃣ Hardware implementation

- Không unit test theo kiểu logic
- Có thể test driver level riêng
- Không dính vào business rule

## 3️⃣ Composition root (main / AppBuilder)

- Chỉ tạo object
- Chỉ inject dependency
- Không chứa rule
- Không decision

## 4️⃣ Application layer (nếu có orchestration)

- Có logic → phải test
- Có thể test bằng integration test
- Không nên trộn với wiring