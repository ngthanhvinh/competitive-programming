#include <bits/stdc++.h>
using namespace std;

const int N = 3005;
const int mod = 1e9 + 7;
const int inv2 = 5e8 + 4;

int n, m;
int fact[N];
int comb[N][N];
int pow4[N];
int pow_inv2[N];
int dp[N];
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

	pow4[0] = 1;
	for (int i = 1; i < N; ++i) pow4[i] = 4LL * pow4[i - 1] % mod;
	pow_inv2[0] = 1;
	for (int i = 1; i < N; ++i) pow_inv2[i] = 1LL * pow_inv2[i - 1] * inv2 % mod;

	for (int i = 0; i < N; ++i) comb[i][0] = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j <= i; ++j) comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
	}

	// solve
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			for (int c = 0; c <= min(i, j); ++c) {
				if ((i + j - 2 * c) % 3 != 0) continue;
				int ab = (i + j - 2 * c) / 3;
				int b = i - c - ab;
				int a = j - c - ab;
				if (a < 0 || b < 0) continue;

				int cur;
				cur = 1LL * comb[i][c] * comb[j][c] % mod;
				cur = 1LL * cur * fact[c] % mod;
				cur = 1LL * cur * pow4[c] % mod;
				cur = 1LL * cur * calc(i - c, j - c, a) % mod;
				cur = 1LL * cur * calc(j - c - 2 * a, i - c - a, b) % mod;
				cur = 1LL * cur * comb[n][i] % mod;
				cur = 1LL * cur * comb[m][j] % mod;

				add(res, cur);
			}
		}
	}

	cout << (res - 1 + mod) % mod << endl;
}