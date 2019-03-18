#include <bits/stdc++.h>
using namespace std;

const int N = 150;
const int md = 1e9 + 7;

int n, m;
int dp[N][N];

void add(int &x, int y) {
	x += y; while(x >= md) x -= md; while(x < 0) x += md;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 3; i <= n; ++i) dp[i][1] = 1;

	for (int j = 2; j <= m; ++j) {
		for (int i = 4; i <= n; ++i) {
			for (int k = 3; k < i; ++k) for (int l = 1; l < j; ++l) {
				int cur;
				if (k == 3) cur = dp[k][l];
				else cur = (dp[k - 1][l] + dp[k - 1][l - 1]) % md;
				add(dp[i][j], 1LL * cur * dp[i + 2 - k][j - l] % md);
			}
			add(dp[i][j], dp[i - 1][j]);
			add(dp[i][j], dp[i - 1][j - 1]);
		}
	}

	cout << dp[n][m] << endl;
}