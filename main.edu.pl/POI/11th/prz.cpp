#include <bits/stdc++.h>
using namespace std;

const int N = 16;
const int inf = 1e9;

int n, W;
int t[N], w[N];
int totW[1 << N], totT[1 << N], f[1 << N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> W >> n;
	for(int i = 0; i < n; ++i) cin >> t[i] >> w[i];

	for(int mask = 1; mask < (1 << n); ++mask) {
		int prv = (mask & -mask);
		prv = (int)log2(prv);
		totW[mask] = totW[mask ^ (1 << prv)] + w[prv];
		totT[mask] = max(totT[mask ^ (1 << prv)], t[prv]);
	}
	
	for (int mask = 1; mask < (1 << n); ++mask) {
		f[mask] = inf;
		for (int smask = mask; smask > 0; smask = (mask & (smask - 1))) {
			if (totW[smask] <= W) {
				f[mask] = min(f[mask], f[mask ^ smask] + totT[smask]);
			}
		}
	}

	printf("%d\n", f[(1 << n) - 1]);
}