#include <bits/stdc++.h>
using namespace std;

const int N = 110;
const int md = 1e9 + 7;

int n, L;
int a[N];
int f[N][N][1010][2][2];

void add(int &x, int y) { x += y; while(x >= md) x -= md; if (x < 0) x += md; }

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> L;
	if (n == 1) {
		printf("1\n"); return 0;
	}
	for (int i = 1; i <= n; ++i) cin >> a[i];
	sort(a + 1, a + n + 1);
	for (int i = n; i >= 2; --i) a[i] = a[i] - a[i-1]; a[1] = 0;

	f[0][0][0][0][0] = 1;
	for (int i = 0; i < n; ++i) for (int j = 0; j <= i; ++j) for (int s = 0; s <= L; ++s) {
		for (int l = 0; l < 2; ++l) for (int r = 0; r < 2; ++r) {
			int cur = f[i][j][s][l][r]; if (cur == 0) continue;
			int ns = s + (2 * j - l - r) * a[i + 1]; if (ns > L) continue;
			
			// push a[i] to the front or the back of a component
			if (!l) add(f[i + 1][j][ns][1][r], 1LL * cur * (j - (i != n - 1 ? r : 0)) % md);
			if (!r) add(f[i + 1][j][ns][l][1], 1LL * cur * (j - (i != n - 1 ? l : 0)) % md);
			add(f[i + 1][j][ns][l][r], 1LL * cur * (2 * j - l - r) % md);

			// use a[i] to connect two distinct components
			if (j >= 1) add(f[i + 1][j - 1][ns][l][r], 1LL * cur * ((j - l - r) * (j - 1) + (i == n - 1 ? l * r : 0)) % md);

			// create a new component
			if (!l) add(f[i + 1][j + 1][ns][1][r], cur);
			if (!r) add(f[i + 1][j + 1][ns][l][1], cur);
			add(f[i + 1][j + 1][ns][l][r], cur);
		}
	}
	
	int ans = 0;
	for (int s = 0; s <= L; ++s) {
		add(ans, f[n][1][s][1][1]);
	}
	cout << ans << '\n';
}