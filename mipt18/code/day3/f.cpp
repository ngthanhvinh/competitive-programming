#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
const int BASE = 510;
const int mod = 998244353;

int n;
string s;
int h[2][N];
int pw[N];
bool foldable[N];
int fl[N];
int fr[N];

int get_hash(int id, int l, int r) {
	int ret;
	if (id == 0) {
		ret = h[0][r] - 1LL * h[0][l - 1] * pw[r - l + 1] % mod;
	} else {
		ret = h[1][l] - 1LL * h[1][r + 1] * pw[r - l + 1] % mod;
	}
	return ret < 0 ? (ret + mod) : ret;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> s;
	n = s.size();
	s = ' ' + s;

	pw[0] = 1;
	for (int i = 1; i <= n; ++i) {
		pw[i] = 1LL * pw[i - 1] * BASE % mod;
	}
	for (int i = 1; i <= n; ++i) {
		h[0][i] = (1LL * h[0][i - 1] * BASE + s[i]) % mod;
	}
	for (int i = n; i >= 1; --i) {
		h[1][i] = (1LL * h[1][i + 1] * BASE + s[i]) % mod;
	}

	long long res = 1;
	for (int i = 1; i <= n - 1; ++i) {
		// is the ith-position foldable?
		int len = min(i, n - i);
		foldable[i] = get_hash(0, i - len + 1, i) == get_hash(1, i + 1, i + len);
		res += foldable[i];
	}

	for (int i = 1; i <= n - 1; ++i) {
		fl[i] = fl[i - 1] + foldable[i];
	}
	for (int i = n - 1; i >= 1; --i) {
		fr[i] = fr[i + 1] + foldable[i];
	}

	res += 1LL * fl[(n + 1) / 2 - 1] * fr[(n + 1) / 2];

	printf("%lld\n", res);
}