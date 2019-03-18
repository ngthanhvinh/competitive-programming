#include <bits/stdc++.h>
using namespace std;

const int N = 500005;
#define int long long 

int n, q;
int d[N];
int x;

int low[50], high[50], val[50], sz;

int calc(int l, int r, int val) {
	// [l...r] >= val
	if (val <= l) return r - l + 1;
	else return max(0LL, r - val + 1);
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> d[i];

	x = d[1];
	for (int i = 2; i <= n; ++i) {
		d[i] = max(d[i - 1], ((d[i] + d[1] - 1) / d[1]) * d[1]);
	}
	for (int i = 1; i <= n; ++i) d[i] /= x;

	for (int i = 2; i <= n; ++i) {
		d[i] = ((d[i] + d[i - 1] - 1) / d[i - 1]) * d[i - 1];
	}

	for (int i = 1; i <= n; ++i) {
		if (d[i] != d[i - 1]) {
			high[sz] = i - 1;
			++sz; 
			low[sz] = i; val[sz] = d[i];
		}
	}
	high[sz] = n;

	while(q--) {
		int t, l, r; cin >> t >> l >> r;
		int res = 0;
		if (t >= l && t <= r) ++res;
		t /= x;

		for (int i = 1; i <= sz; ++i) {
			int k = (t / val[i]) * val[i];
			// [-high + k * x ... -low + k * x]
			// [l ... r]
			res += calc(-high[i] + k * x, -low[i] + k * x, l) - calc(-high[i] + k * x, -low[i] + k * x, r + 1);
		}

		printf("%lld\n", res);
	}
}