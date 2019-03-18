#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const long long INF = 1e18;

int n, a[N];
long long dp[N][N];
int best[N][N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i], a[i] += a[i - 1];

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) dp[i][j] = INF;
	}
	for (int i = 1; i <= n; ++i) dp[i][i] = 0, best[i][i] = i;
	for (int gap = 1; gap < n; ++gap) {
		for (int i = 1; i + gap <= n; ++i) {
			int j = i + gap;
			for (int k = max(i, best[i][j - 1]); k <= min(j - 1, best[i + 1][j]); ++k) {
				if (dp[i][j] > dp[i][k] + dp[k + 1][j] + a[j] - a[i - 1]) {
					dp[i][j] = dp[i][k] + dp[k + 1][j] + a[j] - a[i - 1];
					best[i][j] = k;
				}
			}
		}
	}

	printf("%lld\n", dp[1][n]);
}