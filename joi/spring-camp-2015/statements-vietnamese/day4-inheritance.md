# 遺産相続 (Inheritance)

Mr.JOI, người sở hữu tất cả đường ray trong đất nước IOI vừa mất. Đường ray ông để lại được chia theo di chúc của ông.

Đất nước IOI có $N$ thành phố và $M$ đường ray. Các thành phố được đánh số từ $1$ đến $N$, các đường ray được đánh số từ $1$ đến $M$. Đường ray thứ $i$ nối giữa 2 thành phố $A_i$ và $B_i$, và đem lại lợi nhuận $C_i$ yen mỗi năm. Lưu ý rằng giữa 2 thành phố có thể có nhiều đường ray.

Mr.JOI có $K$ người con, đánh số từ $1$ đến $K$ theo độ lớn. Theo di chúc, những đứa con sẽ được lựa chọn sở hữu đường ray cha để lại theo quy tắc sau:

- Các người con từ $1$ đến $K$ sẽ lần lượt tự chọn cho mình một tập các đường ray trong $M$ đường ray để sở hữu cho mình. Người con $1$ chọn đầu tiên, rồi $2$, ... cuối cùng là $K$.
- Một người con không thể chọn đường ray mà đã được chọn trước đó bởi một người con khác.
- Tập đường ray của mỗi người con không được phép tạo ra một chu trình nào.
- Những đường ray không có ai chọn sẽ được chuyển cho nhà nước.

Tất cả người con đều tham lam như bố mình, vì vậy ai cũng chọn cho mình tập đường ray có tổng lợi nhuận là lớn nhất.
Hãy xác định xem ai đã chọn đường ray nào.

## Yêu cầu

Cho thông tin về các đường ray, hãy tìm chủ sở hữu của từng đường ray sau khi chia.

## Dữ liệu nhập vào

- Dòng đầu tiên gồm 3 số $N$, $M$, $K$ - số thành phố trong đất nước IOI, số đường ray và số người con.
- $M$ dòng tiếp theo, dòng thứ $i$ gồm 3 số $A_i, B_i, C_i$ - đường ray thứ $i$ nối thành phố $A_i$ và $B_i$ với lợi nhuận $C_i$.

## Dữ liệu xuất ra

- In ra $M$ dòng, trong đó dòng thứ $i$ gồm 1 số duy nhất - chỉ số của người con đã chọn đường ray thứ $i$. Nếu đường ray được chuyển cho nhà nước, in `0`.

## Giới hạn

Trong tất cả các test:

- $2 \le N \le 1000$
- $1 \le M \le 3 \times 10^5$
- $1 \le K \le 10^4$
- $1 \le A_i, B_i \le N$ ($1 \le i \le M$)
- $A_i \neq B_i$ ($1 \le i \le M$)
- $1 \le C_i \le 10^9$ ($1 \le i \le M$)
- $C_i \neq C_j$ ($1 \le i < j \le M$)

### Subtask 1 (15 điểm)

- $K \le 10$

### Subtask 2 (85 điểm)

Không có giới hạn gì thêm.

## Ví dụ 

### Input

```
3 5 2
1 2 3
1 2 1
2 3 4
2 3 6
1 3 2
```

### Output

```
1
0
2
1
2
```

### Input

```
3 6 5
1 2 1
1 2 2
2 3 3
2 3 4
3 1 5
3 1 6
```

### Output

```
4
3
2
1
2
1
```