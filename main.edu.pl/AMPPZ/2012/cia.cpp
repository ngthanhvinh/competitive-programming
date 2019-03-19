#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
const int inf = 1e9 + 7;

int n, k, a[N], cost[N][2], f[N][2];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		cin >> a[i]; a[i] %= 2;
		cost[i % k][a[i]]++;
	}
	for (int i = 0; i <= k; ++i) for (int j = 0; j < 2; ++j) f[i][j] = inf;
	f[0][0] = 0;

	for (int i = 0; i < k; ++i) {
		for (int j = 0; j < 2; ++j) {
			f[i + 1][j] = min(f[i + 1][j], f[i][j] + cost[i][1]);
			f[i + 1][j] = min(f[i + 1][j], f[i][(j + 1) % 2] + cost[i][0]);
		}
	}
	cout << f[k][0] << endl;
}