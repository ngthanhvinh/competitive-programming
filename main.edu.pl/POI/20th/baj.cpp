#include <bits/stdc++.h>
using namespace std;

const int N = 1000020;

int n, a[N], f[N][3];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) for (int j = 0; j < 3; ++j) f[i][j] = 1e9;
	f[1][a[1] + 1] = 0;
	for (int i = 2; i <= n; ++i) {
		for (int j = 0; j < 3; ++j) if (f[i-1][j] != 1e9) {
			for (int k = 0; k <= 3; ++k) {
				int x = a[i] + (j - 1) * k;
				if (x + 1 >= j && x < 2 && x > -2) f[i][x + 1] = min(f[i][x + 1], f[i-1][j] + k);
			}
		}
	}

	int ans = 1e9;
	for (int i = 0; i < 3; ++i) ans = min(ans, f[n][i]);
	if (ans == 1e9) printf("BRAK\n"); else printf("%d\n", ans);
}