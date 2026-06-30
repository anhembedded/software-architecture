mỗi loại tri thức đều cần được “chế biến” bằng một công cụ (tool) để trở thành dạng có thể index và truy xuất được**. Nhưng không có nghĩa là mỗi loại cần một tool riêng biệt hoàn toàn — mà là chúng ta dùng **một bộ công cụ chung**, chỉ điều chỉnh cách xử lý đầu vào.

---

## Cụ thể: tool nào cho việc gì?

### 🔧 Tool chung cho **tất cả** các loại tri thức văn bản (Mã nguồn, Quy ước, Tài liệu thiết kế, Ví dụ mẫu)
**Chức năng:** Load dữ liệu → Chia nhỏ (chunk) → Tạo embedding → Lưu vào VectorDB.

- **Load dữ liệu:** LangChain/LlamaIndex có sẵn loader cho code, markdown, text, thậm chí PDF.
- **Chia nhỏ (chunk):** Dùng `RecursiveCharacterTextSplitter` hoặc custom splitter.
- **Tạo embedding:** OpenAI Embedding hoặc HuggingFace (local).
- **Lưu trữ:** Chroma, Qdrant, LanceDB…

**Vậy tức là:**  
Một script duy nhất có thể quét tất cả file `.ts`, `.md`, `.yaml`… và ném vào cùng một VectorDB.  
Khi truy xuất, ta dùng **semantic search** cho tất cả.

### 🔧 Tool bổ sung cho **Mã nguồn** – Code Graph / AST (tra cứu chính xác)
Vì code có **quan hệ cấu trúc** (hàm A gọi hàm B, class kế thừa…), chỉ semantic search có thể thiếu chính xác.  
Ta cần thêm một “tool” để:
- Parse code ra AST (dùng `tree-sitter`).
- Lưu các định danh và quan hệ vào graph (dạng SQLite, NetworkX, hoặc SCIP index).
- Truy vấn: “Hàm `authenticate` nằm ở file nào?”, “Những nơi nào gọi `UserService`?”.

### 🔧 Tool cho **API spec** – hơi đặc biệt nhưng vẫn dùng chung nền tảng
- Load file OpenAPI/GraphQL.
- Dùng parser (có thể tự viết hoặc thư viện `openapi-schema-parser`) để cắt thành từng endpoint/field.
- Cho vào VectorDB kèm metadata (`method`, `path`).  
=> Vẫn là VectorDB, chỉ là cách chia nhỏ khác đi một chút.

---

## Tổng kết: Cần những tool gì?

| Công cụ | Mục đích | Áp dụng cho |
|--------|---------|------------|
| **VectorDB** (Chroma, Qdrant) | Lưu và tìm kiếm ngữ nghĩa | Tất cả các loại tri thức |
| **Embedding model** | Chuyển văn bản thành vector | Tất cả |
| **Chunker / Text Splitter** | Cắt nhỏ văn bản thành chunk có ý nghĩa | Tất cả |
| **AST parser (tree-sitter, SCIP)** | Xây dựng code graph để truy vấn cấu trúc | Chỉ mã nguồn |
| **OpenAPI/GraphQL parser** | Tách API spec thành từng endpoint | Chỉ API spec |

Vậy không cần tới 6 tool riêng biệt cho 6 loại tri thức, mà thực tế chỉ cần:
- **1 pipeline xử lý văn bản chung** (load, chunk, embed, lưu VectorDB).
- **1 công cụ graph riêng cho code** (để nắm quan hệ chính xác).

Và toàn bộ có thể gói gọn trong một dự án Python nhỏ, không hề phức tạp như danh sách có vẻ rời rạc.

Nếu bạn muốn, mình sẽ vẽ kiến trúc tổng thể của **bộ tool này** để bạn thấy bức tranh rõ hơn.