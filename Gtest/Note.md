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

