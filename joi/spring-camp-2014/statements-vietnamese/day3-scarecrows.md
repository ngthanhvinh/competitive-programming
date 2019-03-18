# scarecrows

Ở vùng đất cằn cỗi của làng JOI có $N$ con bù nhìn. Người dân của vùng vẫn hay tổ chức các lễ hội xung quanh bọn bù nhìn. Một ngày nọ, trưởng làng nghe thấy rằng các thần bù nhìn sẽ ban cho dân làng một mảnh đất khả năng trồng trọt. Theo như yêu cầu, mảnh đất phải thỏa mãn:

- Là một hình chữ nhật dọc theo chiều đông-tây và nam-bắc.
- Phải có một bù nhìn ở góc tây-nam, và một bù nhìn ở góc đông-bắc.
- Không được có bù nhìn nào nằm bên trong khu đất (có thể nằm trên biên).

Tất nhiên, không được di chuyển các bù nhìn. Có bao nhiêu mảnh đất thỏa mãn các điều kiện?

## Yêu cầu

Cho biết các vị trí của bù nhìn, đếm số mảnh đất thỏa mãn yêu cầu.

## Dữ liệu nhập vào

- Dòng đầu tiên gồm 1 số $N$, số bù nhìn.
- $N$ dòng tiếp theo, mỗi dòng gồm 2 số $X_i$ và $Y_i$ - tọa độ của bù nhìn thứ $i$. Tọa độ $X$ chạy theo hướng nam-bắc, tọa độ $Y$ chạy theo hướng tây-đông.

## Dữ liệu xuất ra

- In trên 1 dòng 1 số duy nhất - số mảnh đất thỏa mãn.

## Giới hạn

Trong tất cả các test:

- $1 \le N \le 2 \times 10^5$
- $0 \le X_i, Y_i \le 10^9$ ($1 \le i \le N$)
- Các tọa độ $X_i$ đôi một khác nhau.
- Các tọa độ $Y_i$ đôi một khác nhau.

### Subtask 1 (5 điểm)

- $N \le 400$

### Subtask 2 (10 điểm)

- $N \le 5000$

### Subtask 3 (85 điểm)

Không có giới hạn gì thêm.

## Ví dụ

### Input

```
4
0 0
2 2
3 4
4 3
```

### Output

```
3
```

![](./image1.png)

### Input

```
10
2 1
3 0
6 3
10 2
16 4
0 8
8 12
11 14
14 11
18 10
```

### Output

```
15
```

![](./image2.png)