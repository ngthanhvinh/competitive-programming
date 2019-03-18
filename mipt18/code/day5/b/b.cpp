#include <bits/stdc++.h>
using namespace std;

int n;
long long c;
long long v;
long long dp[64][2];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> c;
	++c;
	for (int i = 1; i <= n; ++i) {
		long long x; cin >> x;
		v += x;
	}

	dp[62][0] = 1;
	for (int i = 61; i >= 0; --i) {
		for (int smaller = 0; smaller < 2; ++smaller) {
			if (!dp[i + 1][smaller]) continue;

			int high = (v >> i & 1);
			if (!smaller) {
				high = min(high, (int)(c >> i & 1));
			}

			for (int nxt = 0; nxt <= high; ++nxt) {
				int nsmaller = smaller;
				if (nxt < (c >> i & 1)) nsmaller = 1;
				dp[i][nsmaller] += dp[i + 1][smaller];
			}
		}
	}

	cout << dp[0][1] - 1 << endl;
}