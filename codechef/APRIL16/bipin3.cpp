#include <bits/stdc++.h>
using namespace std;

int n, k;
const int mod = (int)1e9 + 7;

int pw(int a, int b) {
	int res = 1;
	for (int i = 0; (1LL << i) <= b; i++) {
		if (b & (1LL << i)) res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> k;
		int res = (1LL * k * pw(k-1, n-1)) % mod;
		cout << res << endl;
	}
}