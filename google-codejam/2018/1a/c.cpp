#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int INF = 1e9;

int n, P;
int l[N];
double r[N];
double dp[N][N * 250];

void solve() {
	cin >> n >> P;
	int total = 0;

	for (int i = 1; i <= n; ++i) {
		int w, h; cin >> w >> h;
		total += 2 * (w + h);
		l[i] = min(w, h);
		r[i] = sqrt(w * w + h * h);
	}

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n * 250; ++j) {
			dp[i][j] = -INF;
		}
	}

	dp[0][0] = 0.0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= i * 250; ++j) {
			dp[i][j] = dp[i - 1][j];
			if (j >= l[i]) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j - l[i]] + r[i]);
			}
		}
	}

	double mx = 0.0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= n * 250; ++j) {
			if (2 * j <= P - total) {
				mx = max(mx, 2 * dp[i][j]);
			}
		}
	}

	if (mx <= P - total) {
		cout << setprecision(6) << fixed << total + mx << endl;
	} else {
		cout << P << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;
	for (int itest = 1; itest <= tt; ++itest) {
		cout << "Case #" << itest << ": ";
		solve();
	}
}