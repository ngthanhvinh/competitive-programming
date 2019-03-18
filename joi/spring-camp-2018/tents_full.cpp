#include <bits/stdc++.h>
using namespace std;

const int N = 3005;
const int mod = 1e9 + 7;
const int inv2 = 5e8 + 4;

int n, m;
int fact[N];
int comb[N][N];
int dp[N][N];
int pow_inv2[N];
int res;

void add(int &x, int y) {
	x += y; while(x >= mod) x -= mod;
}

int calc(int n, int m, int a) {
	if (!a) return 1;
	int ret = 1;
			ret = 1LL * ret * comb[n][a] % mod;
			ret = 1LL * ret * comb[m][2 * a] % mod;
			ret = 1LL * ret * fact[2 * a] % mod;
			ret = 1LL * ret * pow_inv2[a] % mod;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;

	// prepare
	fact[0] = 1;
	for (int i = 1; i < N; ++i) fact[i] = 1LL * fact[i - 1] * i % mod;

	pow_inv2[0] = 1;
	for (int i = 1; i < N; ++i) pow_inv2[i] = 1LL * pow_inv2[i - 1] * inv2 % mod;

	for (int i = 0; i < N; ++i) comb[i][0] = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j <= i; ++j) comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
	}

	// SOLVE
	
	// calculate dp[][]
	for (int i = 0; i < N; ++i) dp[i][0] = dp[0][i] = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j < N; ++j) {
			add(dp[i][j], dp[i - 1][j]);
			add(dp[i][j], 4LL * j * dp[i - 1][j - 1] % mod);
		}
	}

	for (int a = 0; a <= n; ++a) {
		for (int b = 0; b <= m; ++b) {
			if (a + 2 * b > n) continue;
			if (b + 2 * a > m) continue;

			int cur = 1;
					cur = 1LL * cur * calc(n, m, a) % mod;
					cur = 1LL * cur * calc(m - 2 * a, n - a, b) % mod;
			int i = n - a - 2 * b;
			int j = m - b - 2 * a;
			cur = 1LL * cur * dp[i][j] % mod;

			add(res, cur);
		}
	}

	cout << (res - 1 + mod) % mod << endl;
}