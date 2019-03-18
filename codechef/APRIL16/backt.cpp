#include <bits/stdc++.h>
using namespace std;
#define ff(i, a, b) for (int i = a; i <= b; i++)
typedef vector<int> vi;
const int N = 51;

int n, k, str[N], v, bt[N];
string s;
int ans;

bool check(int pos, int last, int a[]) {
	for (int d = 1; pos - 2 * d > 0; ++d) if (a[pos-d] == a[pos - 2*d] && a[pos-d] == last) return 0;
	return 1;
}

void backt(int pos, int a[], int cnt, int last) {
	//cout << pos << ' ' << cnt << ' ' << last << ' ' << endl;
    if (pos == n+1) { ans++; return; }
   	if (cnt < 2) { if (check(pos, last, a)) a[pos] = last, backt(pos+1, a, cnt+1, last), a[pos] = 0; }
   	for (int next = 1; next <= 3; next++) if (next != last) {
   		if (check(pos, next, a)) a[pos] = next, backt(pos+1, a, 1, next), a[pos] = 0;
   	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	for (n = 1; n <= 15; ++n) ans = 0, backt(1, bt, 3, 0), cout << ans << endl;
}
