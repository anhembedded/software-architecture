Mình sẽ tạo một file PDF mẫu có đủ các "bẫy" hay gặp (2 cột, header/footer, bảng, từ bị gạch nối), rồi parse thử theo hai cách: thô và đã làm sạch, để bạn so sánh.

Đã tạo xong PDF nguồn, giờ mình xem lại bố cục rồi chạy parse thô và parse sạch.

Bố cục chưa đúng ý: toàn bộ chữ nằm gọn trong cột trái nên chưa có "bẫy 2 cột". Mình thu ngắn chiều cao cột để chữ tràn sang cột phải.

Giờ PDF đã có đủ bẫy, kể cả tiêu đề mục 3 bị mồ côi ở cuối cột trái. Tiếp theo là parse thô và parse sạch.

Mình đã tạo một PDF mẫu 2 trang, cố ý đưa vào các lỗi hay gặp: nội dung 2 cột, header/footer lặp lại, và một bảng có ô gộp. Sau đó parse theo hai cách (3 file đính kèm ở trên). Kết quả parse sạch tốt hơn hẳn nhưng vẫn còn một lỗi thật, mình nói ở cuối.

## So sánh hai cách parse

|               | Parse thô (`parse_tho.txt`)                      | Parse sạch (`parse_sach.md`)           |
| ------------- | ------------------------------------------------ | -------------------------------------- |
| Hai cột       | Đọc ngang qua cả hai cột, câu bị xen kẽ          | Đọc hết cột trái rồi mới sang cột phải |
| Header/footer | Lặp lại ở mỗi trang, nằm lẫn trong nội dung      | Đã bỏ                                  |
| Tiêu đề       | Chỉ là dòng chữ thường                           | Thành `#`/`##`, thấy được cây mục      |
| Bảng          | Thành các dòng chữ, không rõ ô nào thuộc cột nào | Thành bảng Markdown, giữ đúng cột      |
| Metadata      | Không có                                         | Có nguồn, phiên bản, số trang          |

Ví dụ lỗi ở bản thô là đoạn này, hai cột bị trộn thành một câu vô nghĩa:

```
1. Giới thiệu Tên mạng (SSID) nên ngắn gọn, không chứa dấu
Router AX3000 hỗ trợ chuẩn Wi-Fi 6 với hai băng
```

Bảng sau khi parse sạch (hàng đầu):

```
|Nhóm|Thời hạn|Phí đổi mới|Ghi chú|
|Router AX3000|24 tháng|Miễn phí|Đổi mới trong 30 ngày đầu nếu lỗi nguồn|
```

Nếu đưa bản thô vào RAG, một câu hỏi như "Router AX3000 bảo hành bao lâu?" rất dễ lấy nhầm chunk hoặc đọc sai số liệu.

## Lỗi còn sót trong bản "sạch"

Tiêu đề **"3. Đặt tên mạng Wi-Fi"** nằm mồ côi ở cuối cột trái, còn nội dung mục 3 nằm đầu cột phải. Parser đã xử lý sai: nội dung mục 3 bị dính vào mục 2, còn tiêu đề mục 3 bị đẩy xuống sau mục 4. Hậu quả là một chunk có thể mang nhầm ngữ cảnh. Đây là lý do mình nhấn mạnh phải **tự đọc lại kết quả parse**, vì không có lỗi nào báo ra.

## Cách làm

- **Công cụ:** PyMuPDF4LLM để trích text theo layout, thêm vài dòng Python để làm sạch.
- **Làm sạch:** bỏ header/footer bằng regex, chuẩn hóa Unicode NFC, gắn metadata đầu file và số trang.
- **Chưa kiểm chứng:** bước nối từ bị gạch nối cuối dòng có trong script, nhưng file mẫu không có trường hợp này nên chưa được thử.
- **Lưu ý khi áp dụng:** regex bỏ header/footer ở đây viết riêng cho file mẫu, tài liệu thật cần chỉnh lại cho khớp.

Bạn có thể đưa một PDF thật của mình (hoặc một vài trang đại diện) để mình chạy cùng pipeline, so sánh vài parser khác nhau rồi chọn cái hợp nhất.