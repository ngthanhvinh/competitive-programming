# aaqqz

IOI 2015 sẽ được tổ chức tại Kazahstan. "Kazakh" (người Kazahstan) được viết trong tiếng Kazahstan là "QAZAQ", một **palindrome**. Mr. JOI, sau khi nghe được thông tin thú vị này, cũng nổi hứng làm một palindrome chơi.

JOI tìm thấy một chuỗi $N$ kí tự. Ta sẽ mã hóa mỗi kí tự khác nhau thành một số trong khoảng từ $1$ đến $C$. Gọi $S = (S_1, S_2, ..., S_N)$ là chuỗi số thể hiện xâu. Ta gọi đoạn các số từ vị trí $i$ đến vị trí $j$ ($1 \le i \le j \le N$) là đoạn $(i, j)$. Nếu đoạn $(i, j)$ giống hệt như đoạn viết ngược lại của nó, tức $(S_i, S_{i + 1}, ..., S_j) = (S_j, S_{j - 1}, ..., S_i)$ thì ta gọi đoạn $(i, j)$ là **palindrome**.

Mr. JOI muốn tạo ra đoạn palindrome dài nhất bằng cách thực hiện các bước sau:

1. Chọn một đoạn $(i, j)$ của $S$, gọi nó là $T$,
2. Tạo đoạn $T'$ là các phần tử của $T$ được sắp xếp tăng dần.
3. Thay thế $T'$ vào $S$ theo đúng vị trí tương ứng của $T$ tạo ra $S' = (S_1, S_2, ..., S_{i - 1}, T'_1, T'_2, ..., T'_{j - i + 1}, S_{j + 1}, S_{j + 2}, ..., S_N)$.
4. Tìm đoạn palindrome dài nhất trong $S'$.

Sau 4 bước trên, Mr. JOI muốn có đoạn palindrome dài nhất có thể.

## Yêu cầu

Cho thông tin về xâu, tìm độ dài của đoạn palindrome dài nhất sau khi thực hiện 4 bước biến đổi đã cho một cách tối ưu.

## Dữ liệu nhập vào

- Dòng đầu tiên gồm 2 số $N$ và $C$, số kí tự trong xâu và giới hạn của các số.
- $N$ dòng tiếp theo, mỗi dòng gồm 1 số $S_i$, kí tự thứ $i$.

## Dữ liệu xuất ra

- In trên 1 dòng 1 số duy nhất là độ dài palindrome dài nhất có thể tạo được.

## Giới hạn

Trong tất cả các test:

- $1 \le N \le 3000$
- $1 \le C \le 3000$
- $1 \le S_i \le C$ ($1 \le i \le N$)


### Subtask 1 (10 điểm)

- $N \le 50$
- $C \le 50$

### Subtask 2 (90 điểm)

Không có giới hạn gì thêm.

## Ví dụ 

### Input

```
12 26
26
17
17
17
1
26
1
17
19
20
1
14
```

### Output

```
8
```

Ta xếp loại đoạn $(4, 8)$ để dãy trở thành $(26 , 17 , 17 , 1, 1 , 17 , 17 , 26 , 19 , 20, 1 , 14)$, có đoạn $(1, 8)$ là palindrome.

### Input

```
4 3
1
2
3
2
```

### Output

```
3
```