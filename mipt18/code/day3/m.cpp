#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int N = 500005;

int n, a[N];
long long out[N];

int binpow(int a, int b) {
	int ret = 1;
	while(b) {
		if (b & 1) ret = 1LL * ret * a % mod; a = 1LL * a * a % mod;
		b >>= 1;
	}
	return ret;
}

long long calc(int l, int r) {
	return 1LL * (r - l - 1) * (a[l] + a[r]);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}

	vector <int> st;
	st.push_back(1);
	long long res = 2 * a[1];
	out[1] = res;

	for (int i = 2; i <= n; ++i) {
		while(st.size() >= 2) {
			long long c = calc(st[(int)st.size() - 2], i);
			long long c1 = calc(st[(int)st.size() - 2], st[(int)st.size() - 1]);
			long long c2 = calc(st[(int)st.size() - 1], i);
			if (c >= c1 + c2 + 2 * a[st[(int)st.size() - 1]]) {
				res -= c1;
				res -= 2 * a[st[(int)st.size() - 1]];
				st.pop_back();
			}
			else break;
		}

		res += calc(st.back(), i);
		res += 2 * a[i];
		st.push_back(i);

		out[i] = res;
	}

	// modulo
	int inv2 = binpow(2, mod - 2);
	for (int i = 1; i <= n; ++i) {
		out[i] %= mod;
		out[i] = out[i] * inv2 % mod; // / 2
		out[i] = out[i] * binpow(i, mod - 2) % mod; // / i
		printf("%lld ", out[i]);
	}
	printf("\n");
}