#include <bits/stdc++.h>
using namespace std;

const int N = 755;

int n, m;
char a[N][N], tmp[N][N];

void rotate() {
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) tmp[m - j + 1][i] = a[i][j];
	swap(n, m);
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) a[i][j] = tmp[i][j]; 
}

int h[N];
void solve(long long corner[][N]) {
	for (int j = 1; j <= m; ++j) h[j] = 0; h[0] = -1;
	for (int i = 1; i <= n; ++i) {
		stack <int> s;
		for (int j = 1; j <= m; ++j) h[j] = (a[i][j] == '1' ? h[j] + 1 : 0);
		int cur = 0; s.push(0);
		for (int j = 1; j <= m; ++j) {
			while(h[s.top()] >= h[j]) {
				int u = s.top(); s.pop(); cur -= (u - s.top()) * h[u]; 
			}
			int u = s.top(); cur += (j - u) * h[j];
			s.push(j);
			corner[i][j] = cur;
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) corner[i][j] += (corner[i-1][j] + corner[i][j-1] - corner[i-1][j-1]);
	}
}

long long T[4][N][N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> a[i][j];
	
	for (int i = 0; i < 4; ++i) {
		solve(T[i]); rotate();
	}

	long long res = T[0][n][m];
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) if (a[i][j] == '1') {
			long long ans = T[0][i-1][m] + T[1][m-j][n] + T[2][n-i][m] + T[3][j-1][n]
						  - T[0][i-1][j-1] - T[1][m-j][i-1] - T[2][n-i][m-j] - T[3][j-1][n-i];
			res = min(res, ans);
		}
	}

	printf("%lld\n", res);
}