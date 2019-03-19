#include <bits/stdc++.h>
using namespace std;

void out(int X1, int Y1, int X2, int Y2) {
	printf("%d %d %d %d\n", Y1, X1, Y2, X2);
	exit(0);
}

const int N = 2010;

int n;
long long f[N][N], sumf[N][N];
long long K;
int h[N], l[N], r[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> K >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) cin >> f[i][j], f[i][j] = f[i-1][j] + f[i][j];
		for (int j = 1; j <= n; ++j) sumf[i][j] = sumf[i][j-1] + f[i][j];
	}

	for (int row = 1; row <= n; ++row) {
		for (int col = 1; col <= n; ++col) 
			if (f[row][col] - f[row-1][col] >= K && f[row][col] - f[row-1][col] <= 2 * K) out(row, col, row, col);
		for (int col = 1; col <= n; ++col) {
			if (f[row][col] - f[row-1][col] > 2 * K) { h[col] = 0; continue; }
			if (f[row][col] - f[row - 1 - h[col]][col] >= K) {
				out(row - h[col], col, row, col);
			}
			++h[col];
		}

		for (int col = 1; col <= n; ++col) {
			l[col] = col;
			while(l[col] > 1 && h[l[col] - 1] >= h[col]) l[col] = l[l[col] - 1];
		}
		for (int col = n; col >= 1; --col) {
			r[col] = col;
			while(r[col] < n && h[r[col] + 1] > h[col]) r[col] = r[r[col] + 1];
		}

		for (int col = 1; col <= n; ++col) {
			int L = l[col], R = r[col];
			long long sum = sumf[row][R] - sumf[row][L-1] - sumf[row - h[col]][R] + sumf[row - h[col]][L-1];
			if (sum >= K) {
				// TRACE
				long long cur = 0;
				for (int i = L; i <= R; ++i) { // for column
					cur += f[row][i] - f[row - h[col]][i];
					if (cur >= K) out(row - h[col] + 1, L, row, i);
				}
			}
		}
	}

	printf("NIE\n");
}