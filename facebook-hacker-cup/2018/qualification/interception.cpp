#include <bits/stdc++.h>
using namespace std;

int n, p[55];

void solve() {
	cin >> n;
	for (int i = 0; i <= n; ++i) cin >> p[i];
	
	// check if x = 0 is an interception?
	int cur = 0;
	for (int i = 0; i <= n; ++i) {
		if (cur == 0) cur = 1;
		else cur = 0;
	}

	if (cur == 0) {
		cout << 1 << endl << 0 << endl;
	} else {
		cout << 0 << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
}