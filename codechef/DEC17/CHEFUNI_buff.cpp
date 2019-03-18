#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int inf = 1e9;

int X, Y, Z;
int A, B, C;
int dp[N][N][N];

void mnm(int &x, int y) { if (x > y) x = y; }

void solve() {
	cin >> X >> Y >> Z >> A >> B >> C;
	// reset
	for (int i = 0; i <= X; ++i) {
		for (int j = 0; j <= Y; ++j) {
			for (int k = 0; k <= Z; ++k) dp[i][j][k] = inf;
		}
	}

	// process
	dp[0][0][0] = 0;
	for (int i = 0; i <= X; ++i) {
		for (int j = 0; j <= Y; ++j) {
			for (int k = 0; k <= Z; ++k) {
				if (i == 0 && j == 0 && k == 0) continue; // base case
				// A
				if (i > 0) mnm(dp[i][j][k], dp[i-1][j][k] + A);
				if (j > 0) mnm(dp[i][j][k], dp[i][j-1][k] + A);
				if (k > 0) mnm(dp[i][j][k], dp[i][j][k-1] + A);
				// B
				if (i > 0 && j > 0) mnm(dp[i][j][k], dp[i-1][j-1][k] + B);
				if (j > 0 && k > 0) mnm(dp[i][j][k], dp[i][j-1][k-1] + B);
				if (i > 0 && k > 0) mnm(dp[i][j][k], dp[i-1][j][k-1] + B);
				// C
				if (i > 0 && j > 0 && k > 0) mnm(dp[i][j][k], dp[i-1][j-1][k-1] + C);
			}
		}
	}

	cout << dp[X][Y][Z] << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	while(tt--) {
		solve();
	}
}