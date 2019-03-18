#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
#define ll long long
ll H[N], R[N];
ll W, L;
int n;

bool f(ll x) {
	ll res = 0LL;
	for (int i = 1; i <= n; i++) {
		if (R[i] < (double)(L - H[i]) / x) continue;
		if (R[i] >= (double)(W - H[i]) / x) return 1;
		ll G = H[i] + R[i] * x;
		if (res >= W - G) return 1; res += G; 
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> W >> L;
	for (int i = 1; i <= n; i++) cin >> H[i] >> R[i];
	ll l = 0, r = 1e18;
	while(l != r) {
		ll mid = ((l + r) >> 1);
		if (f(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << endl;
}