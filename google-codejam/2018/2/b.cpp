#include <bits/stdc++.h>
using namespace std;

const int N = 501;
const int INF = 1e9;

int R, B;
int dp[N][N][N];

void maximize(int &x, int y) {
	x = (x < y) ? y : x;
}

void solve() {
	cin >> R >> B;
	printf("%d\n", dp[N - 1][R][B]);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	// prepare
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < N; ++k) {
				dp[i][j][k] = -INF;
			}
		}
	}

	for (int numB = 0; numB < N; ++numB) dp[0][0][numB] = 0;
	
	for (int i = 1; i < N; ++i) {
		for (int numR = 0; numR < N; ++numR) {
			for (int numC = 0; numC < N; ++numC) {
				if (dp[i - 1][numR][numC] == -INF) continue;

				maximize(dp[i][numR][numC], dp[i - 1][numR][numC]);

				for (int j = (i != 1) ? 0 : 1, k = 1, sum = 0; ; ++j, ++k) {
					if (numR + (i - 1) * k >= N) break;
					sum += j;
					if (numC + sum >= N) break;
					maximize(dp[i][numR + (i - 1) * k][numC + sum], dp[i - 1][numR][numC] + k);
				}
			}
		}
	}

	int ntest; cin >> ntest;

	for (int itest = 1; itest <= ntest; ++itest) {
		printf("Case #%d: ", itest);
		solve(); 
	}
}