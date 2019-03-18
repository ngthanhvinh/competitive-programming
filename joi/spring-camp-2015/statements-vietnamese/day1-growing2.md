# Growing Vegetables is Fun 2

- Thời gian: 1s
- Bộ nhớ: 256MB

Mr. JOI, một người làm vườn chuyên nghiệp, hằng năm trồng một loài cây có tên *IOI*. Khi gieo hạt cây *IOI* vào mùa đông, chúng sẽ trổ bông vào đầu xuân và đạt đến độ cao mong muốn. Một số cây sẽ cho những trái IOI thật đẹp khi thu đến. Mr.JOI thu hoạch những cây IOI ra quả. Những cây không ra quả sẽ héo vào mùa đông. 

Khu vườn của JOI được chia thành $N$ phần đánh số theo hướng Đông - Tây, cây IOI mọc ở phần thứ $i$. Khi mùa xuân đến, cây IOI thứ $i$ mọc đến độ cao $H_i$ và không cao thêm. Quả ở cây thứ $i$ có giá $P_i$ nếu được bán đi. Những cây không có quả không có giá trị thương mại.

Mr.JOI, sau khi xem xét tình trạng của các cây vào mùa xuân, đã quyết định tối đa hóa lợi nhuận bằng cách nhổ một số cây khỏi vườn. Chi phí để nhổ cây $i$ là $C_i$. Những cây bị nhổ lập tức sẽ héo. Mr.JOI chỉ có thể nhổ cây vào mùa xuân, không thể nhổ vào mùa hè hay mùa thu. 

Cây IOI là một loài cây đòi hỏi rất nhiều ánh sáng mặt trời trong mùa hè. Xét một cây IOI được trồng trong phần nào đó của vườn, nếu cả bên trái và phải của nó đều bị một cây có độ cao lớn hơn chắn mất, cây IOI đó sẽ không cho quả vào mùa thu. Nói cách khác, xét các cây không bị nhổ, cây IOI thứ $i$ chỉ ra quả khi:
- Tất cả các cây $j < i$ đều có $H_j \le H_i$, **hoặc**
- Tất cả các cây $j > i$ đều có $H_j \le H_i$.

Lợi nhuận của việc trồng cây được tính bằng tổng giá trị các cây ra quả, trừ đi tổng chi phí nhổ cây. Số tiền lớn nhất Mr.JOI có thể thu được là bao nhiêu?

## Yêu cầu
Cho thông tin của JOI về các cây IOI đang trồng, hãy tìm lợi nhuận tối đa JOI có thể thu được.

## Dữ liệu nhập vào
Hãy đọc từ standard input dữ liệu theo định dạng sau:

- Dòng đầu tiên gồm một số duy nhất $N$, số phần / số cây IOI trong vườn của JOI.
- N dòng tiếp theo miêu tả các cây IOI theo thứ tự. Dòng thứ $i$ gồm 3 số $H_i, $P_i$, $C_i$ thể hiện độ cao, giá trị quả và chi phí nhổ của cây thứ $i$.

## Dữ liệu xuất ra
In ra một dòng duy nhất ghi lợi nhuận tối đa thu được của JOI.

## Giới hạn
Trong tất cả các test:

- $3 \le N \le 100 000$
- $1 \le H_i, P_i, C_i \le 1 000 000 000$

## Subtask
### Subtask 1 (10 điểm)
- $N \le 20$ với mọi test. 

### Subtask 2 (10 điểm)
- $N \le 300$ với mọi test.

### Subtask 3 (10 điểm)
- $N \le 5000$ với mọi test.

### Subtask 4 (50 điểm)
- $H_i \neq H_j$ với mọi $1 \le i < j \le N$ trong mọi test.

### Subtask 5 (20 điểm)
Không có điều kiện gì thêm.

## Ví dụ
### Input 1
```
7
22 60 30
46 40 30
36 100 50
11 140 120
38 120 20
24 90 60
53 50 20
```
### Output 1
```
320
```

Xét trạng thái sau khi nhổ 2 cây $2$ và $7$. Ta có bảng sau:

| Thứ tự | Độ cao | Ra quả |
|--------|--------|--------|
| 1 | 22 | có | 
| 3 | 36 | có |
| 4 | 11 | không |
| 5 | 38 | có |
| 6 | 24 | có |

Các cây 1, 3, 5, 6 ra quả cho lợi nhuận lần lượt là 60, 100, 120, 90. Chi phí để nhổ cây 2 và 7 là 30 và 20. JOI nhận được $60 + 100 + 120 + 90 - (30 + 20) = 320$. Đây cũng là một trong những cách tối ưu.

### Input 2
```
5
18 150 180
18 380 250
18 140 170
17 180 900
14 150 520
```
### Output 2
```
1000
```

Trong ví dụ này tất cả các cây đều sẽ ra quả, không cần nhổ cây nào.

### Input 3
```
8
52 156 59
15 166 185
16 122 115
24 161 154
44 252 678
32 225 557
44 155 254
59 57 253
```
### Output 3
```
854
```