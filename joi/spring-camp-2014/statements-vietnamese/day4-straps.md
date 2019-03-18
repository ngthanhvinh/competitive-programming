# straps

Mr. JOI có $N$ sợi dây trang trí điện thoại. Các sợi dây được đánh số từ $1$ đến $N$. JOI định buộc một số sợi vào điện thoại của mình.

Những sợi dây của JOI có chút kì lạ: chúng được thiết kế để có thể buộc nối một số hữu hạn sợi dây khác vào đuôi. Với mỗi sợi dây JOI có thể buộc chúng thẳng vào điện thoại hoặc vào đuôi của một sợi dây khác. Tuy nhiên, chỉ có tối đa một sợi dây được phép buộc vào điện thoại.

Ngoài ra, với mỗi dây, độ sung sướng khi buộc dây đó đã được định trước. Chỉ số này được biểu diễn bởi một số nguyên. Với một số dây JOI không thích, độ sung sướng đó có thể âm. 

JOI muốn tối đa tổng độ sung sướng khi buộc dây. Cậu không cần thiết phải buộc tất cả các đuôi dây, đồng thời cũng không cần phải buộc ít nhất một dây.

## Yêu cầu

Cho biết thông tin về các sợi dây, hãy tìm độ sung sướng lớn nhất đạt được khi đeo các sợi dây vào điện thoại của JOI một cách tối ưu.

## Dữ liệu nhập vào

- Dòng đầu tiên ghi số $N$ - số sợi dây.
- $N$ dòng tiếp theo, dòng thứ $i$ ghi 2 số $A_i$ và $B_i$ miêu tả sợi dây thứ $i$ có thể nối *trực tiếp* tối đa $A_i$ sợi khác vào đuôi, và có độ sung sướng $B_i$ khi nối.

## Dữ liệu xuất ra

- In trên 1 dòng 1 số duy nhất - độ sung sướng tối đa.

## Giới hạn

Trong tất cả các test:

- $1 \le N \le 2000$
- $0 \le A_i \le N$
- $-10^6 \le A_i \le 10^6$ ($1 \le i \le N$)

### Subtask 1 (5 điểm)

- $N \le 15$

### Subtask 2 (5 điểm)

- $B_i \ge 0$

### Subtask 3 (45 điểm)

- $A_i \le 15$

### Subtask 4 (45 điểm)

Không có ràng buộc gì thêm.

## Ví dụ

### Input

```
5
0 4
2 -2
1 -1
0 1
0 3
```

### Output

```
5
```

Ta buộc 2 vào điện thoại, 1 và 5 vào 2.

### Input

```
6
2 -3
3 -1
0 -4
0 -2
1 -3
4 -1
```

### Output

```
0
```

Tốt nhất không buộc gì cả.

### Input

```
15
1 -4034
1 3406
0 6062
4 -6824
0 9798
0 4500
0 -1915
1 2137
0 9786
0 7330
0 -9365
2 2730
0 -5797
0 6129
0 8925
```

### Output

```
43417
```