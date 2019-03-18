#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int n, m;
int ans;
char a[N][N];
char pattern[N][N];

int cost() {
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (a[i][j] == 'R' && pattern[i][j] == 'G') res += 5; // R -> G : 5
			if (a[i][j] == 'G' && pattern[i][j] == 'R') res += 3; // G -> R : 3
		}
	}
	return res;
}

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) cin >> a[i][j];
	}
	ans = 1e9; // inf
	// create patterns
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			pattern[i][j] = ((i + j) % 2 == 0 ? 'R' : 'G');
		}
	}
	ans = min(ans, cost());
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			pattern[i][j] = ((i + j) % 2 == 0 ? 'G' : 'R');
		}
	}
	ans = min(ans, cost());

	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	while(tt--) {
		solve();
	}
}