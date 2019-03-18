# 記憶縛り (Limited Memory)

JOI, được bầu làm đại diện của Nhật Bản cho kì thi IOI, được chủ tịch K của Hội đồng Khoa học Quốc tế giao cho một bài toán về xử lí thông tin.

Chủ tịch K viết ra một tờ giấy (và không cho JOI biết) một xâu $S$. Xâu $S$ gồm các kí tự `<`, `>`, `[`, `]`. K đưa cho JOI một tờ giấy khác, gồm nội dung của bài toán và độ dài của xâu $S$.

Bài toán đưa ra cho JOI là kiểm tra xem $S$ có phải một xâu **đúng** không. Một xâu được coi là **đúng** khi:

- Nó là một xâu rỗng (độ dài 0).
- Nếu `x` là một xâu đúng, thì `<x>` là một xâu đúng.
- Nếu `x` là một xâu đúng, thì `[x]` là một xâu đúng.
- Nếu `x` và `y` là hai xâu đúng, thì `xy` (`x` viết liền phía trước `y`) là một xâu đúng.
- Tất cả các xâu còn lại không phải là xâu đúng.

Ví dụ, `<>[]` và `[<>]<>` là các xâu đúng, trong khi `><` hay `[<]>` thì không phải.

Mỗi ngày JOI được phép gọi điện cho chủ tịch K tối đa một lần vào buổi trưa. Trong cuộc gọi, JOI có thể hỏi một số $I$, và chủ tịch K sẽ cho JOI biết kí tự thứ $I$ của xâu $S$.

JOI tự đặt ra cho mình một yêu cầu khắt khe: "Mình sẽ không nháp để giải bài toán này". Hàng ngày cậu đi ngủ vào 22 giờ tối và dậy vào 6 giờ sáng ngày hôm sau, tuy nhiên cậu chỉ còn nhớ lại được 22 bit thông tin của ngày hôm trước. Cụ thể, cậu có thể chọn một số bất kì trong khoảng $[0..2^{22})$ để ghi nhớ vào tối hôm trước, và chỉ tiếp tục giải bài toán với số đó là thông tin duy nhất vào ngày hôm sau. Tuy vậy, do độ dài xâu $S$ được viết trên tờ giấy trước đó, nên cậu luôn có thông tin này.

Thay vì học thuộc một số trước khi ngủ, JOI có thể trả lời đáp số của mình cho chủ tịch K qua email. Khi đưa ra câu trả lời, chương trình kết thúc và chủ tịch sẽ kết luận đáp số câu trả lời của cậu. 
Tuy nhiên, nếu sau **15000** ngày mà JOI chưa đưa ra câu trả lời, cậu sẽ bị coi là trả lời sai.

## Yêu cầu

Xây dựng chiến thuật cho JOI và viết chương trình tìm ra câu trả lời đúng.

## Chi tiết cài đặt

Bạn sẽ phải viết một chương trình thực hiện chiến thuật của JOI. Chương trình nên include thư viện `grader.h`.

Chương trình của bạn phải có hàm sau:

```cpp
int Memory(int N, int M)
```

Hàm phải thực hiện chiến thuật của JOI khi biết độ dài xâu $S$ và số đã ghi nhớ ở ngày trước.

- `int N`: độ dài của xâu $S$.
- `int M`: số đã ghi nhớ ở ngày trước. Trong ngày đầu tiên, `M = 0`.
- Trong hàm này, bạn có thể gọi hàm `Get` (sẽ được giải thích sau) tối đa một lần.
- Hàm phải trả về một số trong khoảng $[0, 2^{22})$, hoặc $-1$, hoặc $-2$. Bất kì giá trị nào khác cũng sẽ lập tức bị coi là trả lời sai.
	
	- Nếu giá trị là một số trong khoảng $[0, 2^{22})$, giá trị này sẽ được ghi nhớ cho ngày tiếp theo.
	- Nếu giá trị là $-1$, JOI sẽ trả lời "$S$ là dãy ngoặc đúng" qua email.
	- Nếu giá trị là $-2$, JOI sẽ trả lời "$S$ không phải dãy ngoặc đúng" qua email.

**Lưu ý: Kết quả của hàm chỉ được phụ thuộc vào giá trị $N$, $M$ và giá trị trả về của hàm `Get`. Trên thực tế khi chấm điểm hàm của bạn sẽ được gọi $2^{22} \times 4$ lần.**

Trong chương trình, bạn có thể gọi hàm sau:

```cpp
char Get(int I)
```

Hàm chỉ được gọi một lần trong mỗi lần chạy hàm `Memory`. Nếu điều này bị vi phạm, trình chấm trả về `[2]`.

Tham số $I$ phải thỏa mãn $1 \le I \le N$. Nếu điều này bị vi phạm, trình chấm trả về `[3]`.

Hàm trả về kí tự ở vị trí $I$ của xâu $S$.

## Quy trình chấm 

Mỗi file input chứa một số test, trong đó các test là các xâu $S$ có cùng độ dài $N$. 

Chương trình sẽ chấm theo quy trình sau. Chương trình sẽ thoát ngay lập tức khi có câu trả lời sai.

1. Tính trước tất cả giá trị trả về của hàm `Memory` với mỗi giá trị của $M$ và kết quả hàm `Get` trả về. Cụ thể, với mỗi $0 \le M < 2^{22}$, thực hiện:

	i. Với mỗi kí tự `c` trong `'<', '>', '[', ']'`, gọi hàm `Memory(N, M)` với giá trị của hàm `Get` là `c`. Gọi `m(M, c)` là giá trị trả về của hàm.

	ii. Trong bốn lần gọi, hàm `Memory` phải hoặc cùng gọi hàm `Get` hoặc cùng không gọi. Nếu hàm `Get` được gọi, tham số `I` phải giống nhau ở cả 4 lần. Nếu không, các giá trị `m(M, c)` phải giống hệt nhau. Nếu điều này không thỏa mãn, trình chấm trả về `[4]`. Gọi giá trị `I` được truyền vào hàm `Get` là `i(M)`.

2. Với mỗi xâu trong test, mô phỏng lại bài toán theo đề bài như sau:

	i. Ban đầu, gán `M = 0`.

	ii. Lặp lại các bước sau:

		a. Gọi $c$ là kí tự thứ $i(M)$ của $S$.

		b. Thay `M` bằng $m(M, c)$. 

		c. Nếu `M = -1` hoặc `M = -2`, chuyển sang iii

		d. Nếu vòng lặp quá 15000 lần, chuyển sang iii

	iii. Chương trình trả về sai `[6]` nếu:

	- $S$ là xâu đúng, và `M` khác `-1`.

	- $S$ là xâu không đúng, và `M` khác `-2`.

3. Kết quả là đúng.

## Lưu ý 

- Hàm `Memory` sẽ bị gọi $2^{22} \times 4$ lần, hãy tính toán thời gian và bộ nhớ chạy theo số lần gọi.

- Hàm `Memory` sẽ bị gọi với mọi giá trị của $M$, kể cả giá trị có thể không tồn tại theo thuật toán của bạn. Khi đó hãy trả về đúng yêu cầu của phần trên.

## Biên dịch

```bash
g++ -O2 -s -lm -o grader-simple grader-simple.cpp memory.cpp
g++ -O2 -s -lm -o grader-strict grader-strict.cpp memory.cpp
```

Trình chấm `grader-simple` sẽ tương tác trực tiếp với hàm `Memory` thay vì làm theo quy trình chấm.

## Dữ liệu nhập vào của trình chấm

- Dòng đầu tiên gồm 2 số $N$ và $Q$ ($0 \le Q \le 2^{31} -1$), độ dài của các xâu $S$ và số test.
- $Q$ dòng tiếp theo, mỗi dòng gồm 1 xâu độ dài $N$ - test thứ $i$.

## Dữ liệu xuất ra của trình chấm

- $Q$ dòng, mỗi dòng gồm 1 số $-1$ hoặc $-2$ thể hiện đáp số của test thứ $i$.

Với các loại `[1]`, `[2]`, `[3]`, `[4]`, `[5]`, chương trình sẽ in ra `Wrong Answer [x]` và thoát.

## Giới hạn

Trong tất cả các test:

- $1 \le |S| \le 100$
- Xâu $S$ chỉ gồm các kí tự `[, ], <, >`.

### Subtask 1 (10 điểm)

- $|S| \le 8$

### Subtask 2 (10 điểm)

- $|S| \le 14$

### Subtask 3 (5 điểm)

- $|S| \le 24$

### Subtask 4 (5 điểm)

- $|S| \le 30$

### Subtask 5 (10 điểm)

- Xâu chỉ gồm các kí tự `<, >`.

### Subtask 6 (60 điểm)

Không có giới hạn gì thêm.

## Ví dụ 

### Input

```
4 1
<>[]
```

### Output

```
-1
```