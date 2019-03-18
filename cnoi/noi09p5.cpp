#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const int mod = 1024523;

int n, m;
int dp[N][N][N];
char a[N], b[N];

void add(int &x, int y) {
	x += y; while(x >= mod) x -= mod; while(x < 0) x += mod;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= m; ++i) cin >> b[i];

	dp[n][m][n] = 1;
	for (int sum = n + m; sum >= 1; --sum) {
		for (int a1 = 0; a1 <= n && a1 <= sum; ++a1) {
			int b1 = sum - a1;
			if (b1 > m) continue;
			for (int a2 = 0; a2 <= n && a2 <= sum; ++a2) {
				int b2 = sum - a2;
				if (b2 > m) continue;
				//printf("a1 = %d b1 = %d a2 = %d b2 = %d -> dp = %d\n", a1, b1, a2, b2, dp[a1][b1][a2]);

				if (a1 > 0 && a2 > 0 && a[a1] == a[a2]) add(dp[a1 - 1][b1][a2 - 1], dp[a1][b1][a2]);
				if (a1 > 0 && b2 > 0 && a[a1] == b[b2]) add(dp[a1 - 1][b1][a2], dp[a1][b1][a2]);
				if (b1 > 0 && a2 > 0 && b[b1] == a[a2]) add(dp[a1][b1 - 1][a2 - 1], dp[a1][b1][a2]);
				if (b1 > 0 && b2 > 0 && b[b1] == b[b2]) add(dp[a1][b1 - 1][a2], dp[a1][b1][a2]);
			}
		}
	}

	printf("%d\n", dp[0][0][0]);
}