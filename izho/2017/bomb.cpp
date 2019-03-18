/*
5 5 
00111
00111
11111
11110
11100
*/
#include <bits/stdc++.h>
using namespace std;

#define left __left
#define right __right

const int N = 2505;

int n, m, nrow, ncol;
int left[N][N];
int right[N][N];
int up[N][N];
int down[N][N];
char a[N][N];
int c[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) left[i][j] = a[i][j] == '1' ? left[i][j - 1] + 1 : 0;
		for (int j = m; j >= 1; --j) right[i][j] = a[i][j] == '1' ? right[i][j + 1] + 1 : 0;
	}

	for (int j = 1; j <= m; ++j) {
		for (int i = 1; i <= n; ++i) up[i][j] = a[i][j] == '1' ? up[i - 1][j] + 1 : 0;
		for (int i = n; i >= 1; --i) down[i][j] = a[i][j] == '1' ? down[i + 1][j] + 1 : 0;
	}

	nrow = n, ncol = m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) if (a[i][j] == '1') {
			nrow = min(nrow, up[i][j] + down[i][j] - 1);
			ncol = min(ncol, left[i][j] + right[i][j] - 1);
		}
	}

	int res = 0;
	for (int r = 1; r <= nrow; ++r) c[r] = ncol;

	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
		if (a[i][j] != '1') continue;

		int minleft = ncol;
		int minright = ncol;
		if (down[i][j] == 1) {
			for (int k = i; k >= i - nrow + 1; --k) {
				minleft = min(minleft, left[k][j]);
				minright = min(minright, right[k][j]);
				c[i - k + 1] = min(c[i - k + 1], minleft + minright - 1);
			}
		}

		minleft = minright = ncol;
		if (up[i][j] == 1) {
			for (int k = i; k <= i + nrow - 1; ++k) {
				minleft = min(minleft, left[k][j]);
				minright = min(minright, right[k][j]);
				c[k - i + 1] = min(c[k - i + 1], minleft + minright - 1);
			}
		}
	}

	for (int r = 1; r <= nrow; ++r) res = max(res, r * c[r]);
	cout << res << endl;
}