#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	for (int it = 1; it <= t; ++it) {
		string s; cin >> s;

		int cntB = 0;
		int cntDot = 0;
		for (int i = 0; i < s.size(); ++i) {
			cntB += s[i] == 'B';
			cntDot += s[i] == '.';
		}

		bool yes = true;
		if (cntDot == 0 || cntB == 0) {
			yes = false;
		}
		if (cntB == 1 && cntDot > 1) {
			yes = false;
		}

		cout << "Case #" << it << ": " << (yes ? "Y\n" : "N\n");
	}
}