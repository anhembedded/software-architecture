

# Hướng dẫn xây dựng Knowledge Base cho AI Workflow sinh mã nguồn

## 1. Knowledge Base là gì trong ngữ cảnh này?

KB không chỉ là một tập tài liệu tĩnh. Nó là **toàn bộ ngữ cảnh** cần thiết để AI (LLM) sinh ra code **đúng chuẩn dự án hiện tại**, không bịa đặt API, không phá vỡ kiến trúc, tuân thủ convention của team.

KB bao gồm:

- **Mã nguồn hiện có** (đã được index để tìm kiếm ngữ nghĩa).
- **Database schema**, API specs (OpenAPI/Swagger), GraphQL schema.
- **Quy ước code**: cách đặt tên, cấu trúc thư mục, pattern (Repository, DI, …).
- **Tài liệu thiết kế**: kiến trúc tổng thể, lý do chọn công nghệ.
- **Ví dụ code mẫu** (few‑shot examples) cho từng loại tác vụ.

Khi nhận yêu cầu “thêm API đăng ký”, hệ thống sẽ truy xuất KB để lấy:

- Cách project đang định nghĩa model User.
- Middleware auth hiện tại.
- Cấu trúc response chuẩn (success/error).
- Đoạn code controller tương tự đã có.

Rồi chèn các thông tin đó vào prompt cho LLM.

---

## 2. Các loại tri thức và cách xử lý

| Loại tri thức | Dạng dữ liệu | Phương pháp index | Cách truy xuất |
|---------------|--------------|-------------------|----------------|
| Mã nguồn | File `.ts`, `.py`, `.go`... | Chunk theo function/class + embedding | Semantic search (vector) |
| | | AST → graph quan hệ (import, gọi hàm) | Tra cứu chính xác (code graph) |
| Database schema | SQL, migration file, ORM models | Chunk theo bảng, embedding mô tả | Semantic search |
| API spec | OpenAPI JSON/YAML, GraphQL SDL | Parse thành các endpoint, field → chunk | Semantic search + filter by path |
| Quy ước code | Markdown, text (ví dụ: `CONTRIBUTING.md`, `.cursorrules`) | Toàn bộ file hoặc chunk theo chủ đề | Semantic search |
| Tài liệu thiết kế | Markdown, PDF (đã trích xuất text) | Chunk + embedding | Semantic search |
| Ví dụ code mẫu | Đoạn code ngắn kèm mô tả | Chunk + embedding, gắn tag | Semantic search + tag filter |

---

## 3. Lưu trữ KB – Hai trụ cột chính

### a) Vector Database (tìm kiếm ngữ nghĩa)
Quy trình:
```
Văn bản → Chunk (chia nhỏ) → Embedding (vector) → Lưu vào VectorDB (Chroma, Qdrant, Pinecone...)
```
- **Chunk**: cần đủ ngữ nghĩa, thường từ 200–1000 token. Với code, có thể chunk theo function/class dùng AST.
- **Embedding model**: OpenAI `text-embedding-3-small`, `all-MiniLM-L6-v2` (local, free).
- **Metadata**: lưu kèm mỗi chunk: `source_file`, `language`, `type` (code, doc, spec), `function_name`, `class_name`... để filter.

### b) Code graph / AST (truy vấn chính xác)
Dùng khi cần biết chính xác:
- Hàm `createUser` được định nghĩa ở file nào?
- Những module nào import `AuthService`?
- Endpoint `POST /api/users` gọi tới controller nào?

Công cụ:
- **tree-sitter**: parse code ra AST, lưu vào cấu trúc đồ thị (nodes, edges).
- **SCIP (Sourcegraph Code Intelligence Protocol)**: định dạng chuẩn cho index code chính xác.
- **Sourcegraph** tự xây code graph; bạn có thể dùng thư viện như `scip-python`, `scip-typescript` để index offline.

Bạn có thể kết hợp cả hai: đầu tiên truy xuất ngữ nghĩa bằng vector search, sau đó dùng code graph để lấy chính xác định nghĩa và các tham chiếu.

---

## 4. Xây dựng pipeline index Knowledge Base

Chúng ta sẽ dùng Python + LangChain / LlamaIndex vì tính linh hoạt và hệ sinh thái mạnh. Ví dụ dưới đây dùng **LangChain** và **ChromaDB** (local, dễ cài).

### 4.1. Cài đặt
```bash
pip install langchain langchain-community chromadb openai tiktoken
# Nếu muốn dùng model embedding local
pip install sentence-transformers
```

### 4.2. Index source code
Tạo script quét tất cả file code, chia thành chunk theo function, tạo embedding và lưu.

```python
import os
from langchain_community.document_loaders import TextLoader
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain_community.embeddings import OpenAIEmbeddings  # hoặc HuggingFaceEmbeddings
from langchain_community.vectorstores import Chroma

# 1. Load tất cả file code trong src/
documents = []
for root, dirs, files in os.walk("src"):
    for file in files:
        if file.endswith((".ts", ".js", ".py")):
            file_path = os.path.join(root, file)
            try:
                loader = TextLoader(file_path, encoding="utf-8")
                documents.extend(loader.load())
            except:
                pass

# 2. Chia nhỏ (split) - giữ nguyên ranh giới function nếu có thể
# RecursiveCharacterTextSplitter là đơn giản, nhưng bạn có thể viết custom splitter dùng AST
splitter = RecursiveCharacterTextSplitter(
    chunk_size=1000,
    chunk_overlap=200,
    separators=["\nfunction ", "\nclass ", "\n\n", "\n", " "]
)
chunks = splitter.split_documents(documents)

# 3. Tạo metadata cho chunk (dùng tên file, ngôn ngữ)
for chunk in chunks:
    chunk.metadata["source"] = chunk.metadata.get("source", "unknown")
    chunk.metadata["language"] = os.path.splitext(chunk.metadata["source"])[1][1:]

# 4. Tạo embedding và lưu vào Chroma
embedding = OpenAIEmbeddings()  # hoặc HuggingFaceEmbeddings(model_name="all-MiniLM-L6-v2")
vectorstore = Chroma.from_documents(
    documents=chunks,
    embedding=embedding,
    persist_directory="./kb_vectorstore"
)
vectorstore.persist()
print(f"Indexed {len(chunks)} chunks")
```

### 4.3. Index API specs (OpenAPI)
Parse spec thành các endpoint riêng biệt, mỗi endpoint là một document.

```python
import json
from langchain.schema import Document

with open("openapi.json") as f:
    spec = json.load(f)

api_docs = []
for path, methods in spec["paths"].items():
    for method, details in methods.items():
        text = f"Endpoint: {method.upper()} {path}\nSummary: {details.get('summary','')}\n"
        text += f"Parameters: {details.get('parameters',[])}\n"
        text += f"Responses: {details.get('responses',{})}"
        api_docs.append(Document(
            page_content=text,
            metadata={"type": "api", "path": path, "method": method.upper()}
        ))

# Tách nhỏ nếu cần, rồi thêm vào Chroma
api_chunks = splitter.split_documents(api_docs)
vectorstore.add_documents(api_chunks)
vectorstore.persist()
```

### 4.4. Index quy ước code và tài liệu thiết kế
Tương tự, load các file markdown, text rồi chunk và thêm vào vectorstore.

### 4.5. Index ví dụ code mẫu (few-shot)
Bạn có thể lưu trữ các cặp (mô tả, code) trong một thư mục riêng, hoặc dùng file yaml:

```yaml
- task: "create a new service with dependency injection"
  code: |
    @Injectable()
    export class UserService {
      constructor(private readonly userRepo: UserRepository) {}
      async create(data: CreateUserDto): Promise<User> { ... }
    }
```

Khi index, bạn chunk theo từng example, đặt metadata `type=example`.

---

## 5. Truy xuất KB khi sinh code (RAG)

Khi nhận yêu cầu từ user, workflow sẽ thực hiện truy xuất KB để lấy context phù hợp nhất.

```python
from langchain.chains import RetrievalQA
from langchain.chat_models import ChatOpenAI

# Khởi tạo retriever từ vectorstore, hỗ trợ filter theo metadata
retriever = vectorstore.as_retriever(
    search_type="mmr",         # Maximum Marginal Relevance - tăng độ đa dạng
    search_kwargs={
        "k": 6,
        "filter": {"type": "code"}   # Chỉ lấy code, bỏ qua doc nếu muốn
    }
)

# Hoặc dùng truy vấn tự viết để kiểm soát tốt hơn
def get_context_for_task(task_description: str, language: str = "typescript"):
    # Query cho code hiện hành
    query = f"Code liên quan đến: {task_description}"
    results = vectorstore.similarity_search(
        query,
        k=4,
        filter={"language": language}
    )
    # Query cho convention
    convention_results = vectorstore.similarity_search(
        f"Coding convention {language}",
        k=2,
        filter={"type": "convention"}
    )
    # Query cho api spec nếu liên quan
    api_results = vectorstore.similarity_search(
        f"API endpoint {task_description}",
        k=2,
        filter={"type": "api"}
    )
    # Trộn và sắp xếp context
    all_context = results + convention_results + api_results
    # Loại bỏ trùng lặp và giới hạn độ dài
    return all_context
```

Sau đó, xây dựng prompt cho LLM:

```python
def build_prompt(user_request, context_docs):
    context_text = "\n\n".join([doc.page_content for doc in context_docs])
    prompt = f"""Bạn là một software engineer trong dự án của chúng tôi.
Dưới đây là các quy ước và code mẫu hiện có trong dự án:

{context_text}

Dựa vào những thông tin trên, hãy thực hiện yêu cầu sau:
{user_request}

Chỉ sử dụng những module, hàm, class có sẵn trong context. Không tự ý thêm thư viện mới.
Trả lời bằng code hoàn chỉnh kèm đường dẫn file cần tạo/sửa.
"""
    return prompt
```

---

## 6. Code Graph / AST cho truy vấn chính xác

Để biết chính xác `UserService` nằm ở file nào, bạn cần một cơ sở dữ liệu đồ thị. Có thể dùng:

- **SCIP** + **Sourcegraph CLI**: index code -> file SCIP, có thể query qua API hoặc convert sang SQLite.
- **tree-sitter** + **NetworkX**: tự build graph.

Ví dụ đơn giản với tree‑sitter (Python) để trích xuất symbols:

```python
from tree_sitter import Language, Parser
import tree_sitter_python as tspython

parser = Parser()
parser.set_language(Language(tspython.language()))
tree = parser.parse(source_code_bytes)

# Duyệt cây để lấy các định nghĩa function/class
def extract_definitions(node, source_code):
    definitions = []
    if node.type in ["function_definition", "class_definition"]:
        name_node = node.child_by_field_name("name")
        if name_node:
            name = source_code[name_node.start_byte:name_node.end_byte].decode()
            definitions.append({
                "name": name,
                "kind": node.type,
                "start_line": node.start_point[0] + 1,
                "end_line": node.end_point[0] + 1,
                "source_file": file_path
            })
    for child in node.children:
        definitions.extend(extract_definitions(child, source_code))
    return definitions
```

Lưu kết quả vào SQLite hoặc graph DB để truy vấn nhanh.

---

## 7. Chiến lược duy trì và cập nhật KB

- **Incremental indexing**: Khi code thay đổi, chỉ index lại các file bị ảnh hưởng. Có thể dùng file hash để phát hiện thay đổi.
- **Versioning**: Gắn commit SHA vào metadata của mỗi chunk để biết nó thuộc phiên bản nào.
- **CI/CD integration**: Chạy job indexing mỗi khi merge lên main, tự động cập nhật KB.
- **Tách biệt môi trường**: KB cho production code, KB cho design docs,... tránh nhiễu.

---

## 8. Công cụ và thư viện khuyên dùng

| Mục đích | Công cụ | Ghi chú |
|----------|---------|---------|
| Vector DB (local) | Chroma, Qdrant, LanceDB | Chroma dễ bắt đầu nhất |
| Embedding | OpenAI, sentence-transformers, text-embeddings-inference | Dùng local để tiết kiệm chi phí |
| Indexing pipeline | LangChain, LlamaIndex | Cả hai đều có loader cho code, markdown |
| Code splitting nâng cao | `langchain.text_splitter.Language` (có sẵn cho Python, JS, TS...) | Phân tách theo ranh giới function |
| Graph index | SCIP, tree-sitter + NetworkX | SCIP mạnh mẽ, có CLI miễn phí |
| Self-hosted LLM | Ollama, vLLM | Đảm bảo code không ra ngoài |

---

## 9. Mẫu kiến trúc thư mục cho dự án KB

```
project-root/
├── kb_indexer/          # Code indexing và query
│   ├── indexer.py       # Quét file, tạo chunks, embedding
│   ├── retriever.py     # Hàm truy vấn KB
│   └── graph_builder.py # Build code graph (AST)
├── kb_vectorstore/      # Dữ liệu Chroma persist
├── openapi.json         # API spec
├── conventions/         # Markdown quy ước
│   └── coding-style.md
├── examples/            # Few-shot examples
│   └── services.yaml
└── design_docs/         # Tài liệu thiết kế
    └── architecture.md
```

---

## 10. Kết luận

Với KB được xây dựng như trên, workflow AI của bạn sẽ:
- Sinh code bám sát thực tế dự án, không “hoang tưởng”.
- Tự động tuân thủ quy tắc nhóm.
- Dễ dàng mở rộng khi dự án phát triển.

