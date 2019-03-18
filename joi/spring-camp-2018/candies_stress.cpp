#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const long long INF = 1e18;

int n, a[N];
long long dp[N][N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	for (int j = 1; j <= (n + 1) / 2; ++j) {
		dp[0][j] = -INF;
		for (int i = 1; i <= n; ++i) {
			dp[i][j] = -INF;
			for (int k = 0; k < max(1, i - 1); ++k) {
				dp[i][j] = max(dp[i][j], dp[k][j - 1] + a[i]);
			}
		}
		long long mx = -INF;
		for (int i = 1; i <= n; ++i) {
			mx = max(mx, dp[i][j]);
		}

		cout << mx << endl;
	}
}