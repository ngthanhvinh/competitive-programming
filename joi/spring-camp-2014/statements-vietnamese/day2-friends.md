# Making Friends is Fun

Bạn là một người hoạt động ngầm, bí mật gìn giữ hòa bình thế giới.
Trên thế giới có $N$ quốc gia, đánh số từ 1 đến $N$. 
Mục tiêu của bạn là tạo ra mối quan hệ bằng hữu nhiều nhất có thể giữa các quốc gia. 
Để có thể lên kế hoạch cho tổ chức, bạn vẽ một bức tranh thể hiện các mối quan hệ quốc tế hiện tại.

Bạn lấy một tờ giấy lớn và vẽ ra $N$ điểm trên đó, mỗi điểm thể hiện một quốc gia. 
Sau đó, bạn vẽ $M$ mũi tên, mỗi mũi tên chỉ từ quốc gia $a$ đến quốc gia $b$ thể hiện "$a$ đang có đại sứ tại quốc gia $b$$. 
Để tiện lợi, ta gọi mũi tên chỉ từ $a$ đến $b$ là $F(a, b)$.
$N$ điểm và các mũi tên thể hiện các mối quan hệ quốc tế hiện tại.

Hãy nghĩ đến việc lập ra một *Hội nghị Quan hệ Bằng hữu Quốc Tế* (sau này, ta sẽ gọi tắt là Hội nghị) giữa 2 quốc gia để thiết lập quan hệ bằng hữu. 
Để 2 nước $p$ và $q$ có thể tổ chức Hội nghị, cần phải có một quốc gia $x$ đang có đại sứ tại cả 2 quốc gia $p$ và $q$ làm trung gian. 
Sau Hội nghị, 2 nước $p$ và $q$ sẽ gửi đại sứ sang nước còn lại. 
Tức sẽ có $F(p, q)$ và $F(q, p)$ được vẽ thêm nếu chúng chưa được tồn tại từ trước, và điều kiện là tồn tại $x$ sao cho có $F(x, p)$ và $F(x, q)$.

Công việc của bạn là lựa chọn các quốc gia tham gia hội nghị, cũng như quốc gia trung gian để hội nghị thành công tốt đẹp. 
Khi mô phỏng công việc này, tổ chức đã quyết định xét *độ hòa bình thế giới* bằng số mũi tên được vẽ sau một số bước lập Hội nghị.
Bạn được giao nhiệm vụ tính *độ hòa bình thế giới* tối đa có thể.

## Yêu cầu

Cho thông tin hiện tại về các quốc gia và mối quan hệ giữa các quốc gia hiện tại. Bằng việc liên tục lập các hội nghị, tính số lượng mũi tên tối đa đạt được.

## Dữ liệu nhập vào

- Dòng đầu tiên gồm 2 số $N, M$ - số quốc gia và số mũi tên ban đầu.
- $M$ dòng tiếp theo, mỗi dòng gồm 2 số $A_i, B_i$ thể hiện $F(A_i, B_i)$.

## Kết quả xuất ra

- In ra 1 dòng duy nhất ghi 1 số là đáp số cần tìm.

## Giới hạn

- $1 \le N \le 10^5$
- $0 \le M \le 2 \times 10^5$
- $1 \le A_i, B_i \le N$ ($1 \le i \le M$)
- $A_i \neq B_i$ ($1 \le i \le M$)
- Mỗi mũi tên xuất hiện đúng 1 lần.

### Subtask 1 (5 điểm)

- $N \le 100$

### Subtask 2 (30 điểm)

- $N \le 5000$

### Subtask 3 (65 điểm)

Không có giới hạn gì thêm.

## Ví dụ

### Input
```
5 4
1 2
1 3
4 3
4 5
```

### Output
```
10
```

- 1 làm trung gian, Hội nghị 2 và 3 (+2)
- 4 làm trung gian, Hội nghị 3 và 5 (+2)
- 3 làm trung gian, Hội nghị 2 và 5 (+2)
