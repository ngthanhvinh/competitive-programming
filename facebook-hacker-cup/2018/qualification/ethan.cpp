#include <bits/stdc++.h>
using namespace std;

bool contains(string &B, string &A) {
	int i = 0, j = 0;
	while(i < A.size() && j < B.size()) {
		if (A[i] == B[j]) {
			++i; ++j; continue;
		}
		if (i == 0) {
			++j; continue;
		}
		i = 0;
	}
	if (i >= A.size()) return true;
	else return false;
}

void solve() {
	string s;
	cin >> s;

	int n = s.size();
	for (int i = 1; i < n; ++i) {
		//if (s[i] == s[0]) {
			string pref = s.substr(0, i);
			string t = pref + s;
			if (!contains(t, s)) {
				cout << t << '\n';
				return;
			}
		//}
	}

	cout << "Impossible\n";
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