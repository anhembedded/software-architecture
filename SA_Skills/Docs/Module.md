Một module không cần nhiều tài liệu. Bộ tối thiểu có giá trị thực tế là **1 design doc ngắn (1–5 trang) + 3–4 sơ đồ + các ADR cho quyết định quan trọng**. Phần còn lại (spec chi tiết từng class, sơ đồ code) nên sinh từ code hoặc bỏ qua.

## 1. Tài liệu một module nên có

Phần này từ kiến thức của mình, đã đối chiếu với các nguồn bên dưới.

|Tài liệu|Trả lời câu hỏi|Bắt buộc?|
|---|---|---|
|**Overview / Goals & Non-goals**|Module này giải quyết vấn đề gì? Không làm gì? Ai dùng?|Có|
|**Requirements & Quality goals**|Yêu cầu chức năng, và các yêu cầu phi chức năng (latency, memory, thread-safety, độ tin cậy) với số liệu cụ thể|Có|
|**Constraints & Assumptions**|Ràng buộc (Qt version, RAM/CPU, hệ điều hành, thư viện)|Có|
|**Context & Interfaces (API/contract)**|Module nói chuyện với ai, qua giao diện nào, dữ liệu gì, lỗi trả về ra sao|Có, quan trọng nhất|
|**Kiến trúc nội bộ (building blocks)**|Chia thành những phần nào, mỗi phần chịu trách nhiệm gì|Có|
|**Runtime behavior**|Các kịch bản chính: khởi tạo, luồng dữ liệu, lỗi, tắt module; threading model|Có (2–4 kịch bản)|
|**Data model / State machine**|Cấu trúc dữ liệu, vòng đời, các trạng thái|Nếu có state hoặc data phức tạp|
|**Alternatives considered**|Các phương án khác và lý do loại, kể cả phương án "không làm gì"|Có|
|**ADR (Architecture Decision Record)**|Từng quyết định lớn và lý do|Có, mỗi quyết định một file|
|**Risks & Tech debt**|Rủi ro, điểm yếu đã biết|Nên có|
|**Test strategy**|Test cái gì, mức nào, mock gì|Nên có|
|**Deployment / Config**|Cách build, cấu hình, phụ thuộc runtime|Nếu module có phần triển khai riêng|
|**Glossary**|Thuật ngữ|Nếu nhiều thuật ngữ miền|

## 2. Sơ đồ nên vẽ

| Sơ đồ                                                      | Dùng để                                   | Ưu tiên                                   |
| ---------------------------------------------------------- | ----------------------------------------- | ----------------------------------------- |
| **Context diagram** (module trong hệ thống)                | Ranh giới, bên ngoài tương tác với module | Bắt buộc                                  |
| **Component / Building-block diagram**                     | Cấu trúc bên trong, ai phụ thuộc ai       | Bắt buộc                                  |
| **Sequence diagram** (2–4 kịch bản chính + 1 kịch bản lỗi) | Luồng tương tác theo thời gian            | Bắt buộc                                  |
| **State machine**                                          | Vòng đời, trạng thái, chuyển trạng thái   | Nếu có state                              |
| **Class/ER diagram**                                       | Data model                                | Chỉ cho phần quan trọng                   |
| **Threading / Deployment diagram**                         | Thread, process, nơi chạy                 | Nếu có đa luồng hoặc đa process           |
| **Timing / Activity / Dataflow**                           | Ràng buộc thời gian, pipeline xử lý       | Tùy bài toán (embedded thường cần timing) |

## 3. Các dự án lớn làm gì

- **arc42** là template phổ biến nhất, gồm 12 mục: mục tiêu, ràng buộc, context & scope, solution strategy, building block view, runtime view, deployment view, crosscutting concepts, architecture decisions và các mục khác. Điểm hay là nó khuyến khích dùng nhẹ: các mục giống ngăn tủ, tủ vẫn có giá trị dù một số ngăn để trống, và nên chỉ giữ một số ít kịch bản runtime.
- **C4 model** (Simon Brown) cho sơ đồ theo 4 mức zoom: Context, Container, Component, Code. Thực tế, chỉ nên đi xuống mức Component cho container phức tạp, và mức Code thường được sinh tự động hoặc bỏ qua. Với một module, bạn chủ yếu dùng mức 3.
- **Google design docs** không theo khuôn cứng: đó là tài liệu không chính thức, không có guideline nội dung nghiêm ngặt, nhưng có vài điểm lặp lại: ghi lại các trade-off, hữu ích khi có system-context diagram, hiếm khi chứa code, và đủ ngắn để người bận rộn đọc, thậm chí có "mini design doc" 1–3 trang. Một điểm cần nhớ là doc nào thực chất là hướng dẫn cài đặt thì dấu hiệu là không cần viết doc đó. Các hướng dẫn khác bổ sung: bắt buộc có mục phương án đã cân nhắc, luôn đưa "không làm gì" làm baseline, và kèm số liệu thật như số dòng DB, độ trễ. Quy tắc ngón tay cái: dự án từ khoảng 1 người-tháng trở lên thì nên viết design doc.
- **ADR** ghi từng quyết định: định danh, tiêu đề, trạng thái, context, decision, consequences, alternatives. Nguyên tắc: ADR đã accepted thì bất biến, đổi quyết định thì tạo ADR mới thay thế, và mỗi ADR một quyết định. Phân biệt với design doc: design doc khám phá giải pháp chi tiết, ADR ghi một quyết định kèm lý do ngắn gọn.
- **KEP (Kubernetes), Rust RFC, Python PEP**: quy trình đề xuất thay đổi. KEP lấy cảm hứng từ IETF RFC, Python PEP và Rust RFC, template gồm motivation, goals, non-goals, proposal, risks, design details, test plan kèm trạng thái vòng đời. Tuy nhiên chỉ bắt buộc khi thay đổi rộng và ảnh hưởng hầu hết dự án, và mỗi SIG được tùy biến template theo nhu cầu. Nghĩa là ngay cả dự án lớn cũng không dùng một khuôn cho mọi thứ.

## 4. Pain point phổ biến

1. **Lỗi thời và gây hiểu lầm.** Ba phàn nàn hàng đầu: không ai đọc, gây hiểu lầm, lỗi thời. Có quan điểm cực đoan rằng doc lỗi thời còn tệ hơn không có doc, vì nó "nói dối".
2. **Sơ đồ mức code nhanh hỏng.** Code diagram dễ lỗi thời nên chỉ vẽ cho component phức tạp nhất.
3. **Wiki thành bãi rác.** Confluence hay Notion nhanh chóng thành một mớ cũ và lộn xộn, không ai muốn đụng vào.
4. **Khó bảo trì.** Các blocker thường gặp: thiếu tự động hóa quy trình, hướng dẫn không rõ, thiếu khả năng truy vết.
5. **Viết quá dài hoặc viết lại code bằng chữ.** Doc quá chi tiết thành "implementation viết sớm", và một nguyên tắc hay là chỉ ghi quyết định nếu sai thì tốn kém.
6. **Viết ADR sau khi đã làm xong.** Đây là anti-pattern vì ADR là bản ghi quyết định, không phải tài liệu mô tả cái đã xảy ra.
7. **Doc bị hy sinh đầu tiên khi thiếu thời gian** (tài liệu kỹ thuật thường là thứ bị cắt đầu tiên).

## 5. Lời khuyên cho bạn

Đây là phần mình tự đánh giá từ các nguồn trên, không phải kết luận chắc chắn.

**1. Bắt đầu với bộ tối thiểu, đừng copy nguyên arc42.** Một file `design.md` cho mỗi module, khoảng 6 mục: Goals/Non-goals, Context & Interfaces, Building blocks, Runtime scenarios, Alternatives, Risks. Thêm Test strategy khi module quan trọng. Phần nào chưa cần thì để trống, giống ý "ngăn tủ" của arc42.

**2. Ưu tiên theo giá trị trên chi phí bảo trì.** Giá trị cao nhất, ít hỏng nhất là: **interface/contract**, **ADR**, **sequence diagram cho kịch bản chính**. Giá trị thấp, nhanh hỏng nhất là: class diagram chi tiết, doc mô tả từng hàm.

**3. Docs-as-code.** Để `docs/` cùng repo với module, viết Markdown, vẽ sơ đồ bằng text (PlantUML hợp với bạn, thêm C4-PlantUML nếu muốn chuẩn C4). Doc review cùng PR với code, nhờ đó giảm lỗi thời. Quy ước nhỏ: PR đổi interface hoặc hành vi thì phải đụng tới doc.

**4. Sơ đồ có quy ước nhất quán.** Màu hoặc stereotype theo lớp (ví dụ ranh giới Python/QML hoặc ranh giới sở hữu), và có chú thích (legend) trong mỗi sơ đồ.

**5. ADR ngay khi quyết định, mỗi quyết định một file, đánh số.** Chỉ cho quyết định tốn kém nếu sai (chọn framework, mô hình thread, giao thức, cách lưu dữ liệu). Không ghi mọi thứ.

**6. Chốt phạm vi theo kích cỡ module.** Module nhỏ (dưới 1 tuần): README + 1 sơ đồ. Module trung bình: mini design doc 1–3 trang + vài ADR. Module lớn hoặc rủi ro cao hoặc nhiều người cùng làm: design doc đầy đủ + review trước khi code. Nên có một mục "Open questions" để mọi người góp ý trước khi đầu tư cài đặt.

**7. Cân nhắc cho embedded.** Nếu module chạm phần cứng hoặc real-time, thêm: ngân sách tài nguyên (RAM/flash/CPU), timing diagram, phân tích lỗi (failure modes), và giao diện phần cứng (register hoặc protocol). Đây là phần doc thông thường hay bỏ sót.

Nếu bạn cho mình biết module cụ thể (ví dụ một module Qt/QML hay RAG pipeline), mình có thể dựng sẵn template `design.md` + skeleton PlantUML và một ADR mẫu để bạn dùng ngay.

Sources:

- [arc42 documentation](https://docs.arc42.org/home/)
- [Brief introduction to arc42 (INNOQ)](https://www.innoq.com/de/blog/brief-introduction-to-arc42)
- [C4 Model (MockFlow)](https://mockflow.com/glossary/c4-model)
- [Vaadin: architecture design with C4](https://origin.vaadin.com/docs/v24/building-apps/deep-dives/architecture/design)
- [Design Docs at Google](https://www.industrialempathy.com/posts/design-docs-at-google/)
- [Design doc models (DocuWriter)](https://www.docuwriter.ai/posts/example-of-software-design-document)
- [Design docs at Google (Lodely)](https://www.lodely.com/blog/design-docs-at-google)
- [Angela Zhang, how to write a good software design document](https://www.freecodecamp.org/news/how-to-write-a-good-software-design-document-66fcf019569c)
- [Design doc playbook (HN discussion)](https://zeli.app/story/49696125)
- [Architecture Decision Records concept](https://concepts.dsebastien.net/concept/architecture-decision-records/)
- [10 ADR anti-patterns](https://jopr.org/blog/detail/10-adr-antipatterns)
- [ADR practical guide](https://www.metaproject.pro/resources/architecture-decision-records)
- [ADR skill/guide (sharedcontext.ai)](https://sharedcontext.ai/skills/external/noah-sheldon/architecture-decision-records)
- [Kubernetes KEP (ingress-nginx)](https://kubernetes.github.io/ingress-nginx/enhancements)
- [KEP template](https://kubernetes.github.io/ingress-nginx/enhancements/YYYYMMDD-kep-template)
- [KEP process](https://github.com/kubernetes/enhancements/blob/master/keps/sig-architecture/0000-kep-process/README.md)
- [JetBrains Writerside blog](https://blogs.jetbrains.com/writerside/)
- [ClickHelp: problems with technical documentation](https://clickhelp.com/clickhelp-technical-writing-blog/problems-with-technical-documentation/)
- [Frontend Masters: Pain Points](https://frontendmasters.com/courses/devops/pain-points)
- [Write the Docs: Maintaining Documentation](https://writethedocs-www.readthedocs.io/videos/prague/2022/maintaining-documentation-make-it-easy-emilia-juda-zbay/)
- [DaedTech: Forget Design Documents](https://daedtech.com/?p=868)