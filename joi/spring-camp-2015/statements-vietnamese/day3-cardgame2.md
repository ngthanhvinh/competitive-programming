# とてもたのしいカードゲーム (Card Game Is Great Fun)

Anna rất hay chơi bài với Bruno. Dù vậy, chơi nhiều cũng chán, hôm nay cô quyết định nghĩ ra 1 trò chơi với bài để chơi một mình.

Trước khi bắt đầu, các lá bài có nhiều màu được xếp thành một xấp gồm $N$ lá. Lá thứ $i$ kể từ đầu xấp sẽ có màu $C_i$, số $A_i$ và có giá trị $V_i$.

Ban đầu, trên tay của Anna không có lá bài nào. Cô sẽ lần lượt bốc các lá bài từ xấp bài và cho lên đầu tay bài của mình theo quy tắc sau:

- Mỗi lượt cô được lấy lá bài ở **đầu** hoặc **thứ ba** kể từ đầu xấp bài hiện tại.
- Nếu trên tay Anna có ít nhất một lá bài, thì lá bài tiếp theo cô bốc phải có màu hoặc số giống như lá bài cô bốc cuối cùng.
- Trò chơi kết thúc khi cô không thể bốc thêm lá bài nào. Điểm của cô được tính bằng tổng giá trị các lá bài đã bốc lên tay.

Hiển nhiên Anna muốn tối đa hóa số điểm nhận được.

## Yêu cầu

Cho thông tin về xấp bài, tìm số điểm lớn nhất Anna có thể đạt được.

## Dữ liệu nhập vào

- Dòng đầu tiên gồm số $N$, số lá bài trong xấp bài.
- $N$ dòng tiếp theo, dòng thứ $i$ gồm 3 số $C_i, A_i, V_i$ - màu, số và giá trị của lá bài thứ $i$.

## Dữ liệu xuất ra

- In trên 1 dòng 1 số duy nhất là số điểm lớn nhất Anna có thể đạt được.

## Giới hạn

Trong tất cả các test:

- $1 \le N \le 500$
- $1 \le C_i \le 500$ ($1 \le i \le N$)
- $1 \le A_i \le 500$ ($1 \le i \le N$)
- $1 \le V_i \le 10^6$ ($1 \le i \le N$)

### Subtask 1 (10 điểm)

- $N \le 20$

### Subtask 2 (15 điểm)

- $N \le 50$

### Subtask 3 (75 điểm)

Không có giới hạn gì thêm.

## Ví dụ 

### Input

```
5
1 3 2
4 2 9
1 4 6
2 3 3
2 2 1
```

### Output

```
15
```

Thứ tự bốc bài là: (1, 3, 2), (2, 3, 3), (2, 2, 1), (4, 2, 9).

### Input

```
8
11 5 31
2 8 19
2 9 2
11 8 45
4 8 22
4 2 23
6 9 58
6 2 5
```

### Output

```
160
```