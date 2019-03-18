#include <bits/stdc++.h>
using namespace std;

const int N = 205;

int n;
bool sold[N];
int cnt[N];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) sold[i] = false, cnt[i] = 0;

	for (int i = 0; i < n; ++i) {
		int k; cin >> k;
		vector <int> can;
		while(k--) {
			int x; 
			cin >> x; 
			if (sold[x]) continue;
			can.push_back(x);
			++cnt[x];
		}

		if (can.empty()) {
			cout << -1 << endl;
			continue;
		}

		int mincnt = 1e9;
		for (int &x : can) {
			mincnt = min(mincnt, cnt[x]);
		}

		for (int &x : can) if (cnt[x] == mincnt) {
			cout << x << endl;
			sold[x] = true;
			break;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;
	while(tt--) {
		solve();
	}
}