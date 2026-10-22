
# Tư duy tiếp cận một dự án hoàn toàn mới trong môi trường chuyên nghiệp

Trong môi trường kỹ thuật chuyên nghiệp, điều quan trọng nhất không phải là bắt đầu học công nghệ đó ngay, mà là:
	**Xác định đúng vấn đề** 
	**Giảm thiểu sự bất định** 
	**Tìm ra con đường khả thi để hoàn thành dự án.**

Một kỹ sư có kinh nghiệm không nhất thiết phải biết mọi công nghệ. Điểm khác biệt nằm ở cách họ xử lý những thứ mình chưa biết.

Ví dụ, sếp giao bạn một dự án sử dụng một framework C++ mới, chạy trên Linux, giao tiếp với một thiết bị phần cứng mà bạn chưa từng tiếp xúc.

Có ba cách tiếp cận thường gặp:

- Cách 1 — Người mới: Đọc tài liệu framework từ đầu đến cuối, học cho thật hiểu rồi mới bắt tay vào làm.
- Cách 2 — Người làm theo task: Mở source code, tìm chỗ cần sửa, thử code cho đến khi chạy được.
- Cách 3 — Người tiếp cận theo tư duy hệ thống: Làm rõ kết quả cần đạt, khảo sát kiến trúc, xác định các rủi ro lớn nhất, kiểm chứng tính khả thi, rồi mới xây dựng kế hoạch thực hiện.
    
Cách 3 thường hiệu quả hơn đối với những dự án có nhiều yếu tố chưa rõ. Nó không có nghĩa là bỏ qua việc học hay lập tức thiết kế hệ thống. Nó có nghĩa là học và thiết kế theo thứ tự ưu tiên của dự án, thay vì học mọi thứ theo thứ tự xuất hiện trong tài liệu.

Các phương pháp gồm có: 
	Quy trình tư duy 
	Cách đặt câu hỏi
	Cách đánh giá dự án
	Các phương pháp tiếp cận
	Pitfall dễ mắc phải.

## 1. Trước tiên, phân biệt 3 loại vấn đề

Khi nhận một dự án mới, thường sẽ mang đến cảm giác mình chưa biết gì. 
Nhưng cảm giác đó gộp nhiều loại vấn đề khác nhau, và mỗi loại cần một cách xử lý riêng:

1. **Problem uncertainty — Chưa rõ bài toán**

	Chưa hiểu chính xác cần giải quyết vấn đề gì, đầu ra là gì, tiêu chí nào quyết định thành công.
	Ví dụ: Sếp nói “tích hợp module giao tiếp mới”, nhưng chưa rõ cần thay thế module cũ hoàn toàn hay chỉ bổ sung một giao thức.

2. **Technical uncertainty — Chưa rõ giải pháp kỹ thuật**

	Biết mục tiêu nhưng chưa biết công nghệ, kiến trúc hoặc cách triển khai phù hợp.
	Ví dụ: Chưa biết framework mới xử lý concurrency, event loop, memory ownership hoặc giao tiếp với hardware như thế nào.

3. **Execution uncertainty — Chưa rõ cách hoàn thành**

	Chưa biết cần làm theo thứ tự nào, phụ thuộc ai, cần bao nhiêu thời gian và kiểm thử ra sao.
	Ví dụ: Chưa rõ môi trường build, thiết bị test, quyền truy cập repository hay người phụ trách module liên quan.

**Điểm quan trọng: đừng dùng một phương pháp để giải quyết cả ba loại bất định.**

- Bài toán chưa rõ → hỏi stakeholder, đọc requirement, xác nhận acceptance criteria.
- Kỹ thuật chưa rõ → đọc source, khảo sát kiến trúc, làm prototype.
- Cách thực hiện chưa rõ → lập dependency map, chia milestone, xác định người và tài nguyên cần thiết.

Nếu bạn lao vào học framework trong khi bài toán còn mơ hồ, bạn có thể trở thành chuyên gia về một thứ mà dự án không thực sự cần.

## 2. Quy trình tổng thể: từ lúc nhận task đến lúc tự tin triển khai

Đây là quy trình mình đề xuất cho một dự án mới có độ phức tạp vừa đến cao.

### 01

### Clarify

Hiểu mục tiêu và phạm vi
### 02

### Discover

Khảo sát hệ thống hiện có
### 03

### De-risk

Xác định và kiểm chứng rủi ro lớn
### 04

### Plan

Chọn hướng đi và chia milestone
### 05

### Implement

Phát triển theo từng lát cắt
### 06

### Validate

Kiểm thử, đánh giá và điều chỉnh

Đây không phải quy trình tuyến tính cứng nhắc. Khi phát hiện giả định sai, bạn có thể quay lại bước trước.

## 3. Bước 1 — Clarify: Đừng vội giải quyết thứ mình chưa hiểu

Khi sếp giao dự án, phản xạ đầu tiên của nhiều kỹ sư là hỏi:

- Dùng framework nào?
- Có tài liệu không?
- Có source code mẫu không?
- Bắt đầu code ở đâu?

Đây đều là những câu hỏi hợp lý, nhưng chúng chưa phải câu hỏi quan trọng nhất.
Trước khi tìm hiểu how to build it, hãy làm rõ what problem are we solving và what does success look like?

### 3.1. Năm câu hỏi cần trả lời

| Câu hỏi          | Bạn cần xác định                                                   |
| ---------------- | ------------------------------------------------------------------ |
| **Why?**         | Vì sao dự án này tồn tại? Vấn đề hiện tại là gì?                   |
| **What?**        | Đầu ra cụ thể cần đạt được là gì?                                  |
| **Scope?**       | Phần nào thuộc trách nhiệm của bạn, phần nào không?                |
| **Constraints?** | Deadline, hardware, OS, RAM, CPU, compatibility, coding standards? |
| **Done?**        | Điều kiện nào chứng minh dự án hoàn thành?                         |

Ví dụ, sếp yêu cầu xây dựng một service trên embedded Linux để nhận dữ liệu từ một thiết bị ngoại vi.
Đừng chỉ ghi requirement là “Implement communication service”.

Hãy làm rõ:
- Service nhận loại dữ liệu gì?
- Giao tiếp qua UART, SPI, TCP hay một API có sẵn?
- Có cần đảm bảo latency hoặc throughput không?
- Nếu thiết bị mất kết nối thì phải xử lý thế nào?
- Service có được phép restart không? Ai quản lý lifecycle?
- Test trên hardware thật hay phải hỗ trợ simulation?
- Có cần tương thích với API của hệ thống hiện tại không?

Bạn không nhất thiết phải có tất cả câu trả lời ngay. Mục đích là phân biệt điều gì đã rõ, điều gì chưa rõ và điều gì có thể làm dự án thất bại nếu hiểu sai.

### 3.2. Phân biệt requirement và solution

Đây là một kỹ năng rất quan trọng.
Giả sử sếp nói:

> We need to introduce a new framework to handle asynchronous communication.

**Đây là yêu cầu về giải pháp, chưa chắc là vấn đề gốc.**

Bạn cần tìm hiểu:

- Hệ thống hiện tại đang gặp vấn đề gì?
- Có phải latency quá cao?
- Có quá nhiều thread?
- Khó quản lý lifecycle?
- Hay framework cũ không còn được hỗ trợ?

Tại sao cần phân biệt?

Bởi vì nếu mặc định giải pháp được nêu ra là phương án tối ưu, có thể dành hàng tuần tích hợp một framework phức tạp trong khi vấn đề thật sự chỉ cần một cơ chế event-driven đơn giản.

Tất nhiên, trong môi trường doanh nghiệp, framework có thể là quyết định kiến trúc đã được cấp trên phê duyệt. Chúng ta không nhất thiết phải phản đối. Nhưng vẫn cần hiểu mục tiêu để triển khai đúng và nhận diện các rủi ro.

**Nguyên tắc: Requirement cho biết hệ thống cần đạt điều gì; solution cho biết một cách để đạt điều đó.**

### 3.3. Đầu ra của bước này

Trước khi chuyển sang bước tiếp theo, hãy viết một bản tóm tắt ngắn:

- Objective: Mục tiêu.
- Scope: Phạm vi.
- Constraints: Các giới hạn.
- Acceptance criteria: Tiêu chí nghiệm thu.
- Open questions: Những điểm chưa rõ.
- Assumptions: Những điều đang tạm giả định.

## 4. Bước 2 — Discover: Khảo sát hệ thống trước khi học công nghệ

Sau khi hiểu bài toán, câu hỏi tiếp theo không phải là “Mình phải học framework này trong bao lâu?”

Mà là:

**Mình cần hiểu những phần nào của hệ thống để có thể đưa ra quyết định kỹ thuật đúng?**
Đây là khác biệt giữa học một công nghệ theo giáo trình và học một công nghệ để giải quyết vấn đề.

### 4.1. Khảo sát theo nhiều lớp

Layer 1 — System context
Layer 2 — Architecture
Layer 3 — Implementation
Layer 4 — Build & verification


Đúng rồi. Thực ra phần **"Khảo sát theo nhiều lớp (Layer)"** là một **tư duy general**, không chỉ dành cho software.

Nó xuất phát từ một nguyên lý rất chung:

> Khi gặp một hệ thống phức tạp, đừng nhảy ngay vào chi tiết. Hãy đi từ bối cảnh → cấu trúc → thành phần → vận hành.

Ví dụ trong software, người ta diễn đạt thành:

```
System Context
    ↓
Architecture
    ↓
Implementation
    ↓
Build / Validation
```

Nhưng nếu đổi sang lĩnh vực khác thì các layer sẽ thay đổi.

### Ví dụ 1: Embedded System

Giả sử bạn nhận một ECU mới trong ô tô.

**Layer 1 - System Context**

- ECU này nằm ở đâu trong xe?
- Nói chuyện với CAN nào?
- Input từ cảm biến nào?
- Output điều khiển gì?

**Layer 2 - Architecture**

- Task nào chạy trên RTOS?
- Driver nào quản lý CAN?
- SWC nào xử lý logic?

**Layer 3 - Implementation**

- Source code cụ thể ở đâu?
- CAN callback nào được gọi?
- State machine nào xử lý request?

**Layer 4 - Validation**

- Test bằng HIL?
- Unit test?
- Xe thật?
- Requirement trace?

---

### Ví dụ 2: Nhà máy sản xuất

Nếu được giao phụ trách một dây chuyền mới.

**Layer 1 - System Context**

- Dây chuyền này tạo ra sản phẩm gì?
- Nằm ở công đoạn nào trong toàn nhà máy?

**Layer 2 - Architecture**

- Có những máy nào?
- Luồng nguyên liệu chạy ra sao?

**Layer 3 - Implementation**

- Cách vận hành từng máy?
- Thông số kỹ thuật?

**Layer 4 - Validation**

- Tiêu chuẩn chất lượng?
- KPI sản lượng?
- Tỷ lệ lỗi?

---

### Ví dụ 3: Học một công ty mới khi mới đi làm

**Layer 1 - Context**

- Công ty kiếm tiền bằng cách nào?

**Layer 2 - Structure**

- Các phòng ban liên kết ra sao?

**Layer 3 - Execution**

- Team mình làm gì?
- Process cụ thể thế nào?

**Layer 4 - Measurement**

- KPI là gì?
- Thành công được đo bằng gì?

---

### Ví dụ 3: [[RAG]]


Thực ra điều quan trọng không phải thuộc lòng 4 layer trên, mà là hiểu tư duy:

> Mỗi khi gặp hệ thống mới, hãy hỏi:
> 1. Nó tồn tại trong bối cảnh nào?
> 2. Nó được tổ chức như thế nào?
> 3. Nó hoạt động cụ thể ra sao?
> 4. Làm sao biết nó đang hoạt động đúng?

Đó là một framework tư duy khá phổ quát.

Thậm chí nếu sau này bạn lên **Tech Lead/System Architect**, bạn sẽ thấy senior rất ít khi hỏi:

> "Hàm này viết thế nào?"

mà họ thường hỏi:

> "Module này nằm ở đâu trong hệ thống?"
> 
> "Ai đang gọi nó?"
> 
> "Nếu sửa chỗ này thì ảnh hưởng thành phần nào?"
> 
> "Làm sao chứng minh thay đổi này an toàn?"

Đó chính là tư duy layer-based đang hoạt động phía sau.

### 4.2. Hãy tìm một đường đi xuyên suốt trong source code

Giả sử bạn nhận nhiệm vụ thêm một tính năng xử lý dữ liệu.

Thay vì đọc tất cả các class, hãy truy vết một luồng cụ thể:

`Input → Parser → Business Logic → Output`

Tìm câu trả lời cho các câu hỏi:

- Dữ liệu đi vào từ đâu?
- Ai chịu trách nhiệm validate?
- Logic nghiệp vụ nằm ở đâu?
- Module nào sở hữu dữ liệu?
- Lỗi được truyền đi như thế nào?
- Kết quả được gửi đi đâu?

Khi đã hiểu được một luồng end-to-end, bạn có bản đồ ban đầu của hệ thống. Sau đó mới đào sâu những module liên quan trực tiếp đến task.

### 4.3. Phân biệt những thứ phải học và những thứ chỉ cần biết tồn tại

Ví dụ, framework mới có 30 tính năng. Task hiện tại chỉ dùng 4 tính năng chính.

Bạn có thể chia thành:

- Must understand: Cần hiểu đủ sâu để triển khai đúng.
- Need to know: Biết nó tồn tại, biết tìm tài liệu khi cần.
- Out of scope: Chưa cần nghiên cứu trong task này.

Đây là cách kiểm soát phạm vi học tập. Nếu không có nguyên tắc này, bạn rất dễ rơi vào tutorial hell: đọc nhiều, cảm thấy hiểu nhiều nhưng chưa tạo ra kết quả có thể kiểm chứng.

## 5. Bước 3 — De-risk: Tìm thứ có thể làm dự án thất bại trước tiên

Đây là bước thể hiện rõ nhất tư duy kỹ sư có kinh nghiệm.

Khi chưa biết nhiều về một dự án, bạn không thể chắc chắn toàn bộ thiết kế sẽ đúng. Nhưng bạn có thể chủ động tìm ra những giả định nguy hiểm nhất và kiểm chứng chúng sớm.

### 5.1. Risk không đồng nghĩa với task khó

Một task có thể khó nhưng ít rủi ro vì công nghệ đã ổn định, có tài liệu tốt và đã có người làm tương tự.

Ngược lại, một task có vẻ đơn giản lại có thể rất rủi ro nếu phụ thuộc vào một thư viện chưa được xác minh tương thích với target.

Ví dụ:

- Framework có chạy được trên phiên bản Linux của target không?
- Thư viện có hỗ trợ kiến trúc CPU của thiết bị không?
- API có đáp ứng giới hạn latency không?
- Có build được bằng toolchain của dự án không?
- Có phụ thuộc vào license hoặc thư viện không được phép sử dụng?
- Có tương thích với hệ thống hiện tại không?

Đây là các câu hỏi có thể làm thay đổi hoàn toàn kế hoạch triển khai.

### 5.2. Đánh giá rủi ro theo Impact × Uncertainty

Bạn có thể dùng một mô hình đơn giản:

\[ Risk \approx Impact \times Uncertainty \]

Trong đó:

- Impact: Nếu giả định sai, hậu quả lớn đến đâu?
- Uncertainty: Hiện tại bạn tự tin đến mức nào về giả định đó?

Đây là mô hình ưu tiên thực dụng, không phải công thức định lượng rủi ro chuẩn cho mọi dự án.

Ví dụ:

|Giả định|Impact nếu sai|Mức chưa chắc chắn|Ưu tiên kiểm chứng|
|---|---|---|---|
|Framework build được trên target|Cao|Cao|Rất cao|
|API đáp ứng yêu cầu concurrency|Cao|Cao|Rất cao|
|Tên một helper function|Thấp|Cao|Thấp|
|Có thể tối ưu một đoạn code nhỏ|Thấp|Trung bình|Thấp|

Điểm mấu chốt: đừng ưu tiên câu hỏi dễ trả lời nhất; hãy ưu tiên câu hỏi mà câu trả lời có khả năng làm thay đổi quyết định lớn nhất.

### 5.3. Dùng spike hoặc prototype để giảm rủi ro

Một technical spike là một hoạt động khảo sát kỹ thuật có giới hạn thời gian, nhằm trả lời một câu hỏi cụ thể. Nó không nhất thiết là sản phẩm có thể đưa vào production.

**Prototype** dùng để chứng minh _"cái này trông như thế nào hoặc hoạt động như thế nào với người dùng"_.
**Spike** dùng để chứng minh _"về mặt kỹ thuật có làm được không, khó ở đâu, và rủi ro là gì"_.

Ví dụ:

> Câu hỏi: Framework X có thể chạy trên target Linux của chúng ta và nhận dữ liệu bất đồng bộ hay không?

Spike có thể chỉ cần:

1. Tạo một chương trình tối thiểu.
2. Build bằng toolchain thật.
3. Chạy trên target hoặc môi trường tương đương.
4. Thử một luồng giao tiếp cơ bản.
5. Quan sát log, resource usage và hành vi lỗi cần thiết.
6. Ghi lại kết quả và giới hạn đã phát hiện.

Không cần tạo đầy đủ architecture, logging, configuration hay mọi tính năng production ngay lúc này.

Một spike tốt phải có câu hỏi và điều kiện kết thúc rõ ràng.

Ví dụ:

- Câu hỏi: Có build được với toolchain hiện tại không?
- Thành công: Build và chạy được chương trình mẫu trên target.
- Thất bại: Xác định được incompatibility và phương án thay thế.
- Timebox: Một khoảng thời gian được thống nhất trước với team.

Ngay cả khi prototype thất bại, nó vẫn có giá trị nếu giúp bạn loại bỏ sớm một hướng triển khai không khả thi.

## 6. Bước 4 — Plan: Chọn hướng đi trước khi chia nhỏ công việc

Khi đã có hiểu biết ban đầu và đã kiểm chứng những rủi ro quan trọng, bạn mới nên xây dựng kế hoạch triển khai chi tiết hơn.

Ở bước này, bạn cần tránh hai thái cực:

- Lập kế hoạch cực kỳ chi tiết khi chưa đủ thông tin.
- Không lập kế hoạch gì cả, cứ code rồi tính tiếp.

Cách hợp lý hơn là lập kế hoạch theo từng mức độ chắc chắn.

### 6.1. Chia công việc theo milestone

Giả sử bạn phải tích hợp một framework mới vào hệ thống embedded hiện tại.

M1

Feasibility

Xác nhận toolchain, dependency, khả năng build và chạy trên target.

Deliverable: Báo cáo khả thi và các rủi ro còn lại.

M2

Vertical slice

Triển khai một luồng tối thiểu từ đầu vào đến đầu ra bằng framework mới.

Deliverable: Một luồng end-to-end có thể chạy và kiểm thử.

M3

Functional implementation

Hoàn thiện các chức năng, xử lý lỗi, cấu hình và tích hợp với module liên quan.

Deliverable: Chức năng đáp ứng requirement.

M4

Hardening & delivery

Kiểm thử biên, lỗi, concurrency, resource usage, regression và tài liệu.

Deliverable: Bản phát hành đạt tiêu chí nghiệm thu.

Lợi ích của cách chia này là bạn không cần biết chính xác toàn bộ cách triển khai M4 khi mới bắt đầu M1.

Bạn chỉ cần có đủ thông tin để xác định hướng đi, tiêu chí hoàn thành và rủi ro chính của milestone hiện tại.

### 6.2. Chọn vertical slice thay vì hoàn thiện từng tầng riêng biệt

Một lỗi lập kế hoạch phổ biến là xây dựng toàn bộ framework integration trước, rồi mới làm business logic, rồi cuối cùng mới chạy thử trên target.

Đến lúc tích hợp, bạn có thể phát hiện giả định ban đầu sai.

Thay vào đó, hãy tìm một vertical slice — một lát cắt nhỏ nhưng đi xuyên qua các tầng cần thiết.

Ví dụ:

`Hardware/Input → Adapter → New Framework → Business Logic → Output`

Lát cắt này không cần đầy đủ mọi tính năng. Nó cần đủ để xác nhận các thành phần có thể phối hợp với nhau.

Tuy nhiên, không phải dự án nào cũng nên prototype toàn bộ luồng ngay lập tức. Với hệ thống safety-critical, thay đổi kiến trúc lớn hoặc yêu cầu chứng nhận, bạn có thể phải thực hiện các bước phân tích và phê duyệt chính thức trước khi thử nghiệm.

### 6.3. Đừng quên dependencies

Một task có thể bị chặn không phải vì bạn thiếu kiến thức, mà vì:

- Chưa có hardware.
- Chưa có quyền truy cập repository.
- Team khác chưa hoàn thành API.
- Chưa có toolchain.
- Chưa có yêu cầu chính thức.
- Chưa có dữ liệu để kiểm thử.

Hãy phân biệt:

- Công việc bạn có thể thực hiện ngay.
- Công việc phụ thuộc vào một điều kiện khác.
- Công việc cần quyết định từ cấp trên hoặc team liên quan.

Đó là cách quản lý tiến độ dựa trên thực tế, thay vì chỉ nhìn vào số lượng task.

## 7. Bước 5 — Implement: Học đúng lúc, code đúng phạm vi

Sau khi có kế hoạch, bạn bắt đầu triển khai. Nhưng nguyên tắc vẫn không thay đổi: không cần hiểu tất cả trước khi làm, cũng không được code mà không hiểu những gì có thể ảnh hưởng đến tính đúng đắn.

### 7.1. Dùng vòng lặp nhỏ

Một vòng lặp làm việc hiệu quả có thể là:

### Understand

Xác định hành vi cần đạt

### Implement

Thay đổi nhỏ, có chủ đích

### Verify

Build, test, inspect logs

### Learn

Ghi nhận điều đã xác nhận và điều còn chưa rõ

Lặp lại cho đến khi đạt tiêu chí của từng phần công việc.

Ví dụ, nếu bạn chưa quen với cơ chế callback của framework, đừng vừa viết toàn bộ business logic, vừa thay đổi threading, vừa thêm dependency injection trong cùng một lần sửa.

Hãy tạo một ví dụ tối thiểu để hiểu lifecycle callback, kiểm chứng nó, sau đó áp dụng vào module thực tế.

Điều này làm cho việc debug dễ hơn vì bạn biết thay đổi nào đã gây ra hành vi nào.

### 7.2. Tách điều đã biết, điều đang giả định và điều đã kiểm chứng

Khi làm dự án mới, hãy duy trì một danh sách ngắn:

|Loại|Ví dụ|
|---|---|
|Fact|Framework cung cấp callback khi có dữ liệu mới.|
|Assumption|Callback luôn chạy trên một thread riêng.|
|Verified|Log cho thấy callback đang chạy trên thread của event loop.|
|Open question|Khi shutdown, callback đang chờ được xử lý thế nào?|

Đây là cách giảm tình trạng những phỏng đoán ban đầu dần biến thành “sự thật” trong đầu bạn.

Đặc biệt trong embedded, các giả định về thread, interrupt, buffer ownership, memory lifetime và timing có thể dẫn đến lỗi khó tái hiện.

## 8. Bước 6 — Validate: Chứng minh kết quả, không chỉ chứng minh code chạy

Một dự án không hoàn thành chỉ vì chương trình build thành công hoặc demo được một lần.

Bạn cần xác nhận kết quả dựa trên acceptance criteria đã thống nhất từ đầu.

Tùy loại dự án, việc kiểm chứng có thể gồm:

- Functional correctness.
- Error handling và recovery.
- Boundary conditions.
- Concurrency và race conditions.
- Performance, latency và resource usage.
- Integration và regression tests.
- Khả năng build lại từ môi trường chuẩn.
- Tài liệu và khả năng bàn giao.

Trong embedded, ví dụ service giao tiếp hoạt động tốt khi thiết bị kết nối bình thường chưa chứng minh rằng nó hoạt động đúng khi mất kết nối, nhận dữ liệu sai định dạng hoặc shutdown giữa chừng.

Mỗi rủi ro quan trọng nên được liên kết với một cách kiểm chứng phù hợp.

Nếu đã xác định rủi ro lớn nhất là memory leak, test chức năng thông thường không đủ. Nếu rủi ro là latency, một bài test chỉ xác nhận dữ liệu nhận được cũng không đủ.

# 9. Các phương pháp tiếp cận khác nhau và khi nào nên dùng

Không có một quy trình duy nhất tối ưu cho mọi dự án. Bạn nên chọn phương pháp theo bản chất của vấn đề.

![Risk storming](https://images.openai.com/static-rsc-4/OB9o5YWkS-GZdRpwh5OiEMTevNDseAiLT1pIFkSYmv2BSt0e_KUIb6wztUHw9EuETZljOPNxRWDb7VdE13nY4P8ffo4NTr1ngoGQJU1RfXuKwHeaZdAQxcrqzP8n6EbbOuyHtwkIq-N72bwYqMxkqfpKn2jgvFRt5r4FgFhgnAM?purpose=inline)

A. Top-down — Từ tổng thể xuống chi tiết

Bắt đầu bằng mục tiêu, kiến trúc, module và data flow rồi mới đi vào implementation.

Dùng khi: dự án mới, codebase lớn, nhiều module hoặc yêu cầu chưa rõ.

Điểm mạnh: hiểu được bối cảnh và tránh tối ưu một thành phần không cần thiết.

![Supercharge Your Coding: How Cursor’s MCP Servers and Sequential Thinking Transform Developer Productivity | by Jeffery Alexandro Henry | Medium](https://images.openai.com/static-rsc-4/jumySieKu4IgkBY9WWd9Bjlv8XgX5ua9pUO_e58BNlWICWTK0lEu0_m_aJ6uO_tQxaeBwoE4p1T6LdXLUj2MSryfZZ006wK5uAIAXgKvyhOlczIwvRjsR30kOnNNVRYgTm9ptVPs4dOHpKmtHonuYna0hVMKo9oJHmPwSg7865k?purpose=inline)

B. Bottom-up — Từ thành phần lên hệ thống

Bắt đầu từ một API, library, driver hoặc component nhỏ để hiểu hành vi thực tế, sau đó mở rộng ra toàn hệ thống.

Dùng khi: cần hiểu framework lạ, API khó, driver hoặc vấn đề có thể tái hiện bằng ví dụ nhỏ.

Điểm mạnh: dễ kiểm chứng hành vi và khoanh vùng nguyên nhân.

![Sotware and Firmware Design Services - Teddington Electronics Systems, Cornwall, UK](https://images.openai.com/static-rsc-4/4cyCVsaPNyk7SYf7IoJWk6wvtGfKUkB67vCSI9tJItb8QSe6foRUFTI-Nhajwz3HjhWwR9w2f_6tPAPS7RhhbdiasKgsRzF1gAbpMWNIsL9fGoWh6ljk9UUxtzzqhyAFLG3d3cCHw2avkimI2iq7N3cPfiM_59ZQXE6g-LMF3aI?purpose=inline)

C. Spike / Experimental approach — Thử nghiệm có kiểm soát

Tạo một thử nghiệm nhỏ để xác minh giả định kỹ thuật quan trọng.

Dùng khi: thiếu thông tin, công nghệ mới, compatibility hoặc performance chưa chắc chắn.

Điểm mạnh: thu thập bằng chứng trước khi đầu tư lớn.

![Blog | Zencoder – The AI Coding Agent](https://images.openai.com/static-rsc-4/4um5vLKHOvBeAovVMz2WH5mg4vBS0fp0zsRaxkzdaFVHtRnmlqhYzKVqHdCFiyu8QbhYY5aS5Mu7ragdn2AXy14aHFzuoaejD4i8lvxSjy8wNrRy3CTfEtPsqO8jXi0oXWb5XgghV8mO8TlVc6ZpeWkIZ_7sO12DONoDKmR2OIc?purpose=inline)

D. Incremental / Iterative — Triển khai và hoàn thiện dần

Chia công việc thành các phần có thể kiểm chứng, lấy feedback rồi điều chỉnh.

Dùng khi: yêu cầu có thể thay đổi, dự án nhiều thành phần hoặc cần tích hợp liên tục.

Điểm mạnh: phát hiện vấn đề sớm, giảm chi phí sửa sai về cuối dự án.

Trong thực tế, bạn thường kết hợp cả bốn:

Top-down để định hướng → Bottom-up để hiểu thành phần → Spike để giảm rủi ro → Incremental để triển khai.

Đó là một sự kết hợp tốt cho phần lớn các dự án software engineering có công nghệ mới.

# 10. Pitfalls — Những sai lầm cần đặc biệt tránh

Đây là phần mình muốn bạn chú ý nhất. Nhiều thất bại khi nhận dự án mới không đến từ việc kỹ sư thiếu thông minh, mà đến từ việc phân bổ thời gian và sự chú ý sai chỗ.

Pitfall 1: Học công nghệ trước khi hiểu bài toán

Bạn đọc hàng trăm trang tài liệu nhưng chưa biết phần nào phục vụ yêu cầu thực tế.

Cách sửa: Viết mục tiêu và các câu hỏi kỹ thuật cần giải đáp trước khi lên kế hoạch học. Mỗi chủ đề học nên trả lời một nhu cầu cụ thể của dự án.

Pitfall 2: Đọc code theo thứ tự file

Bạn hiểu nhiều class riêng lẻ nhưng không hiểu luồng thực thi hoặc module nào sở hữu trách nhiệm chính.

Cách sửa: Bắt đầu từ entry point, trace một luồng end-to-end, rồi đọc sâu các thành phần liên quan.

Pitfall 3: Chọn giải pháp trước khi xác định ràng buộc

Bạn thiết kế một kiến trúc đẹp nhưng không phù hợp với RAM, toolchain, coding standard, latency hoặc yêu cầu tương thích.

Cách sửa: Ghi rõ constraints và xác minh các giả định có tác động lớn trước khi chốt kiến trúc.

Pitfall 4: Prototype quá lâu

Prototype ngày càng có nhiều tính năng, bắt đầu trở thành một sản phẩm thứ hai nhưng chưa giải quyết yêu cầu chính.

Cách sửa: Mỗi spike chỉ có một hoặc vài câu hỏi cụ thể, timebox rõ ràng và tiêu chí dừng. Sau đó quyết định tiếp tục, đổi hướng hay dừng.

Pitfall 5: Giả định nhưng không xác minh

Ví dụ, bạn cho rằng API thread-safe, callback không bao giờ chạy sau khi object bị hủy, hoặc một thao tác luôn hoàn thành đồng bộ.

Cách sửa: Kiểm tra documentation, implementation, test hoặc hành vi runtime. Ghi lại điều chưa chắc chắn thay vì tự suy diễn.

Pitfall 6: Im lặng quá lâu khi bị chặn

Bạn dành vài ngày giải quyết một vấn đề phụ thuộc vào team khác, nhưng không báo cáo vì nghĩ rằng mình phải tự xử lý được.

Cách sửa: Báo cáo sớm vấn đề, tác động, những gì đã thử và quyết định cần hỗ trợ. Tự chủ không có nghĩa là làm mọi thứ một mình.

Pitfall 7: Hứa deadline khi chưa biết đủ

Bạn ước lượng dựa trên cảm giác hoặc thời gian học công nghệ, không tính đến integration, testing và các dependency.

Cách sửa: Tách phần đã biết và chưa biết. Ước lượng sơ bộ trước, sau đó cập nhật khi spike và khảo sát đã giảm bất định.

Pitfall 8: Tập trung vào code thay vì kết quả

Bạn hoàn thành nhiều commit nhưng không có bằng chứng tính năng đạt yêu cầu.

Cách sửa: Gắn mỗi milestone với deliverable và tiêu chí kiểm chứng. Đo tiến độ bằng kết quả đã xác nhận, không chỉ bằng lượng code đã viết.

# 11. Làm sao để giao tiếp với sếp mà vẫn thể hiện sự chuyên nghiệp?

Một kỹ sư chuyên nghiệp không cần giả vờ mình biết mọi thứ. Điều quan trọng là trình bày rõ mức độ hiểu biết, kế hoạch xử lý và rủi ro.

Có ba tình huống thường gặp.

### Tình huống A — Bạn chưa hiểu rõ yêu cầu

Thay vì chỉ nói “I don't understand the requirement”, hãy làm rõ điểm cần quyết định.

I understand the overall objective. I’d like to clarify a few details about the expected behavior and acceptance criteria before finalizing the implementation approach.

I’ll review the existing architecture in parallel and come back with the open questions and a proposed plan.

Thông điệp này cho thấy bạn không đứng yên chờ người khác giải thích. Bạn chủ động xử lý những phần có thể làm ngay, đồng thời xác định phần cần làm rõ.

### Tình huống B — Bạn chưa từng làm công nghệ đó

Đừng hứa rằng mình sẽ làm được ngay khi chưa biết độ khó. Cũng đừng tự đánh giá mình không đủ năng lực chỉ vì công nghệ mới.

I haven’t worked with this framework before, so I’ll first assess how it fits into our current system, verify the key technical dependencies, and identify any major risks.

Once I have that initial assessment, I’ll be able to propose a more reliable implementation plan and estimate.

Điều bạn đang cam kết không phải là biết trước mọi thứ. Bạn cam kết một quy trình giảm bất định để đưa ra đánh giá đáng tin cậy hơn.

### Tình huống C — Bạn phát hiện rủi ro có thể ảnh hưởng deadline

Báo cáo theo cấu trúc:

1. Finding: Bạn phát hiện điều gì?
2. Impact: Nó ảnh hưởng đến đâu?
3. Evidence: Bằng chứng hiện tại là gì?
4. Options: Có những hướng xử lý nào?
5. Recommendation: Bạn đề xuất hướng nào và vì sao?
6. Decision needed: Có cần sếp quyết định điều gì không?

Ví dụ:

The initial integration test revealed a compatibility issue with our current toolchain. This may affect the planned delivery date.

I’ve confirmed the issue with a minimal build and identified two possible approaches: adapting the dependency or evaluating an alternative library. I’m assessing the impact of both options and will share a recommendation, including the trade-offs, before we commit to the implementation path.

Đây là cách giao tiếp có giá trị vì bạn mang đến cả vấn đề lẫn phương án xử lý.

# 12. Một checklist thực tế cho ngày đầu tiên nhận dự án

Bạn có thể dùng checklist này để tránh bỏ sót những việc quan trọng. Không cần hoàn thành tất cả trong ngày đầu; hãy dùng nó để xác định bước tiếp theo.

## Project onboarding checklist

### 0/16

### Hiểu bài toán

Tôi diễn đạt được mục tiêu dự án bằng lời của mình.

Tôi biết phạm vi và phần việc thuộc trách nhiệm của mình.

Tôi biết acceptance criteria hoặc các điểm cần xác nhận.

Tôi đã ghi lại các câu hỏi còn mở.

### Hiểu hệ thống

Tôi tìm được repository, tài liệu và người liên hệ chính.

Tôi biết cách build, chạy và test baseline.

Tôi đã xác định entry point và các module liên quan.

Tôi đã trace được ít nhất một luồng dữ liệu hoặc luồng xử lý quan trọng.

### Giảm rủi ro

Tôi đã liệt kê các giả định kỹ thuật quan trọng.

Tôi đã ưu tiên các rủi ro có impact cao.

Tôi biết cần spike nào để xác minh tính khả thi.

Tôi đã kiểm tra các dependency và blocker quan trọng.

### Kế hoạch và giao tiếp

Tôi có milestone đầu tiên với deliverable rõ ràng.

Tôi biết những dependency cần team khác hỗ trợ.

Tôi biết khi nào và bằng cách nào sẽ cập nhật tiến độ.

Tôi chưa đưa ra cam kết deadline vượt quá bằng chứng hiện có.

Reset Copy checklist

# 13. Một tầng tư duy sâu hơn: Quản lý sự bất định

Đến đây, bạn có thể thấy các bước trên thực chất liên kết với nhau bởi một nguyên tắc chung.

Khi nhận một dự án mới, bạn không chỉ đang viết phần mềm. Bạn đang ra quyết định trong một môi trường mà thông tin chưa đầy đủ.

Bạn chưa biết chính xác:

- Giải pháp nào sẽ hoạt động.
- Phần nào sẽ tốn nhiều thời gian.
- Giả định nào sẽ sai.
- Tích hợp có gặp trở ngại không.
- Thiết kế ban đầu có cần thay đổi không.

Vì vậy, hãy xem dự án như một quá trình giảm bất định qua từng vòng lặp.

### Unknowns

Những điều chưa biết và các giả định chưa kiểm chứng

### Questions & hypotheses

Xác định điều gì cần biết và giả thuyết nào cần kiểm tra

### Experiments & evidence

Đọc source, chạy thử, kiểm thử và thu thập bằng chứng

### Decisions

Chọn hướng đi, cập nhật estimate và triển khai

Kết quả thực tế có thể tạo ra câu hỏi mới. Lặp lại chu trình khi cần.

Có một hệ quả quan trọng: không phải mọi thứ chưa biết đều cần được giải quyết ngay.

Bạn cần phân biệt:

- Điều chưa biết nhưng chưa ảnh hưởng đến quyết định hiện tại.
- Điều chưa biết có thể trì hoãn việc triển khai.
- Điều chưa biết nếu phát hiện quá muộn sẽ gây chi phí sửa sai rất lớn.

Loại thứ ba cần được ưu tiên.

Ví dụ, việc bạn chưa hiểu một API phụ trợ chưa chắc đáng lo. Nhưng việc chưa biết framework có thể chạy trên target hay không lại có thể khiến toàn bộ kế hoạch phải làm lại.

Đó chính là lý do người có kinh nghiệm thường tập trung vào những câu hỏi có khả năng thay đổi quyết định, thay vì cố gắng xóa bỏ mọi lỗ hổng kiến thức cùng một lúc.

## 14. Cuối cùng, bạn nên xây dựng thói quen nào?

Nếu phải chọn ra một bộ nguyên tắc ngắn gọn để áp dụng vào mỗi dự án mới, mình sẽ chọn năm nguyên tắc sau:

1. Understand before optimizing: Hiểu bài toán và ràng buộc trước khi tối ưu giải pháp.
2. Investigate before assuming: Tách sự thật khỏi giả định, xác minh điều quan trọng.
3. Test the riskiest assumption first: Kiểm chứng giả định nguy hiểm nhất trước khi đầu tư lớn.
4. Deliver evidence, not just activity: Tạo ra kết quả có thể kiểm chứng, không chỉ tạo ra nhiều công việc.
5. Communicate uncertainty early: Báo cáo điều chưa rõ, blocker và rủi ro trước khi chúng biến thành vấn đề tiến độ.

Và có một điểm cần lưu ý: quy trình này không có nghĩa mọi task nhỏ đều phải trải qua sáu bước đầy đủ. Nếu chỉ là một bug nhỏ, có thể tái hiện rõ ràng trong codebase quen thuộc, bạn có thể đi thẳng vào debug và test. Quy trình đầy đủ phù hợp hơn khi phạm vi lớn, công nghệ mới, nhiều phụ thuộc hoặc chi phí sửa sai cao.

Đích đến không phải là trở thành người biết tất cả mọi thứ. Đích đến là trở thành người có thể tiếp nhận một vấn đề chưa quen thuộc, nhanh chóng xây dựng mô hình hiểu biết đủ tốt, đưa ra quyết định có căn cứ và tạo ra kết quả đáng tin cậy.

Với nền tảng embedded C++ của bạn, mình nghĩ bước nâng cấp tư duy có giá trị nhất là chuyển từ câu hỏi “Mình cần học những gì để làm được task này?” sang câu hỏi “Mình cần xác minh điều gì để biết cách làm nào là đúng, khả thi và ít rủi ro nhất?”.

Sự thay đổi đó có thể không làm bạn viết code nhanh hơn ngay trong ngày đầu tiên, nhưng sẽ giúp bạn tránh rất nhiều giờ làm sai hướng trong những dự án lớn hơn.