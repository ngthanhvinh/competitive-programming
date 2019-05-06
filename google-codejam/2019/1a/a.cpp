#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n;
string s[N];
int dp[N][N];
int common[N];
int mn[N][N];

int get_common(string &a, string &b) {
	int ret = 0;
	for (int i = 0; i < a.size() && i < b.size(); ++i) {
		if (a[i] != b[i]) return ret;
		else ++ret;
	}
	return ret;
}

int get(int l, int r) {
	if (l >= r) return 1e9;
	if (l <= 0 || r <= 0) return 1e9;
	return mn[l][r];
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> s[i];
		reverse(s[i].begin(), s[i].end());
	}
	sort(s + 1, s + n + 1);

	for (int i = 1; i <= n; ++i) cerr << s[i] << endl;

	for (int i = 1; i <= n - 1; ++i) {
		common[i] = get_common(s[i], s[i + 1]);
		//cerr << common[i] << endl;
	}

	for (int i = 1; i <= n - 1; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (j == i + 1) {
				mn[i][j] = common[i];
			} else {
				mn[i][j] = min(mn[i][j - 1], common[j - 1]);
			}
			cerr << i << ' ' << j << ' ' << mn[i][j] << endl;
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			dp[i][j] = -1e9;
		}
	}
	dp[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			dp[i][j] = dp[i - 1][j];
			if (j == i) {
				// choose i
				if (i >= 2 && get(i - 1, i) > 0) {
					for (int k = 0; k <= i - 2; ++k) {
						if (k < 2 || (k >= 2 && get(k - 1, k) > get(k, i - 1))) {
							dp[i][j] = max(dp[i][j], dp[k][k] + 2);
						}
					}
				}
			}
			cerr << "dp " << i << ' ' << j << ' ' << dp[i][j] << endl;
		}
	}

	int res = 0;
	for (int i = 0; i <= n; ++i) res = max(res, dp[n][i]);
	cout << res << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		cout << "Case #" << it << ": ";
		solve();
	}
}