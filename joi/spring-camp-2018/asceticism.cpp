#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int mod = 1e9 + 7;

int n, m;
int fact[N];
int ifact[N];

int binpow(int a, int b) {
	int ret = 1;
	while(b) {
		if (b & 1) ret = 1LL * ret * a % mod; a = 1LL * a * a % mod;
		b >>= 1;
	}
	return ret;
}

int comb(int n, int k) {
	if (n < k || k < 0 || n < 0) return 0;
	return 1LL * fact[n] * (1LL * ifact[k] * ifact[n - k] % mod) % mod;
}

void add(int &x, int y) {
	x += y; while(x >= mod) x -= mod;
}

void sub(int &x, int y) {
	x -= y; while(x < 0) x += mod;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	--m;

	fact[0] = 1; for (int i = 1; i < N; ++i) fact[i] = 1LL * fact[i - 1] * i % mod;
	ifact[0] = 1; for (int i = 1; i < N; ++i) ifact[i] = binpow(fact[i], mod - 2) % mod;

	// Eulerian number
	
	int res = 0;
	for (int k = 0; k <= m + 1; ++k) {
		int cur = 1LL * comb(n + 1, k) * binpow(m + 1 - k, n) % mod;
		if (k % 2 == 0) add(res, cur);
		else sub(res, cur);
	}

	printf("%d\n", res);
}