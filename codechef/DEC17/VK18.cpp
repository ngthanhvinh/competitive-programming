#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int val[N * 2];
int sumval[N * 2];
long long dp[N];

void prepare() {
	for (int i = 1; i < 2 * N; ++i) {
		int dig = i % 10;
		val[i] = val[i / 10] + (dig % 2 == 0 ? dig : -dig);
	}
	for (int i = 1; i < 2 * N; ++i) {
		if (val[i] < 0) val[i] = -val[i];
		sumval[i] = sumval[i - 1] + val[i];
	}

	for (int n = 1; n < N; ++n) { // prepare the answers for every N
		dp[n] = dp[n - 1] + 2LL * (sumval[2 * n - 1] - sumval[n]); // (1,N); (2,N); (3,N), ...; (N-1,N)
		dp[n] += val[n + n]; // (N,N)
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	prepare();
	int tt; cin >> tt;
	while(tt--) {
		int n; cin >> n;
		cout << dp[n] << endl;
	}
}