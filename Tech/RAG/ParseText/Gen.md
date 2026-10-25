# Parse thành text sạch: nghĩa là gì và làm thế nào

## Ý nghĩa

Tài liệu gốc (PDF, Word, HTML, ảnh scan...) được thiết kế cho **mắt người đọc**, không phải cho máy. "Parse" là chuyển nó thành text mà máy dùng được. "Sạch" nghĩa là:

- **Đúng thứ tự đọc** (không trộn dòng giữa các cột)
- **Giữ cấu trúc**: heading, list, bảng (thường xuất ra Markdown)
- **Bỏ rác**: header/footer lặp lại, số trang, menu web, mục lục
- **Gắn metadata**: tên file, số trang, mục, phiên bản, để sau này trích dẫn nguồn

Nếu bước này sai thì các bước sau (chunk, embedding, LLM) đều xử lý trên dữ liệu hỏng, và không có prompt nào cứu được. Nguyên tắc là "rác vào, rác ra".

## Phương pháp theo loại nguồn

| Loại nguồn                                     | Cách làm                                                       | Công cụ thường dùng                                                                                   |
| ---------------------------------------------- | -------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------- |
| PDF có text layer, bố cục đơn giản             | Trích text trực tiếp                                           | PyMuPDF, pdfplumber, pypdf                                                                            |
| PDF bố cục phức tạp (nhiều cột, bảng, heading) | Parser nhận diện layout, xuất Markdown                         | Docling, Marker, MinerU, Unstructured, PyMuPDF4LLM                                                    |
| PDF scan / ảnh                                 | OCR (thường kèm layout analysis)                               | Tesseract, PaddleOCR; dịch vụ cloud như Azure Document Intelligence, AWS Textract, Google Document AI |
| Trang phức tạp (bảng lồng, biểu đồ, sơ đồ)     | Đưa ảnh trang cho model thị giác (VLM) chép lại thành Markdown | Claude/GPT/Gemini vision, LlamaParse                                                                  |
| Word / PowerPoint                              | Đọc cấu trúc trực tiếp từ file                                 | python-docx, mammoth, pandoc, python-pptx                                                             |
| HTML / web                                     | Trích phần nội dung chính, bỏ menu/quảng cáo                   | trafilatura, readability, BeautifulSoup + markdownify                                                 |
| Code                                           | Cắt theo cấu trúc cú pháp (hàm, class)                         | tree-sitter                                                                                           |

Các công cụ này thay đổi rất nhanh, nên trước khi chọn hãy kiểm tra phiên bản và đánh giá mới nhất.

**Cách chọn nhanh:** bắt đầu bằng parser rẻ và nhanh nhất. Lấy 10-20 trang đại diện (có bảng, nhiều cột, scan), chạy 2-3 công cụ, **so sánh bằng mắt**, rồi chọn. Chỉ dùng VLM cho những trang parser thường làm hỏng, vì nó chậm, đắt, và cũng có thể bịa chữ.

## Template quy trình

```
1. Ingest       → phát hiện loại file (PDF text / scan / docx / html)
2. Extract      → chọn parser theo loại, xuất Markdown + thông tin từng trang
3. Clean        → bỏ header/footer lặp, số trang, nối từ bị gạch nối cuối dòng,
                  chuẩn hóa Unicode (NFC) và khoảng trắng
4. Structure    → giữ cây heading (H1 > H2 > H3), bảng thành Markdown/HTML
5. Enrich       → gắn metadata: source, page, section, version, ngày
6. Validate     → kiểm tra mẫu: độ dài bất thường, ký tự lỗi, trang rỗng
7. Cache        → lưu kết quả parse ra file, không parse lại mỗi lần
```

Ví dụ đầu ra mỗi khối nội dung:

```json
{
  "text": "## 3.2 Cấu hình\nNội dung...",
  "source": "manual_v2.pdf",
  "page": 14,
  "section": "3.2 Cấu hình",
  "type": "text"   // text | table | figure | code
}
```

Ví dụ tối giản với Docling (kiểm tra lại API theo phiên bản bạn cài):

```python
from docling.document_converter import DocumentConverter

result = DocumentConverter().convert("manual.pdf")
markdown = result.document.export_to_markdown()
```

## Pain points chính

1. **Bảng**: ô gộp, bảng kéo dài qua nhiều trang, bảng không có đường kẻ. Đây là điểm hỏng nhiều nhất, và hậu quả là LLM đọc sai số liệu.
2. **Nhiều cột**: parser đọc ngang qua các cột nên câu bị trộn lẫn.
3. **Hình, biểu đồ, sơ đồ**: thông tin nằm trong ảnh nên parser text bỏ qua hoàn toàn. Cần mô tả bằng VLM hoặc chấp nhận bỏ.
4. **PDF scan**: OCR sai chữ, đặc biệt với ảnh mờ, chữ nhỏ, hoặc ký tự đặc biệt.
5. **Header/footer/số trang** chen vào giữa câu, làm chunk bị nhiễu và bị trùng lặp.
6. **Thứ tự đọc sai**: chú thích, sidebar, footnote bị chèn vào giữa đoạn chính.
7. **Tiếng Việt**: dấu bị tách rời (NFC/NFD), font nhúng lỗi mã hóa nên copy ra ký tự rác, OCR hay sai dấu. Nên chuẩn hóa Unicode NFC và kiểm tra riêng với tiếng Việt.
8. **Mất cấu trúc heading**: không biết đoạn thuộc mục nào, nên chunk mất ngữ cảnh. Nên giữ đường dẫn heading làm metadata.
9. **Công thức, ký hiệu đặc biệt**: bị biến thành ký tự lạ.
10. **Trùng lặp và nhiều phiên bản** của cùng một tài liệu làm retrieval trả về thông tin cũ lẫn mới.
11. **Chi phí và tốc độ**: parser dùng model hoặc VLM chậm và đắt khi kho tài liệu lớn.

## Lời khuyên thực tế

- **Luôn mở file đã parse ra đọc thử**, đừng tin mà không kiểm tra. Đây là việc đáng thời gian nhất.
- **Giữ số trang và nguồn** ngay từ bước parse để sau này trích dẫn được.
- **Xử lý bảng riêng**: xuất ra Markdown/HTML, hoặc cho LLM tóm tắt bảng thành câu mô tả để dễ tìm hơn.
- **Cache kết quả parse**, vì parse tốn thời gian và bạn sẽ chỉnh chunking nhiều lần.
- **Đừng cố hoàn hảo ngay**: parse đủ tốt, rồi đo retrieval để xem lỗi parse nào thật sự ảnh hưởng, và chỉ sửa những lỗi đó.

Nếu bạn cho mình biết loại tài liệu chính (PDF scan hay PDF gốc, nhiều bảng hay không, tiếng Việt hay tiếng Anh), mình sẽ gợi ý công cụ phù hợp nhất để thử đầu tiên.