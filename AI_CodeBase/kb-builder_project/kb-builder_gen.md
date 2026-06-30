Dưới đây là một **dự án Python thực tế** giúp bạn "nấu" tất cả dữ liệu thô (code, docs, api spec…) thành Knowledge Base sẵn sàng cho AI workflow.  
Bạn có thể chạy nó như một CLI, tích hợp vào CI/CD hoặc gọi như thư viện.

---

## 1. Cấu trúc thư mục dự án

```
kb-builder/
├── pyproject.toml          # (tùy chọn) quản lý dependency
├── requirements.txt
├── .env                    # chứa OPENAI_API_KEY nếu dùng OpenAI
├── config.yaml             # cấu hình: thư mục source, loại file, chunk size...
├── kb_builder/
│   ├── __init__.py
│   ├── main.py             # CLI chính
│   ├── loaders.py          # Đọc file từ nhiều nguồn
│   ├── chunkers.py         # Chia nhỏ theo loại
│   ├── embedder.py         # Tạo embedding (OpenAI / local)
│   ├── vector_store.py     # Thao tác với ChromaDB
│   ├── graph_builder.py    # Xây dựng code graph (tree‑sitter)
│   └── retriever.py        # Truy vấn kết hợp Vector + Graph
├── data/
│   └── chroma/             # Persist directory của Chroma
└── examples/               # Dữ liệu mẫu để test
    └── sample_project/
```

---

## 2. Cài đặt dependencies

```requirements.txt
chromadb>=0.4
langchain>=0.1
langchain-community>=0.1
langchain-openai>=0.1
openai>=1.0
sentence-transformers>=2.2
tree-sitter>=0.21
tree-sitter-python>=0.21   # thay bằng ngôn ngữ bạn cần
pyyaml>=6.0
click>=8.0
```

Bạn cũng cần cài đặt grammar cho từng ngôn ngữ. Ví dụ:

```bash
pip install tree-sitter-javascript tree-sitter-typescript
# Nếu dùng Python:
# pip install tree-sitter-python
```

---

## 3. Code từng module (tóm lược)

### `loaders.py` – Nạp tất cả file thành danh sách `Document` (LangChain)

```python
import os
from typing import List
from langchain_core.documents import Document
from langchain_community.document_loaders import TextLoader

def load_all_files(root_dir: str, patterns: List[str]) -> List[Document]:
    docs = []
    for root, _, files in os.walk(root_dir):
        for file in files:
            if any(file.endswith(ext) for ext in patterns):
                path = os.path.join(root, file)
                try:
                    loader = TextLoader(path, encoding="utf-8")
                    docs.extend(loader.load())
                except Exception as e:
                    print(f"Bỏ qua {path}: {e}")
    # Gán metadata ban đầu
    for doc in docs:
        doc.metadata["source"] = doc.metadata.get("source", "")
        doc.metadata["type"] = "code"  # có thể ghi đè sau
    return docs
```

### `chunkers.py` – Chia nhỏ phù hợp với từng loại

Dùng `RecursiveCharacterTextSplitter` cho văn bản chung, nhưng tùy chỉnh cho code.

```python
from langchain.text_splitter import RecursiveCharacterTextSplitter

code_splitter = RecursiveCharacterTextSplitter.from_language(
    language="typescript",  # hoặc python, javascript...
    chunk_size=1000,
    chunk_overlap=200
)

text_splitter = RecursiveCharacterTextSplitter(
    chunk_size=800,
    chunk_overlap=100,
    separators=["\n\n", "\n", " ", ""]
)

def chunk_documents(docs, doc_type="code"):
    if doc_type in ("code", "api_spec"):
        return code_splitter.split_documents(docs)
    else:
        return text_splitter.split_documents(docs)
```

### `embedder.py` – Tạo embedding

```python
from langchain_openai import OpenAIEmbeddings
# Hoặc dùng local:
# from langchain_community.embeddings import HuggingFaceEmbeddings

def get_embedder():
    # Nếu có key OpenAI
    # return OpenAIEmbeddings(model="text-embedding-3-small")
    # Dùng local để tránh phụ thuộc API:
    from langchain_community.embeddings import HuggingFaceEmbeddings
    return HuggingFaceEmbeddings(model_name="all-MiniLM-L6-v2")
```

### `vector_store.py` – Quản lý ChromaDB

```python
import chromadb
from chromadb.config import Settings
from langchain_chroma import Chroma
from .embedder import get_embedder

def init_vectorstore(persist_dir: str = "data/chroma"):
    embedder = get_embedder()
    vectorstore = Chroma(
        persist_directory=persist_dir,
        embedding_function=embedder
    )
    return vectorstore

def add_documents_to_store(vectorstore, docs):
    # docs đã được chunk
    vectorstore.add_documents(docs)
    # Không cần persist() với Chroma mới nếu dùng persist_directory
```

### `graph_builder.py` – Xây dựng code graph (đơn giản)

Dùng tree‑sitter để trích xuất symbol và lưu vào dictionary (có thể mở rộng ra SQLite/NetworkX).

```python
from tree_sitter import Language, Parser
import tree_sitter_python as tspython  # ví dụ cho Python

# Bạn cần build Language object trước, hoặc dùng prebuilt wheel.
# Đây là code minh họa, thực tế cần chỉnh theo ngôn ngữ.

class CodeGraph:
    def __init__(self):
        self.symbols = {}  # name -> location, type

    def parse_file(self, file_path):
        with open(file_path, "rb") as f:
            content = f.read()
        parser = Parser()
        lang = Language(tspython.language())  # ví dụ Python
        parser.set_language(lang)
        tree = parser.parse(content)
        # Duyệt cây tìm function/class definitions
        # ... (code duyệt node)
        # Lưu vào self.symbols
```

Tuy nhiên, để nhanh, bạn có thể dùng thư viện `scip-python` hoặc `scip-typescript` để xuất ra file index chính xác hơn.

### `retriever.py` – Truy vấn hỗn hợp

```python
def retrieve_context(query: str, vectorstore, code_graph=None, top_k=6):
    # Semantic search từ VectorDB
    docs = vectorstore.similarity_search(query, k=top_k)
    # Nếu có code_graph, tra cứu thêm chính xác
    if code_graph:
        # Ví dụ tìm theo tên function được nhắc đến trong query
        # -> ghép thêm vào docs
        pass
    # Tạo context string
    context = "\n\n".join([d.page_content for d in docs])
    return context
```

---

## 4. CLI chính – `main.py`

```python
import click
from kb_builder.loaders import load_all_files
from kb_builder.chunkers import chunk_documents
from kb_builder.vector_store import init_vectorstore, add_documents_to_store
from kb_builder.retriever import retrieve_context

@click.group()
def cli():
    pass

@cli.command()
@click.option('--src', default='./project_src', help='Thư mục mã nguồn')
def index(src):
    """Index toàn bộ dự án vào Knowledge Base."""
    print("Đang load file...")
    code_patterns = ['.ts', '.tsx', '.js', '.jsx', '.py']
    docs_code = load_all_files(f"{src}/src", code_patterns)
    
    docs_convention = load_all_files(f"{src}/docs", ['.md'])
    # ... load thêm API spec, examples...
    
    # Gộp và gán type metadata
    for d in docs_code: d.metadata['type'] = 'code'
    for d in docs_convention: d.metadata['type'] = 'convention'
    
    all_docs = docs_code + docs_convention  # ...
    
    print("Chunking...")
    chunks = chunk_documents(all_docs)  # có thể phân loại theo type nếu muốn chunker riêng
    
    print("Lưu vào VectorDB...")
    vs = init_vectorstore()
    add_documents_to_store(vs, chunks)
    print(f"Đã index {len(chunks)} chunks.")

@cli.command()
@click.argument('query')
def search(query):
    """Tìm kiếm context cho một yêu cầu."""
    vs = init_vectorstore()
    ctx = retrieve_context(query, vs)
    click.echo(ctx)

if __name__ == '__main__':
    cli()
```

Chạy:

```bash
python -m kb_builder.main index --src ./my_project
python -m kb_builder.main search "Viết API login sử dụng JWT"
```

---

## 5. Mở rộng để thành một project hoàn chỉnh

- **Tự động phát hiện loại file** và dùng splitter tối ưu (Language splitter của LangChain).
- **Xây dựng Code Graph hoàn chỉnh**: dùng SCIP để có index chính xác, lưu vào SQLite.
- **Tích hợp retriever lai**: dùng `EnsembleRetriever` của LangChain kết hợp keyword (BM25) và vector.
- **Tạo Docker image** để chạy index tự động trong CI/CD.
- **Thêm cache** để không index lại những file không thay đổi.

---

## 6. Tổng kết

Vậy là bạn đã có một "cỗ máy" trong một project Python để biến toàn bộ tài sản tri thức của dự án thành dạng máy có thể tiêu hóa được.  
Bạn chỉ cần:

1. Gom nguyên liệu (file code, docs, spec…)
2. Chạy `index` – nó sẽ tự nấu thành KB.
3. Gọi `search` (hoặc dùng `retrieve_context` trong code) để lấy context cho AI.

Nếu bạn muốn mình viết chi tiết hơn phần **Code Graph** (dùng SCIP hoặc tree‑sitter đầy đủ), hoặc cách tích hợp vào **Orchestrator** đã có, cứ nhắn nhé. Mình sẵn sàng mở rộng code mẫu.