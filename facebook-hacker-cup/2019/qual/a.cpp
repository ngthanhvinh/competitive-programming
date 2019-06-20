#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;

	for (int itest = 1; itest <= t; ++itest) {
		string s; cin >> s;
		int cntB = 0;
		int cntDot = 0;
		for (int i = 0; i < s.size(); ++i) {
			cntB += s[i] == 'B';
			cntDot += s[i] == '.';
		}

		cout << "Case #" << itest << ": ";
		if (cntDot && cntB >= cntDot) {
			cout << "Y\n";
		} else {
			cout << "N\n";
		}
	}
}