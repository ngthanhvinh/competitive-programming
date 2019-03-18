# Copy and Paste 2

- Thời gian: 1s
- Bộ nhớ: 256MB

Một trong những tính năng quan trọng của một trình sửa văn bản là sao chép và dán (copy và paste). Công ty JOI đang thiết kế một trình sửa văn bản có khả năng copy và paste trong thời gian rất ngắn. Là một trong những lập trình viên triển vọng của công ty, bạn là người được giao trọng trách kiểm tra chức năng cốt lõi này. JOI đặt cả vận mệnh công ty vào phần mềm mới này, nên công việc của bạn là đảm bảo chức năng phải đúng và chạy nhanh nhất có thể.

Tóm tắt miêu tả chức năng như sau: Ban đầu văn bản là một xâu kí tự $S$. Các thao tác copy và paste sẽ được thực hiện $N$ lần. Trong thao tác thứ $i$, đoạn kí tự liên tiếp từ $A_i$ đến $B_i$ sẽ được sao chép và dán vào vị trí thứ $C_i$ của xâu. Vị trí $x$ được định nghĩa là khoảng trống ngay sau $x$ kí tự đầu tiên của xâu (vị trí $0$ là vị trị đầu của xâu). Ví dụ, trong xâu `copypaste`, vị trí $6$ là
khoảng trống nằm giữa kí tự `a` và kí tự `s`; vị trí $9$ là khoảng trống sau kí tự `e` - tức cuối xâu. Tuy nhiên, sau khi thực hiện thao tác, nếu xâu có độ dài lớn hơn $M$, các kí tự ở cuối sẽ được xóa dần cho đến khi chỉ còn đúng $M$ kí tự.

Để tạo ra một test cho trình sửa văn bản, bạn cần tìm trước $K$ kí tự đầu của xâu sau $N$ truy vấn.

## Yêu cầu

Cho số nguyên $K$, $M$ là giới hạn độ dài xâu, xâu ban đầu $S$ và $N$ truy vấn copy-paste, hãy tìm ra $K$ kí tự đầu tiên của xâu sau khi thực hiện tất cả truy vấn.

## Dữ liệu nhập vào

Hãy đọc từ standard input dữ liệu theo định dạng sau:

- Dòng thứ nhất gồm 2 số $K$ và $M$ cách nhau bởi khoảng trống. $K$ thể hiện số kí tự cần in ra, $M$ thể hiện giới hạn độ dài xâu sau mọi truy vấn. 
- Dòng thứ hai gồm một xâu duy nhất $S$ là xâu ban đầu của văn bản.
- Dòng thứ ba ghi một số duy nhất $N$, số truy vấn.
- $N$ dòng tiếp theo, mỗi dòng thể hiện một truy vấn. Dòng thứ $i$ gồm 3 số $A_i$, $B_i$ và $C_i$, bạn cần copy đoạn từ $A_i$ đến $B_i$ và dán vào vị trí $C_i$.

## Dữ liệu in ra

Hãy in ra standard output một dòng duy nhất gồm $K$ kí tự là $K$ kí tự đầu tiên của xâu sau $N$ truy vấn.

## Giới hạn

Gọi $S'$ là xâu $S$ sau tất cả truy vấn.

Trong tất cả các test:

- $1 \le K \le 200$
- $1 \le M \le 10^9$
- Xâu $S$ chỉ gồm các kí tự Latin thường (`a` đến `z`).
- $K \le |S| \le \min(M, 200 000)$
- $1 \le N \le 200 000$
- Gọi $L_i$ là độ dài của xâu sau truy vấn thứ $i$, ta có $0 \le A_i < B_i \le L_i$ và $0 \le C_i \le L_i$ với mọi $i$.

## Subtask
### Subtask 1 (10 điểm)
Các test có thêm giới hạn sau:

- $M \le 2000$
- $N \le 2000$

### Subtask 2 (90 điểm)
Không có giới hạn gì thêm.

## Ví dụ
### Input 1
```
2 18
copypaste
4
3 6 8
1 5 2
4 12 1
17 18 0
```
### Output 1
```
ac
```
Trong test này, có 4 truy vấn:

- Ban đầu, xâu là `copypaste`.
- Trong truy vấn đầu tiên, đoạn `ypa` (3 đến 6) được copy vào vị trí số $8$, biến xâu thành `copypastypae`.
- Truy vấn thứ 2, `opyp` (1 đến 5) được copy vào $2$,
xâu trở thành `coopyppypastypae`.
- Truy vấn thứ 3, `yppypast` (4 đến 12) được copy vào
$1$, xâu trở thành `cyppypastoopyppypastypae`. Tuy nhiên khi đó độ dài xâu vượt quá $M = 18$ nên bị cắt
thành `cyppypastoopyppypa`.
- Truy vấn cuối cùng, `a` (17 đến 18) được copy vào đầu xâu, xâu trở thành `acyppypastoopyppypa` và bị cắt thành `acyppypastoopyppyp`.

Do $K = 2$ nên ta sẽ in ra `ac`.

### Input 2
```
6 100
jjooii
3
5 6 2
4 6 1
1 2 3
```

### Output 2
```
joioji
```