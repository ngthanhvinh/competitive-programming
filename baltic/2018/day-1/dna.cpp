#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, k, r;
int a[N];
int mn[N];
vector <int> vec[N];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> k >> r;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		vec[a[i]].push_back(i);
	}
	for (int i = 1; i <= r; ++i) {
		int x; cin >> x; cin >> mn[x];
	}

	multiset <int> ms;
	int res = 1e9;
	for (int i = 1; i <= n; ++i) {
		int x = a[i];
		int pos = lower_bound(vec[x].begin(), vec[x].end(), i) - vec[x].begin();
		if (mn[x] > 0 && pos >= mn[x] - 1) {
			int cur = pos - (mn[x] - 1);
			if (cur > 0) {
				ms.erase(ms.find(vec[x][cur - 1]));
			}
			ms.insert(vec[x][cur]);
		}

		if (ms.size() == r) {
			res = min(res, i - (*ms.begin()) + 1);
		}
	}

	if (res == 1e9) cout << "impossible\n";
	else cout << res << '\n';
}