#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
const int N = 1005;
const int dx[] = {0, 0, -1, +1}, dy[] = {-1, +1, 0, 0};

int n, m;
int a[N][N];
long long f1[N][N];
long long f2[N][N];
long long f3[N][N];
long long f4[N][N];
long long res = -INF;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];
		}
	}

	for (int i = 0; i <= n + 1; ++i) {
		for (int j = 0; j <= m + 1; ++j) {
			f1[i][j] = f2[i][j] = f3[i][j] = f4[i][j] = -INF;
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			f1[i][j] = max({(long long)-a[i][j] + i + j, f1[i - 1][j], f1[i][j - 1]});
		}
		for (int j = m; j >= 1; --j) {
			f2[i][j] = max({(long long)-a[i][j] + i - j, f2[i - 1][j], f2[i][j + 1]});
		}
	}

	for (int i = n; i >= 1; --i) {
		for (int j = 1; j <= m; ++j) {
			f3[i][j] = max({(long long)-a[i][j] - i + j, f3[i + 1][j], f3[i][j - 1]});
		}
		for (int j = m; j >= 1; --j) {
			f4[i][j] = max({(long long)-a[i][j] - i - j, f4[i + 1][j], f4[i][j + 1]});
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			res = max(res, a[i][j] - 1 - i - j + f1[i][j]);
			res = max(res, a[i][j] - 1 - i + j + f2[i][j]);
			res = max(res, a[i][j] - 1 + i - j + f3[i][j]);
			res = max(res, a[i][j] - 1 + i + j + f4[i][j]);
		}
	}

	cout << res << endl;
}