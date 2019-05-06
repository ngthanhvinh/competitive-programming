#include <bits/stdc++.h>
using namespace std;

const char ch[] = {'R', 'P', 'S'};

void solve() {
	int n;
	cin >> n;
	vector <string> s(n);
	for (int i = 0; i < n; ++i) {
		string t; cin >> t;
		for (int j = 0; j < 500; ++j) {
			s[i] += t[j % (int)t.size()];
		}
	}

	string res = "";
	for (int j = 0; j < 500; ++j) {
		n = s.size();
		if (n == 0) break;

		map <char, int> cnt;
		for (int i = 0; i < n; ++i) {
			cnt[s[i][j]]++;
		}

		if (cnt.size() >= 3) {
			cout << "IMPOSSIBLE\n";
			return;
		}

		if (cnt.size() == 2) {
			for (int win = 0; win < 3; ++win) {
				int lose = (win + 2) % 3;
				if (cnt[ch[win]] && cnt[ch[lose]]) {
					res += ch[win];
					vector <string> ss;
					for (int i = 0; i < n; ++i) {
						if (s[i][j] == ch[win]) {
							ss.push_back(s[i]);
						}
					}
					s = ss;
				}
			}
		}

		if (cnt.size() == 1) {
			for (int lose = 0; lose < 3; ++lose) if (cnt[ch[lose]]) {
				int win = (lose + 1) % 3;
				res += ch[win];
			}
			break;
		}
	}

	cout << res << endl;
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