# 防壁 (Walls)

Bạn mới mua một trò chơi mới của hãng game JOI và chơi nó liên tục trong nhiều ngày liền.

Một ngày nọ, một màn chơi mới với tên gọi "lasers" xuất hiện. Giang hồ đồn đại rằng màn chơi này khó đến nỗi một người chơi lão luyện cũng chỉ có thể vượt qua màn nếu như họ vô cùng may mắn. Bạn, không quá tài năng, không quá may mắn, nhưng bạn nhận ra rằng nếu có thể tính toán cực nhanh có thể dễ dàng vượt qua màn chơi này. Bạn quyết định viết một chương trình thực hiện điều đó.

Không gian trong trò chơi là một lưới 2 chiều với các ô $1 \times 1$ có tọa độ $(x, y)$ là các số nguyên không âm. Ô $(0, 0)$ nằm ở góc dưới trái, ô $(x, y)$ nằm ở bên phải ô $(0, 0)$ $x$ đơn vị và nằm bên trên ô $(0, 0)$ $y$ đơn vị.

Bạn được cung cấp $N$ rào chắn, được đánh số từ $1$ đến $N$. Ban đầu, rào chắn thứ $i$ sẽ chiếm các ô từ $(L_i, i)$ đến $(R_i, i)$, chứa cả 2 đầu.

Bạn phải chống chọi $M$ đợt tấn công của địch. Đợt tấn công thứ $j$ là một tia laser bắn thẳng từ ô $(P_j, N + 1)$ đến ô $(P_j, 0)$. Các đợt tấn công sẽ lần lượt diễn ra.

Để ngăn cản tia laser, bạn cần di chuyển các rào chắn sao cho **cả $N$ rào chắn** đều giao với tia laser của địch.
Mỗi bước bạn có thể dịch một rào chắn sang trái hoặc sang phải một đơn vị.

Hãy tìm số bước nhỏ nhất để ngăn chặn $M$ đợt tấn công của địch.

## Yêu cầu

Cho cấu trúc màn chơi, hãy tìm chi phí nhỏ nhất để di chuyển các rào chắn sao cho ngăn chặn cả $M$ đợt tấn công của địch.

## Dữ liệu nhập vào

- Dòng đầu tiên gồm 2 số $N$ và $M$ - số rào chắn và số đợt tấn công.
- $N$ dòng tiếp theo, dòng thứ $i$ gồm 2 số $L_i$ và $R_i$ - tọa độ chiều ngang của rào chắn thứ $i$.
- $M$ dòng tiếp theo, dòng thứ $j$ gồm 1 số $P_j$ - tọa độ dọc của tia laser trong đợt tấn công thứ $j$.

## Dữ liệu xuất ra

- In ra $N$ dòng, dòng thứ $i$ in chi phí nhỏ nhất để di chuyển rào chắn thứ $i$ để chặn tất cả đợt tấn công.

## Giới hạn

Trong tất cả các test:

- $1 \le N \le 2 \times 10^5$
- $1 \le M \le 2 \times 10^5$
- $1 \le L_i \le R_i \le 10^9$ ($1 \le i \le N$)
- $1 \le P_j \le 10^9$ ($1 \le j \le M$)

### Subtask 1 (10 điểm)

- $N = 1$

### Subtask 2 (45 điểm)

- $L_i = 0$ với mọi $1 \le i \le N$

### Subtask 3 (45 điểm)

Không có giới hạn gì thêm.

## Ví dụ 

### Input

```
4 4
0 3
4 4
2 7
8 11
6
4
3
8
```

### Output

```
5
10
1
7
```

Ta di chuyển như hình sau:

![](./1.png)

### Input

```
7 11
12 39
22 23
5 38
6 47
10 43
0 50
18 46
38
19
15
1
12
29
29
0
6
40
6
```

### Output

```
34
178
13
6
18
0
36
```