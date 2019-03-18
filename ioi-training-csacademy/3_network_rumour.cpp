#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9 + 7;

int n;
int e[13][13];
int dp[13][1 << 13];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) cin >> e[i][j];
	}

	for (int i = 0; i < n; ++i) for (int mask = 0; mask < (1 << n); ++mask) {
		dp[i][mask] = inf;
	}

	for (int i = 0; i < n; ++i) dp[i][1 << i] = 0;

	for (int mask = 1; mask < (1 << n); ++mask) {
		for (int i = 0; i < n; ++i) if (mask & (1 << i)) {
			for (int sub = mask; sub > 0; sub = mask & (sub - 1)) {
				for (int j = 0; j < n; ++j) if (sub & (1 << j)) {
					dp[i][mask] = min(dp[i][mask], e[i][j] + max(dp[j][sub], dp[i][mask ^ sub]));
				}
			}
		}
	}

	cout << dp[0][(1 << n) - 1] << endl;
}