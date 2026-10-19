Ví dụ này rất hay vì nó cho thấy cách áp dụng tư duy "khảo sát theo nhiều lớp" vào một dự án AI thực tế.

Giả sử sếp giao:

> "Xây dựng một hệ thống RAG để team có thể hỏi đáp nhanh về tài liệu dự án."

Nếu là người mới thường sẽ nghĩ:

- Học LangChain
- Học RAG
- Học ChromaDB
- Học Vector DB
- Học Embedding

Nhưng theo tư duy trong bài viết, chưa nên làm vậy.

---

# Layer 1: System Context

Câu hỏi:

> Hệ thống này tồn tại để giải quyết vấn đề gì?

Ví dụ:

Hiện tại team có:

- 500 file requirement
- 300 file design
- Hàng ngàn trang wiki
- Source code C++

Mỗi lần cần tìm:

> "Module A gửi message gì sang Module B?"

phải mất 30 phút đọc tài liệu.

Problem statement:

```
Giảm thời gian tìm kiếm thông tin kỹ thuật.
```

Lúc này mới hỏi tiếp:

### Ai là user?

- Dev?
- Tester?
- PM?
- Customer support?

### Họ hỏi gì?

Ví dụ:

```
"What is the startup sequence of ECU Manager?"
```

hoặc

```
"Which module publishes VehicleSpeed?"
```

---

# Layer 2: Architecture

Sau khi biết bài toán.

Mới khảo sát kiến trúc.

RAG tổng thể gồm gì?

```
Documents
     ↓
Chunking
     ↓
Embedding
     ↓
Vector DB
     ↓
Retriever
     ↓
LLM
     ↓
Answer
```

Lúc này chưa cần học code.

Chỉ cần hiểu:

### Data Flow

```
pdf/docx/wiki
      ↓
ingestion pipeline
      ↓
vector database
      ↓
retrieval
      ↓
prompt
      ↓
LLM answer
```

### Các component

- Document Loader
- Chunker
- Embedding Model
- Vector DB
- Retriever
- LLM

---

# Layer 3: Implementation

Lúc này mới đào sâu.

Ví dụ task của bạn là:

> Import tài liệu dự án vào RAG

Thì cần nghiên cứu:

### Entry Point

```
ingest.py
```

### Loader

```
PDFLoader
DirectoryLoader
```

### Chunking

```
RecursiveCharacterTextSplitter
```

### Embedding

```
bge-m3
text-embedding-3-large
```

### Vector Database

```
FAISS
Qdrant
Chroma
Milvus
```

Lưu ý:

Bạn chưa cần hiểu fine-tuning.

Bạn chưa cần hiểu agent.

Bạn chưa cần hiểu multi-agent.

Vì nó chưa liên quan bài toán.

Đây là ý:

> Learn what intersects with your problem.

---

# Layer 4: Build & Verification

Senior thường sẽ khảo sát phần này rất sớm.

Ví dụ:

### Build

Docker?

```
docker compose up
```

hay

Kubernetes?

### Deploy

- Local PC?
- Server?
- Azure?
- AWS?

### Test

Làm sao biết RAG hoạt động?

Ví dụ benchmark:

Q1

```
Startup sequence gồm những bước nào?
```

Q2

```
Signal VehicleSpeed được publish từ đâu?
```

Q3

```
Watchdog timeout là bao nhiêu?
```

RAG trả lời đúng ≥80%?

Hay ≥90%?

Đây mới là acceptance criteria.

---

# Tiếp theo là bước De-risk

Một senior sẽ hỏi:

## Risk 1

Tài liệu có đủ chất lượng không?

Ví dụ:

```
PDF scan
```

OCR lỗi.

=> RAG vô dụng.

---

## Risk 2

Context có quá dài không?

Ví dụ:

```
1000-page software architecture
```

LLM không đọc hết.

---

## Risk 3

Embedding model có hiểu tài liệu kỹ thuật không?

Ví dụ:

```
AUTOSAR
CAN
SOME/IP
UDS
```

Embedding tổng quát có thể retrieval rất kém.

---

## Risk 4

Source code có cần query không?

Người dùng hỏi:

```
Where is VehicleSpeed generated?
```

Nếu chỉ index document thì không đủ.

Có thể phải index cả source:

```
C++
XML
ARXML
```

---

# Một Spike tốt cho dự án này

Thay vì học hết RAG.

Senior thường làm:

### Question

"Liệu RAG có tìm được thông tin từ tài liệu ECU không?"

### Spike

Lấy:

```
10 file PDF
```

↓

Chunk

↓

FAISS

↓

Embedding

↓

LLM

↓

Test 20 câu hỏi thực tế

### Success Criteria

```
>= 80% câu trả lời tìm đúng document
```

Nếu spike thất bại:

- đổi chunk size
- đổi embedding model
- đổi retrieval strategy

Trước khi build toàn bộ hệ thống.

---

Nếu nhìn dưới góc "quản lý bất định", ngày đầu nhận task RAG mình sẽ không hỏi:

> "Nên dùng LangChain hay LlamaIndex?"

Mà sẽ hỏi:

> "Tài liệu hiện tại có đủ chất lượng để retrieval không?"

Vì nếu câu trả lời là **không**, thì mọi quyết định kỹ thuật phía sau gần như đều vô nghĩa. Đó chính là tư duy **de-risk trước, code sau** mà bài viết đang nhấn mạnh.