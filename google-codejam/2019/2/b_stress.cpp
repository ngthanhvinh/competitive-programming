#include <bits/stdc++.h>
using namespace std;

int n, a[15], b[15];
long long val[15];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i] >> b[i];
	}

	for (int c = 1; c <= 300; ++c) {
		for (int j = 1; j <= 300; ++j) {
			for (int i = 1; i <= n; ++i) {
				val[i] = 1LL * c * a[i] + 1LL * j * b[i];
			}
			bool ok = true;
			for (int i = 2; i <= n; ++i) {
				if (val[i] <= val[i - 1]) {
					ok = false;
					break;
				}
			}
			if (ok) {
				cout << c << ' ' << j << endl;
				return;
			}
		}
	}

	cout << "IMPOSSIBLE\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		cout << "Case #" << it << ": ";
		solve();
	}
}