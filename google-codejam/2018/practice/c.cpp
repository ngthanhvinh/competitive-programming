#include <bits/stdc++.h>
using namespace std;

const double INF = 2e18 + 123;

const int N = 1005;

int dest, n;
int k[N], s[N];

void solve() {
	cin >> dest >> n;
	for (int i = 1; i <= n; ++i) cin >> k[i] >> s[i];

	double v = INF;
	for (int i = 1; i <= n; ++i) {
		double mintime = (double)(dest - k[i]) / s[i];
		for (int j = 1; j <= n; ++j) {
			if (s[i] > s[j] && k[j] > k[i]) 
				mintime = min(mintime, (double)(k[j] - k[i]) / (s[i] - s[j]));
		}
		v = min(v, (double)k[i] / mintime + s[i]);
	}

	cout << setprecision(6) << fixed << v;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int itest = 1; itest <= tt; ++itest) {
		cout << "Case #" << itest << ": ";
		solve();
		cout << endl; 
	}
}