# Bus

Mr. JOI, một sinh viên đại học, hàng ngày đến trường bằng xe buýt. Nhà của JOI và trường đại học đều nằm trong thành phố IOI.
Thành phố IOI có $N$ bến xe buýt, đánh số từ $1$ đến $N$. 
Bến gần nhà JOI đánh số 1, bến gần trường đại học đánh số $N$.

Trong thành phố IOI có $M$ chuyến xe buýt, mỗi xe đều có thời gian và địa điểm xuất phát và đến đích cố định. Không xe nào dừng giữa chừng, JOI cũng không thể lên hay xuống xe giữa chừng.

Mỗi sáng, JOI đến trường bằng một hoặc nhiều chuyến xe buýt. Ta có thể giả sử rằng việc đổi chuyến không tốn thời gian. Nói cách khác, JOI có thể đi một chuyến xe buýt nếu cậu có mặt ở bến xuất phát không muộn hơn thời điểm khởi hành. Ngoài ra, mỗi bến xe có thể được đến nhiều lần.

Với các điều kiện trên, JOI muốn biết thời gian muộn nhất mình có thể khởi hành là bao nhiêu mà vẫn có thể kịp vào lớp. Ở đại học, mỗi ngày lại có một lịch học khác nhau. Trong $Q$ ngày, bạn được biết thời gian vào lớp của ngày đó, hãy tính xem JOI có thể xuất phát muộn nhất vào lúc nào?

## Yêu cầu 

Cho thông tin về các chuyến xe buýt, với mỗi ngày biết thời gian JOI phải có mặt ở bến $N$, tính thời gian muộn nhất JOI phải có mặt ở bến $1$.

## Dữ liệu nhập vào

- Dòng đầu tiên ghi 2 số $N$ và $M$ - số bến xe và số chuyến xe buýt.
- $M$ dòng tiếp theo mỗi dòng gồm 4 số $A_i, B_i, X_i, Y_i$ ($1 \le A_i, B_i \le N$, $A_i \neq B_i$, $1 \le i \le M$) thể hiện một chuyến xe buýt xuất phát ở $A_i$ tại $X_i$, đến $B_i$ tại $Y_i$. Thời gian được tính bằng số mili-giây tính từ nửa đêm.
- Dòng tiếp theo ghi 1 số $Q$ - số ngày cần tính.
- $Q$ dòng tiếp theo mỗi dòng ghi 1 số $L_j$ ($1 \le j \le Q$), thời điểm bắt đầu học của ngày $j$.

## Kết quả xuất ra 

- In ra $Q$ dòng, với dòng thứ $j$ ghi thời gian muộn nhất JOI có thể xuất phát. Nếu JOI không thể đến đúng giờ, in `-1`.

## Giới hạn

Trong tất cả các test:

- $2 \le N \le 10^5$
- $1 \le M \le 3 \times 10^5$
- $0 \le X_i < Y_i < 86400000$
- $1 \le Q \le 10^5$
- $0 \le L_j < 86400000$

### Subtask 1 (20 điểm)

- $N, M \le 2000$
- $Q = 1$

### Subtask 2 (15 điểm)

- $N, M \le 2000$

### Subtask 3 (15 điểm)

- $Q = 1$

### Subtask 4 (50 điểm)

Không có giới hạn gì thêm.

## Ví dụ

### Input
```
5 6
1 2 10 25
1 2 12 30
2 5 26 50
1 5 5 20
1 4 30 40
4 5 50 70
4
10
30
60
100
```

### Output
```
-1
5
10
30
```

Truy vấn 2: Đi chuyến 4.

Truy vấn 3: Đi chuyến 1, 3.

Truy vấn 4: Đi chuyến 5, 6.

### Input
```
3 8
1 2 1 5
1 3 0 1
1 3 2 8
2 3 2 3
2 3 3 4
2 3 4 5
2 3 5 6
2 3 6 7
6
3
4
5
6
7
8
```

### Output
```
0
0
0
1
1
2
```