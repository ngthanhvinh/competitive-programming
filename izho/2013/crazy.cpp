#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n;
bool taken[N];
int a[N];
int who[N];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	int cnt = 0;
	int seat = 0;
	for (int crazy = 1; crazy <= n; ++crazy) {
		who[1] = crazy;
		for (int i = 2, cur = 1; i <= n; ++i, ++cur) {
			if (cur == crazy) ++cur;
			who[i] = cur;
		}

		for (int i = 1; i <= n; ++i) taken[i] = false;

		taken[a[1]] = true;

		bool ok = true;
		for (int i = 2; i <= n; ++i) {
			if (taken[who[i]]) {
				if (taken[a[i]]) ok = false;
				taken[a[i]] = true;
			} else {
				if (a[i] != who[i]) ok = false;
				taken[who[i]] = true;
			}
		}

		if (ok) {
			++cnt;
			seat = crazy;
		}
	}

	printf("%d\n", (cnt == 1) ? seat : 0);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt;
	cin >> tt;
	while(tt--) {
		solve();
	}
}