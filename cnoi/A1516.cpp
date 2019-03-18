#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const int mod = 1e9 + 7;
const int offset = 9;

string A, B;
int dp[N][2][30];

void add(int &x, int y) { x += y; while(x >= mod) x -= mod; }

int solve() {
	cin >> A >> B;
	while(A.size() < B.size()) A = '0' + A;
	while(B.size() < A.size()) B = '0' + B;

	int n = B.size();
	A = ' ' + A;
	B = ' ' + B;

	memset(dp, 0, sizeof dp);
	dp[0][0][offset] = 1; // dp[i][smaller][diff]
	for (int i = 0; i < n; ++i) {
		for (int smaller = 0; smaller < 2; ++smaller) {
			for (int diff = -offset; diff <= offset; ++diff) {
				if (!dp[i][smaller][diff + offset]) continue;

				int high = 9;
				if (!smaller) high = B[i + 1] - '0';
				
				for (int dig = 0; dig <= high; ++dig) {
					int ndiff = diff * 2 + (A[i + 1] - '0') - dig; // F(X) <= F(A)
					ndiff = max(ndiff, -offset);
					ndiff = min(ndiff, offset);

					add(dp[i + 1][smaller | (dig < B[i + 1] - '0')][ndiff + offset], dp[i][smaller][diff + offset]);
				}
			}
		}
	}

	int res = 0;
	for (int diff = 0; diff <= offset; ++diff) {
		add(res, dp[n][0][diff + offset]);
		add(res, dp[n][1][diff + offset]);
	}

	return res;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int tt; cin >> tt;
	for (int itest = 1; itest <= tt; ++itest) {
		printf("Case #%d: %d\n", itest, solve());
	}
}