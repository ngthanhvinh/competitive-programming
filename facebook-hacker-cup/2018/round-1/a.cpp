#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int N = 1005;

int n, dp[N][3];
char a[N][3];

void add(int &x, int y) {
	x += y; while(x >= mod) x -= mod;
}

void solve() {
	cin >> n;
	for (int i = 0; i < 3; ++i) {
		for (int j = 1; j <= n; ++j) cin >> a[j][i];
	}
	memset(dp, 0, sizeof dp);
	dp[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		if (a[i][0] == '.' && a[i][1] == '.') add(dp[i][0], dp[i - 1][1]);
		if (a[i][1] == '.' && a[i][0] == '.') add(dp[i][1], dp[i - 1][0]); 
		if (a[i][1] == '.' && a[i][2] == '.') add(dp[i][1], dp[i - 1][2]);
		if (a[i][2] == '.' && a[i][1] == '.') add(dp[i][2], dp[i - 1][1]);
	}
	printf("%d\n", dp[n][2]);
}

int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int ntest; cin >> ntest;
	for (int itest = 1; itest <= ntest; ++itest) {
		printf("Case #%d: ", itest);
		solve();
	}
}