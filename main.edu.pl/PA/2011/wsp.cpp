#include <bits/stdc++.h>
using namespace std;
const int N = 500010;

int a[N], begin[N], end[N], val[N];
int n;
int block;
int ans = 1;

int main() {
	freopen("/media/vinh/Vinh/Informatics/cppProblems/main.edu.pl/PA/2011/wsp_tests/wsp1b.in", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; for (int i = 1; i <= n; i++) { int x, y; cin >> x >> y; a[i] = x + y; }
	a[0] = -1;
	for (int i = 1; i <= n; i++) {
		if (a[i] != a[i-1]) {
			end[block] = i-1;
			++block;
			begin[block] = i;
			val[block] = a[i];
		}
	}
	end[block] = n;
	for (int i = 1; i <= block; i++) cout << i << ' ' << val[i] << ' ' << begin[i] << ' ' << end[i] << endl;
	for (int i = 1; i <= block; i++) {
		if (val[i] % 2 == 0) {
			int res = 2 * (end[i] - begin[i] + 1) - 1;
			if (begin[i] >= 2 && a[begin[i]-1] >= val[i] / 2) res++;
			if (end[i] < n && a[end[i]+1] >= val[i] / 2) res++;
			ans = max(ans, res);
		}
	}
	cout << ans << endl;
}