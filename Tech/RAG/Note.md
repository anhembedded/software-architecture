Repo hiện đang trống (chỉ có `.gitignore`), nên mình sẽ bắt đầu từ số 0 cùng bạn. Trước khi lập plan, mình cần hiểu context. Bạn trả lời giúp mình các nhóm câu hỏi dưới đây. Câu nào chưa biết thì cứ ghi "chưa rõ", mình sẽ đề xuất mặc định.

## 1. Mục tiêu và bối cảnh

1. Project này để **làm gì**? Ví dụ: học và portfolio, sản phẩm thương mại, công cụ nội bộ công ty, hay POC cho khách hàng.
2. **Người dùng cuối** là ai, và họ hỏi về loại nội dung gì? Ví dụ: tài liệu kỹ thuật, hợp đồng, wiki nội bộ, sản phẩm e-commerce.
3. "RAG engine" bạn hiểu là **thư viện/SDK**, **service có API** (REST/gRPC), hay **ứng dụng hoàn chỉnh có UI chat**?
4. Thành công nghĩa là gì? Ví dụ: trả lời đúng ≥ X%, latency dưới Y giây, hỗ trợ N user đồng thời.

## 2. Dữ liệu

5. Nguồn dữ liệu là gì? PDF, Word, web, Confluence/Notion, database, code, ảnh, bảng biểu?
6. Khối lượng: bao nhiêu tài liệu và bao nhiêu GB/triệu chunk? Dữ liệu có cập nhật liên tục không?
7. Ngôn ngữ chính là tiếng Việt, tiếng Anh, hay lẫn cả hai? Điều này ảnh hưởng nhiều đến việc chọn embedding model.
8. Dữ liệu có nhạy cảm không? Có yêu cầu phân quyền theo user/nhóm (ACL) không?

## 3. Ràng buộc kỹ thuật

9. Ngôn ngữ và stack bạn muốn dùng: Python, TypeScript, Go, hay khác? Mức kinh nghiệm của bạn với từng thứ?
10. LLM và embedding: dùng API cloud (Claude, OpenAI...), hay phải chạy local/self-host (Ollama, vLLM)? Có yêu cầu dữ liệu không được rời máy không?
11. Hạ tầng triển khai: laptop, Docker, VPS, hay cloud (AWS/GCP/Azure)? Có sẵn vector DB hay Postgres chưa?
12. Bạn muốn **tự build từng thành phần** (chunking, retrieval, rerank...) để hiểu sâu, hay chấp nhận dùng framework như LangChain/LlamaIndex để đi nhanh?

## 4. Nguồn lực và thời gian

13. Mấy người làm và mỗi tuần dành bao nhiêu giờ? Một mình hay có team?
14. Deadline hoặc mốc quan trọng, nếu có (demo, ra mắt)?
15. Ngân sách hàng tháng cho API và hạ tầng khoảng bao nhiêu?

## 5. Phạm vi và chất lượng

16. Những tính năng nào là **bắt buộc** cho bản đầu (MVP)? Ví dụ: trích dẫn nguồn, hội thoại nhiều lượt, hybrid search, rerank, streaming, đa người dùng.
17. Bạn đã có **bộ câu hỏi mẫu kèm đáp án đúng** để đánh giá chưa? Nếu chưa, mình sẽ đưa việc xây bộ eval vào plan.
18. Có yêu cầu về monitoring, logging hay bảo mật (auth, rate limit) ngay từ đầu không?

## 6. Cách làm việc

19. Bạn muốn plan ở dạng nào: doc/roadmap theo milestone, backlog GitHub Issues, hay cả hai? Mình có thể tạo issue trực tiếp trong repo `anhembedded/sagittarius_rag`.
20. "Sagittarius" có ý nghĩa gì với project, hay chỉ là codename?

---

Nếu muốn trả lời nhanh, 6 câu quan trọng nhất là: **1, 5, 7, 9, 10, 13**. Mình có thể lập bản plan sơ bộ từ 6 câu này rồi tinh chỉnh dần.