#include <bits/stdc++.h>
using namespace std;
const int N = 1010, mod = (int)1e9 + 7;

int n, m, a[N], s;
int f[N][N];

void solve() {
	cin >> n >> m >> s; memset(f, 0, sizeof f); f[0][s] = 1;
	for (int i = 1; i <= m; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) for (int pos = 1; pos <= n; pos++) {
		if (pos + a[i] <= n) f[i][pos] = (f[i][pos] + f[i-1][pos + a[i]]) % mod;
		if (pos - a[i] > 0) f[i][pos] = (f[i][pos] + f[i-1][pos - a[i]]) % mod;
	}
	for (int i = 1; i <= n; i++) cout << f[m][i] << ' '; cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--) solve();
}