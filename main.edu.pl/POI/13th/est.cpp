#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N];
int f[N][N];
int pre[N][N], suf[N][N];

int main() {
	ios::sync_with_stdio(false);
	cin >> m >> n; m++;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i], a[i]++, a[i] += a[i - 1];
	}
	memset(f, INF, sizeof f);
	memset(suf, INF, sizeof suf);
	memset(pre, INF, sizeof pre);
	f[1][1] = pre[1][1] = suf[1][1] = 0;
	for (int i = 2; i <= n; ++i) {
		if (a[i] <= m) f[i][1] = 0;
		int pos = 1;
		for (int j = 2; j <= i; ++j) {
			while (pos < j && a[pos - 1] <= 2 * a[j - 1] - a[i]) pos++;
			if (a[i] - a[j - 1] <= m) {
				f[i][j] = min(f[i][j], suf[j - 1][pos] + a[i] - 2 * a[j - 1]);
				f[i][j] = min(f[i][j], pre[j - 1][pos - 1] + 2 * a[j - 1] - a[i]);
			}
		}
		for (int j = 1; j <= i; ++j) pre[i][j] = min(pre[i][j - 1], f[i][j] - a[j - 1]);
		for (int j = i; j >= 1; --j) suf[i][j] = min(suf[i][j + 1], f[i][j] + a[j - 1]);
	}
	int res = INF;
	for (int i = 1; i <= n; ++i) res = min(res, f[n][i]);
	cout << res;
}