#include <bits/stdc++.h>
using namespace std;

int n; string type;
long long ans;

void solve() {
	cin >> n >> type; ans = 0;
	while(n--) {
		string s; cin >> s;
		if (s == "CONTEST_WON") { int rank; cin >> rank; ans += 300 + max(20 - rank, 0); }
		else if (s == "BUG_FOUND") { int severity; cin >> severity; ans += severity; }
		else if (s == "CONTEST_HOSTED") ans += 50;
		else ans += 300;
	}
	cout << ans / ((type == "INDIAN") ? 200 : 400) << endl;
} 

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--) solve();
}