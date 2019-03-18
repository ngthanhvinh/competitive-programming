# voltage

Bạn có biết đến Công ty **Just Odd Inventions** không? Đây là một công ty chuyên làm ra các *just odd inventions*... Ở đây ta sẽ gọi công ty là JOI cho ngắn gọn.

Một phòng thí nghiệm của JOI có một hệ thống mạng điện phức tạp. Mạng điện gồm $N$ điện thế và $M$ dây điện trở. Mỗi điện thế có 2 trạng thái "điện thế cao" và "điện thế thấp". Mỗi dây điện trở nối 2 điện thế, và có dòng điện chạy qua khi và chỉ khi có 1 điện thế cao và 1 điện thế thấp. Lưu ý rằng ta có thể đổi trạng thái của bất cứ điện thế nào.

Để thực hiện bảo trì mạch điện, bạn phải thử ngắt từng dây điện một. Khi ngắt một dây điện, bạn phải đảm bảo dây điện đó không có dòng điện chạy qua, đồng thời $M-1$ dây điện còn lại **phải** có dòng điện chạy qua. Có bao nhiêu dây điện có thể được bảo trì?

*Việc công ty JOI xây dựng mạch điện này cho mục đích gì là thông tin tối mật, chỉ có ngài Chủ tịch được biết.*

## Yêu cầu

Cho thông tin về hệ thống mạch điện, xác định số lượng các dây điện có thể thực hiện bảo trì.

## Dữ liệu nhập vào

- Dòng đầu tiên gồm 2 số $N$ và $M$ - số điện thế và dây điện trở.
- $M$ dòng tiếp theo, dòng $i$ gồm 2 số $u_i$ và $v_i$ - miêu tả dây điện thứ $i$ nối điện thế $u_i$ và điện thế $v_i$. ($1 \le u_i, v_i \le N$, $u_i \neq v_i$, $1 \le i \le M$)

## Dữ liệu xuất ra

- In ra 1 dòng 1 số duy nhất - số lượng dây điện thỏa mãn.

## Giới hạn

Trong tất cả các test:

- $2 \le N \le 10^5$
- $1 \le M \le 2 \times 10^5$

### Subtask 1 (10 điểm)

- $N \le 1000$
- $M \le 2000$

### Subtask 2 (10 điểm)

- Luôn có đường nối bằng dây điện giữa 2 điện thế bất kì.
- $M = N$

### Subtask 3 (35 điểm)

- Luôn có đường nối bằng dây điện giữa 2 điện thế bất kì.
- $M \le N + 100$

### Subtask 4 (45 điểm)

Không có ràng buộc gì thêm.

## Ví dụ

### Input

```
4 5
1 2
1 3
1 4
2 4
3 4
```
### Output

```
1
```

![](./1.png)

Theo hình vẽ, hiển nhiên chỉ có dây điện `1-4` có thể được bảo trì.

### Input

```
4 4
1 2
2 3
3 2
4 3
```

### Output

```
2
```

Ta có thể bảo trì `1-2` và `3-4` như sau:

![](./2.png)

### Input

```
13 16
1 6
2 6
3 1
3 2
4 7
4 7
5 9
6 5
8 2
8 13
9 11
10 3
11 10
11 12
12 8
13 6
```

### Output

```
3
```