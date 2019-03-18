#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
const int md = 1e9 + 7;

int n, k;
int dp[N][N], part[N][N];
int ans;

void add(int &x, int y) {
	x += y; while(x >= md) x -= md; while(x < 0) x += md;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	
	cin >> n >> k;

	dp[1][0] = 1;
	for (int i = 2; i <= n; ++i) {
		for (int j = 0; j <= i - 2; ++j) if (dp[i - 1][j]) {
			if (j > 0) add(dp[i][j - 1], 1LL * j * dp[i - 1][j] % md);
			add(dp[i][j + 1], dp[i - 1][j]);
			add(dp[i][j], 1LL * (i - j - 1) * dp[i - 1][j] % md);
		}
	}

	part[0][0] = 1;
	for (int j = 1; j <= n; ++j) {
		for (int i = j; i <= n; ++i) {
			part[i][j] = part[i - 1][j] + part[i - 1][j - 1] - 
									 ((i - k - 1 >= 0) ? part[i - k - 1][j - 1] : 0);
			while (part[i][j] < 0) part[i][j] += md;
			while (part[i][j] >= md) part[i][j] -= md;
		}
	}

	for (int ngroup = 1; ngroup <= n; ++ngroup) {
		add(ans, 1LL * dp[ngroup][0] * part[n][ngroup] % md);
	}

	cout << ans << endl;
}