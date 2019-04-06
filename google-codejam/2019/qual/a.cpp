#include <bits/stdc++.h>
using namespace std;

void solve() {
	string sn; cin >> sn;
	int sz = sn.size();

	string sa = sn, sb = sn;

	for (int i = sz - 1; i >= 0; --i) {
		if (sn[i] == '4') {
			sa[i] = '2';
			sb[i] = '2';
		} else {
			sa[i] = '0';
			sb[i] = sn[i];
		}
	}

	while(sa.size() >= 2 && sa[0] == '0') sa.erase(sa.begin());
	while(sb.size() >= 2 && sb[0] == '0') sb.erase(sb.begin());

	cout << sa << ' ' << sb << endl;
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