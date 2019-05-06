#include <bits/stdc++.h>
using namespace std;

int ask(int pos) {
	cout << pos << endl;
	char rep; cin >> rep;
	return (int)(rep - 'A');
}

int main() {
	ios_base::sync_with_stdio(false); 
	cin.tie(0);

	int tt, maxQueries; 
	cin >> tt >> maxQueries;

	while(tt--) {
		vector <int> can;
		for (int i = 0; i < 119; ++i) {
			can.push_back(i);
		}

		vector <int> res;
		vector <bool> forbidden(5, false);

		for (int pos = 0; pos < 5; ++pos) {
			if (can.empty()) break;
			vector <int> cnt(5, 0);
			vector <int> queries(can.size(), 0);

			for (int i = 0; i < can.size(); ++i) {
				int dig = ask(can[i] * 5 + pos + 1);
				cnt[dig]++;
				queries[i] = dig;
			}

			int mx = *max_element(cnt.begin(), cnt.end());
			for (int dig = 0; dig < 5; ++dig) if (!forbidden[dig] && cnt[dig] < mx) {
				res.push_back(dig);
				forbidden[dig] = true;
			}

			vector <int> newCan;
			for (int i = 0; i < can.size(); ++i) {
				if (queries[i] == res.back()) {
					newCan.push_back(can[i]);
				}
			}
			can = newCan;
		}

		for (int dig = 0; dig < 5; ++dig) if (!forbidden[dig]) {
			res.push_back(dig);
		}

		for (auto &i : res) cout << (char)(i + 'A'); cout << endl;

		char verdict; cin >> verdict;
		if (verdict != 'Y') {
			//assert(0);
			exit(0);
		}
	}
}