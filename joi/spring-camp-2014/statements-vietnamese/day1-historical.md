# Historical Research

Một tập tài liệu cổ đại, được viết bởi những cư dân của vương quốc cổ đại IOI vừa đến tay Giáo sư Joy, một chuyên gia về vương quốc IOI. Giáo sư quyết định khảo sát các sự kiện được thuật lại trong tập tài liệu để tìm hiểu thêm về cuộc sống trong vương quốc.

Trong tài liệu có $N$ sự kiện, mỗi sự kiện lần lượt diễn ra trong 1 ngày. Mỗi sự kiện được đại diện bởi một số $X_i$. Người ta cho rằng $X_i$ càng lớn thì quy mô của sự kiện càng lớn.

Giáo sư Joy quyết định khảo sát các sự kiện theo phương pháp sau:

1. Chọn ra một khoảng liên tiếp các sự kiện.
2. Với mỗi sự kiện loại $t$, ta tính **độ quan trọng** của sự kiện là $t \times K_t$ với $K_t$ là số lần xuất hiện của sự kiện $t$ trong khoảng đã chọn.
3. Tìm độ quan trọng lớn nhất trong tất cả các loại sự kiện.

Bạn được giáo sư giao cho công việc tính toán bước 2 và 3. Hãy viết chương trình thực hiện điều này với mỗi khoảng được yêu cầu.

## Yêu cầu

Cho thông tin về $N$ sự kiện, và $Q$ khoảng liên tiếp cần tính toán, hãy tìm **độ quan trọng** lớn nhất của mỗi khoảng.

## Dữ liệu nhập vào

- Dòng đầu tiên gồm 2 số $N$ và $Q$ - số sự kiện và số khoảng liên tiếp cần tính toán.
- Dòng tiếp theo ghi $N$ số $X_1, X_2, ..., X_N$ - loại của từng sự kiện.
- $Q$ dòng tiếp theo, mỗi dòng ghi 2 số $A_i$ và $B_i$, bạn cần tính toán trong khoảng sự kiện từ $A_i$ đến $B_i$.

## Kết quả xuất ra

- In ra $Q$ dòng, mỗi dòng in 1 số duy nhất là độ quan trọng tính được trong khoảng tương ứng.

## Giới hạn

Trong tất cả các test:

- $1 \le N, Q \le 10^5$
- $1 \le X \le 10^9$

### Subtask 1 (5 điểm)

- $N, Q \le 100$

### Subtask 2 (10 điểm)

- $N, Q \le 5000$

### Subtask 3 (25 điểm)

- Không tồn tại $i \neq j$ thỏa mãn $A_i \le A_j \le B_j \le B_i$

### Subtask 4 (60 điểm)

Không có giới hạn gì thêm.

## Ví dụ

### Input
```
5 5
9 8 7 8 9
1 2
3 4
4 4
1 4
2 4
```

### Output
```
9
8
8
16
16
```

### Input
```
8 4
9 9 19 9 9 15 9 19
1 4
4 6
3 5
5 8
```

### Output
```
27
18
19
19
```

### Input
```
12 15
15 9 3 15 9 3 3 8 16 9 3 17
2 7
2 5
2 2
1 12
4 12
3 6
11 12
1 7
2 6
3 5
3 10
7 10
1 4
4 8
4 8
```

### Output
```
18
18
9
30
18
15
17
30
18
15
18
16
30
15
15
```