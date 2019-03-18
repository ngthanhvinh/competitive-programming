#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n, a[N], p[N];

string solve() {
	cin >> n;
	a[n] = -1;
	for (int i = 0; i < n; ++i) cin >> a[i], --a[i], p[a[i]] = i;	
	string ans = "";
	for (int i = 0; i < n; ++i) ans += '.';
	ans[p[0]] = 'A';

	int cur = 0;
	for (int i = 1; i < n; ++i) {
		int x = p[i-1] + 1, y = p[i] + 1;
		if (a[x] < a[y]) ans[p[i]] = cur + 'A';
		else {
			++cur;
			if (cur == 26) return "-1";
			ans[p[i]] = 'A' + cur;
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		cout << "Case #" << i << ": " << solve() << endl;
	}
}