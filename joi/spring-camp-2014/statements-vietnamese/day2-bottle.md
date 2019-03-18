# Water Bottle

Thành phố IOI, nơi JOI sinh sống, được biết đến với cơn nóng đặc biệt mỗi năm.

Thành phố IOI có thể được coi là một hình chữ nhật, được chia thành $H \times W$ phần. Mỗi phần có thể là một tòa nhà, một khu trống hoặc một bức tường. Có tất cả $P$ ô tòa nhà, đánh số từ 1 đến $P$.

JOI chỉ có thể đi vào các khu tòa nhà và các khu trống. Ngoài ra, JOI chỉ có thể di chuyển qua các khu kề cạnh với khu đang đứng, và không được di chuyển ra ngoài thành phố. 

JOI cần phải đi lại qua một số tòa nhà để thực hiện công việc của mình. Các tòa nhà đã có điều hòa đầy đủ, tuy nhiên các khu trống thì nắng nóng gay gắt, nên để đi qua chúng sẽ cần một lần uống nước.
Ngoài ra, do không có máy bán hàng hay điểm bán nước nào trong thành phố, nên JOI hay mang theo một chai nước khi đi. 
Một chai nước cỡ $x$ có thể uống $x$ lần.
Khi đi vào một toà nhà, JOI có thể lấy lại cho đầy chai nước.

Mang chai nước lớn rất tốn công, nên JOI muốn mang đi chai nước gọn nhất có thể. 
Hãy viết một chương trình, hỏi JOI về cặp tòa nhà cậu muốn đi, và trả về kích cỡ chai nước nhỏ nhất cậu có thể mang đi.

## Yêu cầu

Cho biết hình dạng thành phố, với mỗi cặp tòa nhà được yêu cầu, tìm kích cỡ chai nước bé nhất có thể mang đi để đi lại được giữa cặp toà nhà.

## Dữ liệu nhập vào

- Dòng đầu tiên gồm 4 số $H, W, P, Q$ - kích cỡ thành phố, số toà nhà và số yêu cầu.
- $H$ dòng tiếp theo, mỗi dòng gồm $W$ kí tự `.` hoặc `#` thể hiện từng ô của thành phố. Kí tự `#` thể hiện một bức tường (JOI không thể đi vào), `.` thể hiện một ô trống hoặc một tòa nhà. 
- $P$ dòng tiếp theo, mỗi dòng gồm 2 số $A_i, B_i$, thể hiện tọa độ của toà nhà thứ $i$. Không có hai toà nhà nào trùng nhau.
- $Q$ dòng tiếp theo, mỗi dòng gồm 2 số $S_j, T_j$ thể hiện cặp toà nhà được yêu cầu thứ $j$.

## Kết quả xuất ra

- In ra $Q$ dòng, dòng $j$ in ra 1 số là đáp số của yêu cầu thứ $j$. Nếu JOI không thể đi lại giữa 2 tòa nhà in `-1`. Nếu không cần mang chai nước, in `0`.

## Giới hạn

Trong tất cả các test:

- $1 \le H \le 2 000$
- $1 \le W \le 2 000$
- $2 \le P \le 2 \times 10^5$
- $1 \le Q \le 2 \times 10^5$
- $1 \le Aj \le H$ $(1 \le j \le P)$
- $1 \le Bj \le W$ $(1 \le j \le P)$
- $1 \le S i < Ti \le P$ $(1 \le i \le Q)$

### Subtask 1 (10 điểm)

- $H, W, P \le 200$

### Subtask 2 (30 điểm)

- $P \le 5000$
- $Q = 1$

### Subtask 3 (30 điểm)

- $P \le 5000$
- $Q \le 10000$

### Subtask 4 (30 điểm)

Không có giới hạn gì thêm.

## Ví dụ

### Input
```
5 5 4 4
.....
..##.
.#...
..#..
.....
1 1
4 2
3 3
2 5
1 2
2 4
1 3
3 4
```

### Output
```
3
4
4
2
```

Bản đồ của thành phố IOI được thể hiện trong hình dưới. Các ô màu đen thể hiện tường, ô có số là các tòa nhà có số tương ứng, ô trống thể hiện khu trống.

![](./exp1a.png)

Xét việc di chuyển từ tòa nhà 2 sang toà nhà 4.

![](./exp1b.png)

Nếu không di chuyển qua toà nhà nào khác, JOI sẽ mất 6 lần uống nước để đi từ 2 đến 4. 

Tuy nhiên, như hình bên phải, nếu JOI đi qua tòa nhà 1 trên đường đi thì chỉ phải mang chai nước kích cỡ 4. Đây cũng là đáp án tối ưu.

### Input
```
5 5 3 2
...#.
..#..
#....
.##..
...#.
1 3
5 2
1 5
1 2
1 3
```

### Output
```
-1
7
```

