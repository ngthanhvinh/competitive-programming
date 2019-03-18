# joioji

Mr. JOIOJI là chú của JOI. Chú rất thích tên của mình vì chúng có các kí tự `J`, `O`, `I` mỗi loại xuất hiện đúng 2 lần. 

Gần đây chú JOIOJI mới sinh con. Chú định đặt tên cho con của mình cũng với 3 kí tự `J`, `O`, `I`, các kí tự xuất hiện với số lần như nhau.

Chú JOIOJI có một cuốn mật thư được truyền lại qua nhiều thế hệ. Trong cuốn mật thư là một bài thơ. Bài thơ là một chuỗi $N$ kí tự `J`, `O` hoặc `I`. Chú muốn đặt tên cho con của mình là chuỗi liên tiếp dài nhất trong bài thơ mà có cùng số kí tự `J`, `O` và `I`.

## Yêu cầu

Cho nội dung bài thơ trên cuốn mật thư của chú JOIOJI, hãy tìm độ dài chuỗi liên tiếp dài nhất có cùng số kí tự `J`, `O` và `I`.

## Dữ liệu nhập vào

- Dòng đầu tiên ghi số $N$, số kí tự của bài thơ.
- Dòng tiếp theo ghi $N$ kí tự `J`, `O` hoặc `I`, nội dung của bài thơ.

## Dữ liệu xuất ra

- In ra một dòng duy nhất là độ dài của chuỗi liên tiếp dài nhất thỏa mãn.

## Giới hạn

Trong tất cả các test:

- $1 \le N \le 2 \times 10^5$

### Subtask 1 (5 điểm)

- $N \le 200$

### Subtask 2 (15 điểm)

- $N \le 4000$

### Subtask 3 (80 điểm)

Không có giới hạn gì thêm.

## Ví dụ

### Input
```
10
JOIIJOJOOI
```

### Output
```
6
```

Ta chọn đoạn `IIJOJO`.

### Input
```
8
IOIIJIIO
```

### Output
```
0
```

### Input
```
20
JJIOOIJIJOIOJIOJOOIJ
```

### Output
```
15
```