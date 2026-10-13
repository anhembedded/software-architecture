# RAG tổng quan

## RAG là gì

**RAG (Retrieval-Augmented Generation)**: trước khi hỏi LLM, hệ thống **tìm** các đoạn tài liệu liên quan trong kho dữ liệu của bạn, rồi **đưa chúng vào prompt** cùng câu hỏi. LLM trả lời dựa trên đoạn đó, thay vì chỉ dựa vào những gì nó đã học khi huấn luyện.

**Vì sao cần:** LLM không biết dữ liệu nội bộ của bạn, không biết thông tin mới sau thời điểm huấn luyện, và có thể bịa khi không biết. RAG cho nó "mở sách" để tra trước khi trả lời.

## Pipeline cơ bản

**Chuẩn bị dữ liệu (làm một lần, cập nhật định kỳ):**

1. **Thu thập** tài liệu (PDF, wiki, web, code, ticket...)
2. **Parse** thành text sạch
3. **Chunking**: cắt thành các đoạn nhỏ (thường vài trăm đến ~1000 token)
4. **Embedding**: biến mỗi chunk thành một vector số; các đoạn có nghĩa gần nhau thì vector gần nhau
5. **Lưu** vào vector store (FAISS, Chroma, pgvector, Qdrant...)

**Mỗi lần có câu hỏi:**

1. Embed câu hỏi bằng cùng embedding model
2. Tìm top-k chunk gần nhất
3. (Tùy chọn) Rerank để lọc lại cho chính xác
4. Ghép chunk + câu hỏi vào prompt, gửi LLM
5. LLM trả lời, kèm trích dẫn nguồn

## Khái niệm cần biết

- **Embedding**: vector biểu diễn ý nghĩa của văn bản.
- **Chunking**: cách cắt tài liệu; ảnh hưởng rất lớn đến chất lượng. Quá nhỏ thì mất ngữ cảnh, quá lớn thì loãng.
- **Top-k**: số chunk lấy về mỗi lần (thường 3-10).
- **Hybrid search**: kết hợp tìm theo nghĩa (vector) và theo từ khóa (BM25), vì vector thuần yếu khi cần khớp chính xác tên riêng, mã, số hiệu.
- **Reranker**: model nhỏ chấm điểm lại top-k để đưa chunk liên quan nhất lên đầu.
- **Metadata filtering**: lọc theo nguồn, loại tài liệu, phiên bản, ngày tháng trước khi tìm.
- **Context window**: giới hạn lượng text đưa vào một prompt.

## Những lầm tưởng phổ biến

1. **"RAG hết hallucination."** Sai. RAG chỉ _giảm_ chứ không loại bỏ. LLM vẫn có thể hiểu sai đoạn được đưa, bỏ qua nó, hoặc bịa khi không tìm thấy gì. Nên yêu cầu "chỉ trả lời dựa trên ngữ cảnh, không có thì nói không biết" và bắt trích dẫn nguồn.
    
2. **"Đổ hết tài liệu vào vector DB là chạy."** Sai. Phần lớn lỗi nằm ở parse và chunking, không phải ở LLM. PDF có bảng, sơ đồ, nhiều cột thường bị parse thành rác.
    
3. **"Vector database là phần khó/quan trọng nhất."** Không. Với vài nghìn đến vài chục nghìn chunk, FAISS hay pgvector là đủ. Nút thắt thật sự là chất lượng retrieval.
    
4. **"Embedding model đắt hơn thì tốt hơn."** Không chắc. Phải đo trên dữ liệu của bạn. Với tiếng Việt cần chọn model hỗ trợ đa ngôn ngữ.
    
5. **"Similarity cao nghĩa là chunk đúng."** Sai. Nó chỉ nói hai đoạn "nghe giống nhau", không phải "chứa câu trả lời". Vì vậy mới cần rerank và hybrid search.
    
6. **"Context window to rồi thì khỏi cần RAG."** Không hẳn. Nhét quá nhiều vẫn tốn tiền, chậm, và LLM dễ bỏ sót thông tin ở giữa. Kho tài liệu lớn hoặc hay thay đổi thì RAG vẫn hợp lý hơn.
    
7. **"RAG và fine-tune thay thế nhau."** Chúng giải quyết việc khác nhau. RAG đưa **kiến thức** (cập nhật được, có nguồn). Fine-tune dạy **hành vi/phong cách**. Muốn LLM biết tài liệu nội bộ thì RAG thường là bước đầu tiên.
    
8. **"Demo chạy ngon là xong."** Demo với vài câu hỏi chọn lọc luôn đẹp. Hệ thống thật cần một **bộ câu hỏi đánh giá** (vài chục câu có đáp án đúng) để đo xem retrieval có lấy đúng chunk không; không có thì bạn đang chỉnh mò.
    
9. **"Gửi dữ liệu lên API là an toàn."** Tùy chính sách. Với dữ liệu nhạy cảm/nội bộ, hãy kiểm tra quy định công ty, hoặc cân nhắc model chạy local.
    

## Cách bắt đầu

1. Chọn một tập tài liệu nhỏ và **20-30 câu hỏi** bạn đã biết đáp án.
2. Dựng bản đơn giản nhất bằng Python: parse → chunk (~500 token, overlap nhẹ) → embedding → FAISS/Chroma → LLM. LlamaIndex hoặc LangChain giúp nhanh, nhưng tự viết khoảng 100 dòng một lần sẽ hiểu rõ hơn.
3. **Đo retrieval trước**: chunk đúng có nằm trong top-k không? Nếu không, sửa parse/chunking trước khi đụng đến prompt hay LLM.
4. Thêm hybrid search và rerank khi cần.
5. Bắt LLM trích dẫn nguồn để dễ kiểm chứng.

Nếu bạn cho mình biết loại tài liệu, quy mô, và có được dùng API bên ngoài hay phải chạy local, mình sẽ gợi ý stack cụ thể hơn.