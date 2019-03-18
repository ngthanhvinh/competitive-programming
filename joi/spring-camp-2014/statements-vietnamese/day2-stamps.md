# Collecting Stamps

Đường ray IOI là một đoạn thẳng có $N + 2$ trạm.
Các trạm đánh số từ $0$ đến $N + 1$ theo đúng thứ tự xuất hiện trên đường ray.

Có hai loại tàu chạy trên đường ray IOI: tàu lên dốc và tàu xuống dốc. Khi đi tàu lên dốc thì bạn đi từ trạm có chỉ số thấp hơn lên chỉ số cao hơn và ngược lại. 
Để di chuyển giữa 2 trạm liên tiếp bạn phải mất thời gian $T$ cho cả chiều lên lẫn xuống.
Ngoài ra bạn không được đi tàu lên dốc ở trạm $N + 1$ hay đi tàu xuống dốc ở trạm $0$. Có rất nhiều tàu qua lại, nên ta có thể coi thời gian chờ tàu là không đáng kể.

Mỗi trạm có 2 nhà chờ - một cho tàu lên dốc và một cho tàu xuống dốc. Một cột tem được đặt ở hành lang nối giữa 2 nhà chờ ở mỗi trạm.

Nhiệm vụ của bạn là xuất phát từ trạm $0$, mua tem từ tất cả các trạm từ $1$ đến $N$ và kết thúc ở trạm $N + 1$ trong thời gian ngắn nhất.

Để có thể mua tem ở một trạm, bạn phải đi bộ từ nhà chờ đến cột tem, mua tem, rồi quay lại. Thời gian cụ thể để đi ở trạm $i$ như sau:

- Nhà chờ tàu lên dốc đến cột tem: $U_i$ giây
- Cột tem đến nhà chờ tàu lên dốc: $V_i$ giây
- Nhà chờ tàu xuống dốc đến cột tem: $D_i$ giây
- Cột tem đến nhà chờ tàu xuống dốc: $E_i$ giây

Bạn chỉ được phép đi qua trạm $0$ và $N + 1$ đúng một lần. Với các trạm còn lại, có thể qua lại nhiều lần.

## Yêu cầu

Cho các thông tin về đường ray và trạm tàu, tính thời gian ngắn nhất để hoàn thành nhiệm vụ. 

Thời gian thực hiện nhiệm vụ được tính bằng tổng thời gian di chuyển từ khi xuất phát từ trạm $0$ đến khi kết thúc ở trạm $N + 1$. Bạn có thể bỏ qua thời gian chờ tàu và thời gian mua tem.

## Dữ liệu nhập vào

- Dòng đầu tiên gồm 2 số $N$ và $T$ - tức có $N + 2$ trạm tàu và thời gian di chuyển giữa 2 trạm liên tiếp là $T$.
- N dòng tiếp theo, mỗi dòng gồm 4 số $U_i, V_i, D_i, E_i$ miêu tả trạm tàu thứ $i$ ($1 \le i \le N$), với thời gian di chuyển được giải thích như trên.

## Kết quả xuất ra

- In ra 1 dòng duy nhất ghi 1 số là thời gian ngắn nhất để hoàn thành nhiệm vụ.

## Giới hạn

Trong tất cả các test:

- $1 \le N \le 3000$
- $1 \le T \le 10^5$
- $1 \le U_i, V_i, D_i, E_i \le 10^5$ ($1 \le i \le N$)

### Subtask 1 (10 điểm)

- $N \le 16$

### Subtask 2 (75 điểm)

- $N \le 100$

### Subtask 3 (15 điểm)

Không có giới hạn gì thêm.

## Ví dụ

### Input

```
4 1
1 1 1 1
1 9 9 1
9 9 1 1
1 9 9 1
```

### Output

```
23
```

Đi theo thứ tự 0 > 2 (tem) > 1 (tem) > 4 (tem) > 3 (tem) > 1 > 5.

### Input

```
6 2
5 5 3 5
9 7 9 3
3 4 9 4
8 2 6 6
8 5 7 5
3 2 1 6
```

### Output

```
73
```
