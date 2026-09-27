Để dừng một tiến trình (process) trong Linux, bạn có thể sử dụng các lệnh kinh điển như `kill`, `pkill`, hoặc `killall`. Cách thức thực hiện phụ thuộc vào việc bạn biết Mã tiến trình (PID) hay Tên của tiến trình. [1, 2, 3, 4, 5]

Dưới đây là hướng dẫn chi tiết các bước từ tìm kiếm đến tiêu diệt một tiến trình, kèm theo các câu hỏi phỏng vấn thường gặp về chủ đề này. [6, 7]

---

## 🚀 3 Bước dừng một tiến trình bằng PID (Cách an toàn nhất) [8]

## Bước 1: Tìm PID của tiến trình [9]

Sử dụng lệnh `ps` hoặc `pgrep` để tìm mã số PID của ứng dụng (ví dụ bạn muốn dừng `nginx`): [10, 11, 12]

```bash
ps -ef | grep nginx
# Hoặc dùng lệnh ngắn hơn:
pgrep nginx
```

## Bước 2: Dừng tiến trình một cách an toàn (Gửi tín hiệu SIGTERM)

Mặc định, lệnh `kill` sẽ gửi tín hiệu SIGTERM (Signal 15). Tín hiệu này yêu cầu tiến trình tự đóng các tệp đang mở, lưu lại dữ liệu và tự giải phóng bộ nhớ trước khi tắt. [13, 14, 15, 16, 17]

```bash
sudo kill <PID>
# Ví dụ: sudo kill 1234
```

## Bước 3: Ép buộc dừng ngay lập tức (Gửi tín hiệu SIGKILL) [18, 19]

Nếu tiến trình bị treo, bị đơ và không phản hồi lệnh `kill` thông thường, bạn buộc phải dùng tín hiệu mạnh nhất là SIGKILL (Signal 9). Tín hiệu này sẽ kết thúc tiến trình ngay lập tức mà không cho phép nó lưu dữ liệu. [20, 21, 22, 23]

```bash
sudo kill -9 <PID>
# Hoặc: sudo kill -SIGKILL <PID>
```

---

## 🎯 Cách dừng tiến trình bằng Tên (Không cần tìm PID) [24, 25]

Nếu bạn không muốn mất công tìm số PID, bạn có thể tắt trực tiếp bằng tên của ứng dụng:

- Dùng `pkill` (Hỗ trợ tìm kiếm theo tên gần đúng):
    
    ```bash
    sudo pkill nginx
    ```
    
- Dùng `killall` (Tắt chính xác mọi tiến trình trùng tên):
    
    ```bash
    sudo killall chrome
    ```
    
    [26, 27, 28, 29, 30]

---

## ❓ Các câu hỏi phỏng vấn về "Dừng tiến trình" (Kèm câu trả lời)

## Q1: Sự khác biệt lớn nhất giữa `kill -15` (SIGTERM) và `kill -9` (SIGKILL) là gì? Khi nào bạn nên dùng cái nào? [31, 32, 33]

- Trả lời:
    
    - `kill -15` (SIGTERM): Là tín hiệu lịch sự. Hệ điều hành gửi yêu cầu dừng và tiến trình có quyền bắt lấy tín hiệu này (catch) để thực hiện dọn dẹp bộ nhớ, đóng kết nối cơ sở dữ liệu và lưu lại công việc trước khi chết. Luôn luôn dùng lệnh này đầu tiên.
    - `kill -9` (SIGKILL): Là tín hiệu cưỡng ép. Tiến trình không thể bắt (catch) hoặc bỏ qua tín hiệu này. Hệ điều hành sẽ xóa bỏ tiến trình khỏi bộ nhớ ngay lập tức. Chỉ dùng khi tiến trình bị treo hoàn toàn. Hậu quả của `kill -9` có thể làm hỏng (corrupt) file dữ liệu đang ghi dở. [34, 35, 36, 37, 38]
    

## Q2: Có tín hiệu (Signal) nào khác của lệnh `kill` mà một DevOps/SysAdmin nên biết không?

- Trả lời: Có 2 tín hiệu rất phổ biến khác:
    
    - `kill -1` (SIGHUP): Thường dùng để reload (tải lại) file cấu hình của các dịch vụ (như Nginx, Apache) mà không cần phải dừng hẳn dịch vụ (không làm gián đoạn người dùng kết nối).
    - `kill -19` (SIGSTOP): Dùng để tạm dừng (pause) một tiến trình lại thay vì giết chết nó. Để tiếp tục chạy lại tiến trình đó, ta gửi tín hiệu `kill -18` (SIGCONT). [39, 40]
    

## Q3: [Tình huống] Bạn chạy lệnh `sudo kill -9 <PID>` nhưng tiến trình đó vẫn cứng đầu xuất hiện và không hề biến mất. Nguyên nhân do đâu và bạn xử lý thế nào?

- Trả lời: Có hai nguyên nhân chính cho tình huống này:
    
    1. Tiến trình đang ở trạng thái Uninterruptible Sleep (Trạng thái `D` trong lệnh `ps`): Tiến trình này thường đang đợi một tiến trình I/O phần cứng (như đọc ổ đĩa NFS bị mất kết nối, hoặc phần cứng bị lỗi). Lúc này, nhân Linux (Kernel) bảo vệ tiến trình để tránh hỏng dữ liệu, nên nó sẽ bỏ qua cả `kill -9`. Cách duy nhất để xử lý là khởi động lại hệ điều hành (reboot) hoặc khắc phục lỗi kết nối phần cứng đó.
    2. Đó là một tiến trình Zombie (Trạng thái `Z`): Tiến trình này thực chất đã chết rồi, nó chỉ còn là một cái bóng trong bảng quản lý. Bạn không thể `kill` một thứ đã chết. Để xóa nó, bạn phải tìm PPID (Mã tiến trình cha) của nó bằng lệnh `ps -ef` rồi `kill` hoặc restart tiến trình cha đó. [41, 42, 43, 44, 45]
    

---

Nếu bạn muốn tiếp tục mở rộng kiến thức, bạn có muốn tìm hiểu về cách chạy một tiến trình dưới nền (Background/Foreground với `&`, `bg`, `fg`) hay cách quản lý chúng qua Systemd (`systemctl`) không? [46]

  

[1] [https://serveravatar.com](https://serveravatar.com/kill-a-running-process-in-linux/)

[2] [https://blog.udemy.com](https://blog.udemy.com/linux-kill-process/)

[3] [https://www.geeksforgeeks.org](https://www.geeksforgeeks.org/linux-unix/how-to-kill-processes-by-given-partial-names-in-linux/)

[4] [https://labex.io](https://labex.io/tutorials/linux-terminate-processes-in-linux-44)

[5] [https://linuxize.com](https://linuxize.com/post/how-to-kill-a-process-in-linux/)

[6] [https://www.bizmanualz.com](https://www.bizmanualz.com/library/what-does-kill-command-mean)

[7] [https://1gbits.com](https://1gbits.com/blog/kill-a-process-in-linux/)

[8] [https://www.baeldung.com](https://www.baeldung.com/linux/kill-background-process)

[9] [https://1gbits.com](https://1gbits.com/blog/kill-a-process-in-linux/)

[10] [https://builtin.com](https://builtin.com/articles/kill-process-linux)

[11] [https://blog.udemy.com](https://blog.udemy.com/linux-kill-process/)

[12] [https://docs.oracle.com](https://docs.oracle.com/cd/E19455-01/806-2902/othercommands-9/index.html)

[13] [https://www.ibm.com](https://www.ibm.com/docs/en/zos/3.1.0?topic=descriptions-kill-end-process-job-send-it-signal)

[14] [https://baransel.dev](https://baransel.dev/post/cli-how-to-terminate-process/)

[15] [https://www.linkedin.com](https://www.linkedin.com/posts/upopovic_heres-a-linux-tip-when-you-kill-a-process-activity-7393339346059309056-VIC6)

[16] [https://payaldungarwal.files.wordpress.com](https://payaldungarwal.files.wordpress.com/2016/01/to-study-and-implement-ps-and-kill-command-in-linux.pdf)

[17] [https://superuser.com](https://superuser.com/questions/49024/kill-9-programs-but-they-still-hang-on)

[18] [https://superuser.com](https://superuser.com/questions/872244/killing-processes-in-raspbian)

[19] [https://linuxize.com](https://linuxize.com/post/how-to-kill-a-process-in-linux/)

[20] [https://linuxize.com](https://linuxize.com/post/how-to-kill-a-process-in-linux/)

[21] [https://www.linkedin.com](https://www.linkedin.com/posts/upopovic_heres-a-linux-tip-when-you-kill-a-process-activity-7393339346059309056-VIC6)

[22] [https://community.qlik.com](https://community.qlik.com/t5/Qlik-Replicate/How-Kill-process-task-when-Console-in-Windows-and-Server-in/td-p/2547299)

[23] [https://www.geeksforgeeks.org](https://www.geeksforgeeks.org/linux-unix/shell-scripting-how-to-send-signal-to-a-processes/)

[24] [https://www.hostitsmart.com](https://www.hostitsmart.com/manage/knowledgebase/486/kill-process-in-linux.html)

[25] [https://www.pair.com](https://www.pair.com/support/kb/paircloud-using-kill-killall-and-pkill/)

[26] [https://blog.udemy.com](https://blog.udemy.com/linux-kill-process/)

[27] [https://pimylifeup.com](https://pimylifeup.com/linux-kill-process/)

[28] [https://linuxopsys.substack.com](https://linuxopsys.substack.com/p/linux-process-signals-explained)

[29] [https://shasheenrashmina.medium.com](https://shasheenrashmina.medium.com/mastering-process-management-in-rhel-essential-commands-d841053c9b1b)

[30] [https://mackeeper.com](https://mackeeper.com/blog/how-to-force-quit-chrome-on-mac/)

[31] [https://monovm.com](https://monovm.com/blog/kill-process-in-ubuntu/)

[32] [https://akaabachi.medium.com](https://akaabachi.medium.com/respect-of-the-kill-how-to-properly-terminate-your-linux-processes-99f6025f2e53)

[33] [https://linuxize.com](https://linuxize.com/post/kill-command-in-linux/)

[34] [https://akaabachi.medium.com](https://akaabachi.medium.com/respect-of-the-kill-how-to-properly-terminate-your-linux-processes-99f6025f2e53)

[35] [https://www.zemris.fer.hr](https://www.zemris.fer.hr/predmeti/os/pripreme/z1_Lab1_signals.pdf)

[36] [https://labex.io](https://labex.io/lesson/process-signals)

[37] [https://cloudxlab.com](https://cloudxlab.com/assessment/displayslide/66/process-hierarchy)

[38] [https://unix.stackexchange.com](https://unix.stackexchange.com/questions/260675/difference-between-stop-kill-and-terminate-in-xfce-task-manager-1-0-1)

[39] [https://labex.io](https://labex.io/questions/what-is-the-purpose-of-kill-command-in-linux-44)

[40] [https://askubuntu.com](https://askubuntu.com/questions/1007621/pause-a-screen-terminal)

[41] [https://community.hpe.com](https://community.hpe.com/t5/operating-system-hp-ux/how-do-you-kill-a-hung-unix-session/td-p/2882903)

[42] [https://serverfault.com](https://serverfault.com/questions/579158/difference-between-calling-tomcat-shutdown-script-and-killing-process)

[43] [https://adamtheautomator.com](https://adamtheautomator.com/linux-kill-process/)

[44] [https://www.ibm.com](https://www.ibm.com/docs/en/imdm/11.6.0?topic=processor-stopping-batch-jobs)

[45] [https://serverfault.com](https://serverfault.com/questions/12503/what-is-a-zombie-process-and-how-do-i-kill-it)

[46] [https://www.opensourceforu.com](https://www.opensourceforu.com/2023/08/mastering-processes-in-linux-a-comprehensive-tutorial/)