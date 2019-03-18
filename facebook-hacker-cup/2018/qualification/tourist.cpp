#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n, k;
	long long ntour;
	cin >> n >> k >> ntour;
	--ntour;

	vector <string> name(n);
	for (int i = 0; i < n; ++i) {
		cin >> name[i];
	}

	int nloop = n / __gcd(k, n);
	ntour %= nloop;

	vector <pair <int, int> > a;
	for (int i = 0; i < n; ++i) a.push_back(make_pair(0, i));

	while(ntour--) {
		for (int i = 0; i < k; ++i) a[i].first++;
		sort(a.begin(), a.end());
	}

	vector <int> res;
	for (int i = 0; i < k; ++i) {
		res.push_back(a[i].second);
	}

	sort(res.begin(), res.end());
	for (auto &i : res) {
		cout << name[i] << ' ';
	}
	cout << endl;
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