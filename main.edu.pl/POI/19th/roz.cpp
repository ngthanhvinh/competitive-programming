#include <bits/stdc++.h>
using namespace std;
#define ll long long

int mx;
ll f[101];
map <ll, int> F;
ll n;

int A(ll x) {
	int res = 0;
	for (int i = mx; i >= 1; i--) {
		if (x >= f[i]) x -= f[i], ++res;
	}
	return res;
}

int calc(ll x) {
	if (x == 0 || x == 1) return x;
	if (F.count(x)) return F[x];
	//cout << x << endl;
	int res = A(x), Max = 0;
	for (int i = mx; i >= 1; i--) {
		if (x >= f[i]) { res = min(res, 1 + calc(f[i + 1] - x)), res = min(res, 1 + calc(x - f[i])); break; }
	}
	return F[x] = res;
}

void solve() {
	cin >> n; 
	cout << calc(n) << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	f[0] = 0; f[1] = 1;
	mx = 1;
	while(f[mx] <= 4 * 1e17) mx++, f[mx] = f[mx-1] + f[mx-2];
	int t; cin >> t;
	while(t--)
		solve();
}