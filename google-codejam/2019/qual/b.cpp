#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		cout << "Case #" << it << ": ";
		// solve
		int n; cin >> n;
		string s; cin >> s;
		string t = "";
		for (auto &c : s) {
			t += (c == 'S') ? 'E' : 'S';
		}

		cout << t << endl;
	}
}