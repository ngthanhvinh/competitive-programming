#include <bits/stdc++.h>
using namespace std;

const int N = 45, K = 64005;
const int inf = 1e9;
int n, k;
int f[2][N][K];
int c[N], l[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> c[i]; reverse(c + 1, c + n + 1);
	for (int i = 1; i <= n; ++i) cin >> l[i]; reverse(l + 1, l + n + 1);

	for (int j = 0; j <= 40; ++j) for (int money = 0; money <= k; ++money) f[0][j][money] = -inf;
	f[0][0][0] = 0;

	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= 40; ++j) for (int money = 0; money <= k; ++money) f[i&1][j][money] = -inf;
		for (int j = 0; j <= 40; ++j) for (int money = 0; money <= k; ++money) {
			int cur = l[i] - j;
			int add = min(j, l[i]) * c[i];
			f[i&1][j][money] = max(f[i&1][j][money], f[1 - (i&1)][j][money] + add);
			if (money + c[i] <= k && cur > 0) {
				f[i&1][j + 1][money + c[i]] = max(f[i&1][j + 1][money + c[i]], f[i&1][j][money] + c[i]);  
			}
		}
	}

	int ans = 0;
	for (int j = 0; j <= 40; ++j) for (int money = 0; money <= k; ++money) {
		ans = max(ans, f[n&1][j][money]);
	}
	cout << ans << endl;
}