#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const int mod = 1e9 + 7;

int n, k;
int dp[N][N];

void add(int &x, int y) {
	x += y; while(x >= mod) x -= mod;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> k;

	dp[0][1] = 1;
	for (int i = 1; i <= k; ++i) {
		for (int j = 0; j <= n; ++j) {
			if (!dp[i - 1][j]) continue;
			add(dp[i][j], 1LL * (j + (n - j) * (n - 1)) * dp[i - 1][j] % mod);
			if (j < n) add(dp[i][j + 1], 1LL * (n - j) * dp[i - 1][j] % mod);
			if (j > 0) add(dp[i][j - 1], 1LL * j * (n - 1) * dp[i - 1][j] % mod);
		}
	}

	int res = 0;
	for (int i = 1; i <= n; ++i) {
		add(res, dp[k][i]);
	}

	cout << 1LL * res * n % mod << endl;
}