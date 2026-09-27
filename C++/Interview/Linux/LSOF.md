Dưới đây là chi tiết về các tùy chọn (options) quan trọng của lệnh `lsof` và tổng hợp các câu hỏi phỏng vấn thực tế từ cơ bản đến nâng cao (thường gặp trong các buổi phỏng vấn Linux Admin, DevOps, SRE). [1, 2]

---

## 📑 Bảng tổng hợp các Option phổ biến của `lsof`

Mặc định, khi bạn kết hợp nhiều option (ví dụ: `lsof -u root -i`), `lsof` sẽ hiểu theo phép toán OR (hiển thị tệp của root _HOẶC_ tệp mạng). [3]

|Tùy chọn (Option) [2, 3, 4, 5, 6, 7, 8]|Chức năng chi tiết|Ví dụ thực tế|
|---|---|---|
|`-i`|Lọc theo kết nối mạng (Internet). Có thể chỉ định giao thức, cổng hoặc IP.|`lsof -i :80` _(Xem cổng 80)_  <br>`lsof -i tcp` _(Chỉ xem giao thức TCP)_|
|`-u`|Lọc các tệp được mở bởi một User cụ thể.|`lsof -u www-data`|
|`-c`|Lọc theo tên Command (Tiến trình/Ứng dụng).|`lsof -c nginx`|
|`-p`|Lọc theo mã tiến trình (PID).|`lsof -p 2415`|
|`-a`|Áp dụng phép toán AND thay vì OR khi kết hợp các option.|`lsof -a -u root -i` _(Chỉ xem kết nối mạng của root)_|
|`-n`|Không phân giải tên miền (hiển thị IP dạng số), giúp lệnh chạy nhanh hơn rất nhiều.|`lsof -n -i`|
|`-P`|Không phân giải tên cổng (hiển thị số port thay vì tên dịch vụ như http, ssh).|`lsof -P -i`|
|`+D`|Tìm tất cả các file đang mở thuộc một Thư mục và các thư mục con của nó.|`lsof +D /var/log/`|
|`-t`|Chỉ xuất ra duy nhất số PID (Dùng để tối ưu khi viết script lồng lệnh).|`kill -9 $(lsof -t -i :8080)` _(Tắt nhanh tiến trình chiếm port)_|
|`^`|Ký tự phủ định (loại trừ), đặt trước User hoặc PID.|`lsof -u ^root` _(Xem file mở bởi tất cả user trừ root)_|

---

## ❓ Các câu hỏi phỏng vấn về `lsof` (Kèm câu trả lời)

## 1. Câu hỏi cơ bản (Dành cho Fresher / Junior Linux Admin)

Q1: Lệnh `lsof` là gì và tại sao nó lại quan trọng trong Linux?

- Trả lời: `lsof` là viết tắt của _List Open Files_. Trong Linux, triết lý thiết kế là _"Everything is a file"_ (Mọi thứ đều là tệp - từ file cấu hình, thư mục, thiết bị phần cứng đến kết nối mạng). Do đó, `lsof` cho phép người quản trị nhìn thấy toàn bộ tài nguyên hệ thống đang bị chiếm dụng bởi tiến trình nào, giúp chẩn đoán lỗi hiệu quả. [1, 6, 9, 10, 11]

Q2: Làm thế nào để tìm nhanh tiến trình nào đang chiếm dụng cổng `8080`?

- Trả lời: Sử dụng lệnh: `sudo lsof -i :8080`. Để lấy chính xác mã PID nhằm viết kịch bản tự động tắt dịch vụ, ta thêm option `-t`: `lsof -t -i :8080`. [4, 5, 6]

Q3: Phân biệt sự khác nhau giữa `lsof /var/log` và `lsof +D /var/log`?

- Trả lời:
    
    - `lsof /var/log` chỉ kiểm tra các tiến trình đang mở trực tiếp chính thư mục `/var/log` đó.
    - `lsof +D /var/log` sẽ quét đệ quy (recursive), hiển thị tất cả các tiến trình đang mở bất kỳ tệp hoặc thư mục con nào nằm bên trong `/var/log`. [4, 5]
    

---

## 2. Câu hỏi tình huống & Nâng cao (Dành cho Senior / DevOps / SRE)

Q4: [Tình huống] Ổ đĩa báo đầy 100% (`df -h`), bạn đã dùng `rm` để xóa một file log nặng 50GB nhưng dung lượng đĩa vẫn không giảm. Bạn xử lý thế nào bằng `lsof`?

- Trả lời:
    
    - Nguyên nhân: Khi dùng `rm`, tệp chỉ bị xóa trên danh nghĩa (bỏ liên kết - unlink). Nếu một tiến trình vẫn đang mở và ghi vào file đó, hệ điều hành sẽ không giải phóng các block dữ liệu trên ổ đĩa.
    - Cách xử lý:
        
        1. Chạy lệnh: `sudo lsof | grep deleted` để tìm tiến trình đang giữ file đã xóa. Kết quả sẽ hiển thị dạng `(deleted)` ở cuối dòng.
        2. Xác định `PID` của tiến trình đó và thực hiện khởi động lại (restart) dịch vụ (hoặc dùng `kill -HUP <PID>`) để giải phóng dung lượng ổ đĩa một cách an toàn mà không cần khởi động lại máy chủ. [4, 12]
        
    

Q5: Làm thế nào để lọc ra các kết nối mạng đang ở trạng thái `LISTEN` bằng `lsof`?

- Trả lời: Ta có thể kết hợp bộ lọc giao thức và trạng thái thông qua cú pháp:
    
    ```bash
    sudo lsof -i TCP -s TCP:LISTEN -n -P
    ```
    
    _(Trong đó `-s TCP:LISTEN` bắt buộc `lsof` chỉ hiển thị các socket đang lắng nghe kết nối)._

Q6: Option `-a` hoạt động như thế nào? Chuyện gì xảy ra nếu chạy `lsof -u root -i tcp` so với `lsof -a -u root -i tcp`?

- Trả lời:
    
    - Lệnh `lsof -u root -i tcp` áp dụng phép OR: Kết quả trả về gồm tất cả các file mở bởi user `root` HOẶC tất cả các kết nối mạng `tcp` của toàn bộ hệ thống.
    - Lệnh `lsof -a -u root -i tcp` áp dụng phép AND: Kết quả trả về bắt buộc phải thỏa mãn cả 2 điều kiện cùng lúc (chỉ hiển thị kết nối mạng `tcp` được mở bởi riêng user `root`). [3]
    

Q7: Tại sao lệnh `lsof -i` đôi khi chạy rất chậm hoặc bị "treo" vài giây? Làm thế nào để khắc phục?

- Trả lời:
    
    - Nguyên nhân: Mặc định, `lsof` sẽ cố gắng thực hiện tra cứu DNS ngược (Reverse DNS lookup) để dịch địa chỉ IP thành Hostname và dịch số cổng thành tên dịch vụ (ví dụ: biến `80` thành `http`). Nếu hệ thống gặp vấn đề về phân giải DNS, lệnh sẽ bị nghẽn.
    - Khắc phục: Thêm hai tùy chọn `-n` (No DNS) và `-P` (No Port name) để bỏ qua quá trình dịch này, lệnh sẽ trả kết quả lập tức: `lsof -nP -i`. [3, 4]
    

---

Để giúp bạn chuẩn bị tốt nhất, bạn đang hướng tới vị trí công việc cụ thể nào (SysAdmin, DevOps hay Cloud Engineer) để tôi có thể thiết kế thêm các câu hỏi tình huống thực tế sát nhất với vị trí đó?

  

[1] [https://lanit.com.vn](https://lanit.com.vn/lenh-lsof-tren-linux.html)

[2] [https://www.scaler.com](https://www.scaler.com/topics/lsof-command-in-linux/)

[3] [https://knowledge.dhound.io](https://knowledge.dhound.io/security-practices/cheatsheets/lsof-cheatsheet)

[4] [https://linux-audit.com](https://linux-audit.com/cheat-sheets/lsof/)

[5] [https://www.cheat-sheets.org](https://www.cheat-sheets.org/project/tldr/command/lsof/)

[6] [https://quickref.me](https://quickref.me/lsof.html)

[7] [https://phoenixnap.com](https://phoenixnap.com/kb/lsof-command)

[8] [https://linuxize.com](https://linuxize.com/cheatsheet/lsof/)

[9] [https://dotrungquan.info](https://dotrungquan.info/su-dung-lenh-lsof-trong-linux/)

[10] [https://vietnix.vn](https://vietnix.vn/lenh-lsof-trong-linux/)

[11] [https://blogd.net](https://blogd.net/linux/huong-dan-dung-lenh-lsof-co-ban/)

[12] [https://bizflycloud.vn](https://bizflycloud.vn/tin-tuc/10-vi-du-su-dung-chuong-trinh-lenh-lsof-tren-linux-20180309115630683.htm)