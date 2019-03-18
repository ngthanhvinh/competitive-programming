# Ramen

JOI và IOI đều rất thích [Ramen](http://lmgtfy.com/?q=ramen). Tuy vậy, JOI thì thích Ramen nhiều bánh, IOI thì thích Ramen nhiều nước. (Tất nhiên, nhiều nước thì ít bánh và ngược lại).
Ở thị trấn mà JOI và IOI sống có $N$ quán Ramen, được đánh số từ $0$ đến $N - 1$.

Không thể tìm được quán nào hợp khẩu vị cả 2, nên JOI và IOI quyết định tìm một quán bán Ramen nhiều nước nhất và quán bán Ramen nhiều bánh nhất trong các quán ở thị trấn.

Độ "nhiều nước" của Ramen trong các quán có thể biểu diễn được thành một hoán vị từ $0$ đến $N-1$. Mỗi ngày JOI và IOI sẽ đến 2 quán để ăn so sánh, và đưa ra kết luận hàng nào có Ramen nhiều nước hơn. 

Do kinh phí có hạn, nên JOI và IOI chỉ có thể đi so sánh được tối đa **600** ngày.

## Yêu cầu
Cho biết số quán Ramen $N$, bằng không quá 600 lần so sánh 2 quán Ramen, tìm ra quán Ramen nhiều nước nhất và quán Ramen nhiều bánh nhất.

## Thư viện

Code của bạn cần thêm vào thư viện sau:

```
#include "grader.h"
```

Bạn được cung cấp các hàm:

- `int Compare(int X, int Y)`: So sánh 2 hàng Ramen $X$ và $Y$ ($0 \le X, Y < N$, $X \neq Y$). Hàm trả về `1` nếu hàng $Y$ có Ramen nhiều nước hơn và `-1` nếu ngược lại. Bạn được gọi hàm này không quá **600** lần.
- `void Answer(int X, int Y)`: Đưa ra câu trả lời `X` là quán nhiều nước nhất, `Y` là quán nhiều bánh nhất ($0 \le X, Y < N$). Bạn chỉ được gọi hàm này đúng một lần. Sau khi gọi hàm, chương trình sẽ thoát.

Bạn phải cài đặt hàm:

- `void Ramen(int N)`: Đây là hàm chạy thuật toán hỏi của bạn, được cung cấp số $N$ - số quán Ramen. Từ hàm này bạn có thể gọi 2 hàm thư viện. Hàm sẽ được gọi đúng 1 lần trong chương trình.

### Grader mẫu

Grader mẫu sẽ đọc theo khuôn dạng:

- Dòng đầu tiên gồm 1 số $N$ - số quán Ramen.
- Dòng tiếp theo gồm $N$ số $A_0, A_1, ..., A_{N - 1}$, độ "nhiều nước" của từng quán Ramen. Đây phải là một hoán vị từ $0$ đến $N - 1$.

Và trả về:

- 1 dòng duy nhất ghi 2 số $X$ - quán Ramen nhiều nước nhất, và $Y$ - quán Ramen nhiều bánh nhất.

Nếu có bất cứ lỗi nào sinh ra khi chạy, grader mẫu sẽ trả về exit code khác 0. Khi đó khuôn dạng trả về có thể khác miêu tả.

#### Biên dịch grader mẫu
```
g++ -O2 grader.cpp ramen.cpp -o grader
```

Hoặc chạy file `compile.sh`.

## Giới hạn

Trong tất cả các test:

- $1 \le N \le 400$

### Subtask 1 (20 điểm)

- $N \le 30$

### Subtask 2 (30 điểm)

- $N \le 300$

### Subtask 3 (50 điểm)

Không có giới hạn gì thêm.

## Ví dụ

### Input của Grader mẫu
```
3
1
2
0
```

### Output của Grader mẫu
```
1 2
```