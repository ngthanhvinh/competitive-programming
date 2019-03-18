# constellation 2

IOI và JOI là đôi bạn thân. Một ngày nọ, 2 bạn rủ nhau đi ngắm vũ trụ qua đài thiên văn trên đỉnh núi.

Trên đài thiên văn, ta có thể quan sát $N$ ngôi sao. Ta đánh số các ngôi sao từ $1$ đến $N$. Mỗi ngôi sao có một trong 3 màu đỏ, xanh hoặc vàng.

Ta có thể biểu diễn các ngôi sao quan sát được là các điểm trên mặt phẳng. Ngôi sao thứ $i$ sẽ được biểu diễn  là điểm $P_i(X_i, Y_i)$. Các điểm $P_1, P_2, ..., P_N$ có tọa độ phân biệt, đồng thời không có 3 điểm nào thẳng hàng.

JOI và IOI quyết định tạo ra chòm sao **JOIOI**! Đầu tiên họ nghĩ ra việc nối 3 ngôi sao với 3 màu khác nhau thành một chòm sao tam giác. Hình tam giác này được gọi là **tốt**.

Hai người đã quyết định chọn ra hai chòm tam giác **tốt**  (theo bất kì thứ tự nào) thỏa mãn các điều kiện sau để làm chòm sao **JOIOI**:

- Hai hình tam giác phải không có điểm chung (cả trên cạnh lẫn bên trong tam giác). Điều này bao gồm cả giao nhau và lồng nhau.
![](./e.png)
Trong hình trên, phần bên trái thỏa mãn, 2 phần bên phải thì không.

JOI và IOI quyết định sẽ đếm xem có bao nhiêu cặp chòm tam giác thỏa mãn điều kiện trên. Lưu ý rằng, có thể sẽ có 2 cặp có cùng 6 điểm, tuy nhiên nếu cách tạo tam giác là khác nhau, chúng vẫn được coi là 2 cặp khác nhau.

## Yêu cầu

Cho biết hình dạng của các ngôi sao được biểu diễn trên mặt phẳng, xác định các cặp chòm sao tam giác thỏa mãn.

## Dữ liệu nhập vào

- Dòng đầu tiên gồm số $N$ - số lượng ngôi sao.
- $N$ dòng tiếp theo, dòng $i$ gồm 3 số $X_i, Y_i, C_i$ biểu diễn ngôi sao thứ $i$ nằm ở tọa độ $(X_i, Y_i)$ và có màu $C_i$.

## Dữ liệu xuất ra

- In trên 1 dòng 1 số duy nhất - số cặp chòm tam giác thỏa mãn.

## Giới hạn

Trong tất cả các test:

- $6 \le N \le 3000$
- $-10^5 \le X_i, Y_i \le 10^5$
- $0 \le C_i \le 2$
- Mỗi màu luôn có ít nhất 1 ngôi sao.
- Các ngôi sao đôi một khác nhau.
- Không có 3 ngôi sao nào thẳng hàng.

### Subtask 1 (15 điểm)

- $N \le 30$

### Subtask 2 (40 điểm)

- $N \le 300$

### Subtask 3 (45 điểm)

Không có giới hạn gì thêm.

## Ví dụ

### Input

```
7
0 0 0
2 0 1
1 2 2
-2 1 0
-2 -3 0
0 -2 1
2 -2 2
```

### Output

```
4
```

![](./1.png)

Có các cách chọn sau:

![](./2.png)

### Input

```
8
16 0 0
17 0 0
0 7 2
0 -7 2
-1 -1 1
-1 1 2
-6 4 1
-6 -4 1
```

### Output

```
12
```

### Input

```
21
1 20 0
4 20 0
0 22 0
5 22 0
6 25 0
8 25 0
4 26 0
11 11 1
7 12 1
14 13 1
8 15 1
15 16 1
11 17 1
18 0 2
13 2 2
16 2 2
19 4 2
18 6 2
21 8 2
24 8 2
19 10 2
```

### Output

```
7748
```