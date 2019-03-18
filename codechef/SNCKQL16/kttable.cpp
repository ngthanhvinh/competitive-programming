#include <bits/stdc++.h>
using namespace std;
int a[10010], b[10010];
int n;

void solve() {
	cin >> n; int ans = 0;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++) {
		//cout << b[i] << ' ' << a[i] << ' ' << a[i-1] << endl;
		if (b[i] <= a[i] - a[i-1]) ans++;
	}
	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--) solve();
}