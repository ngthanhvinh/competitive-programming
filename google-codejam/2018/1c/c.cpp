#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int MAX = 300;
const long long INF = 1e18;

int n, w[N];
long long dp[N][MAX + 1];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> w[i];
	}

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= MAX; ++j) {
			dp[i][j] = INF;
		}
	}

	dp[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= MAX && j <= i; ++j) {
			dp[i][j] = dp[i - 1][j];
			if (j > 0 && dp[i - 1][j - 1] <= 6LL * w[i]) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + w[i]);
			}
		}
	}

	for (int i = MAX; i >= 1; --i) {
		if (dp[n][i] != INF) {
			printf("%d\n", i); return;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;
	for (int itest = 1; itest <= tt; ++itest) {
		printf("Case #%d: ", itest);
		solve();
	}
}