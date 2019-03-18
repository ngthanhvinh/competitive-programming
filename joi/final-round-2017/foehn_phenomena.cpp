#include <bits/stdc++.h>
using namespace std;
 
const int N = 200005;
 
int n, q, S, T;
int a[N];
long long c[N];
long long ans;
 
long long calc(long long v) { if (v < 0) return 1LL * v * S; else return 1LL * v * T; }
 
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q >> S >> T;
	for (int i = 0; i <= n; ++i) cin >> a[i];
 
	for (int i = 0; i <= n - 1; ++i) {
		c[i] = a[i] - a[i+1];
		ans += calc(c[i]);
	}
 
	while(q--) {
		int l, r, X; cin >> l >> r >> X;
		if (l > 0) {
			ans -= calc(c[l - 1]);
			c[l - 1] -= X;
			ans += calc(c[l - 1]);
		}
		if (r < n) {
			ans -= calc(c[r]);
			c[r] += X;
			ans += calc(c[r]);
		}
		printf("%lld\n", ans);
	}
}