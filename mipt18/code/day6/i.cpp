#include <bits/stdc++.h>
using namespace std;

const int N = 45;

int n, m, a[N], t[N];
bool e[N][N];
int to_v1[N], to_v2[N], adjmask[1 << 25], sxor[1 << 25];
long long cnt[1 << 15][64], f[1 << 15];
int g[40005];

int calc_grundy(int u) { // <= 40
	g[0] = 0;
	for (int val = 1; val <= t[u]; ++val) {
		bitset <50> bs;
		for (int v = 1; v <= n; ++v) if (e[u][v]) {
			bs[g[max(0, val - t[v])]] = 1;
		}
		g[val] = 0;
		while(bs[g[val]]) ++g[val];
	}
	return g[t[u]];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> t[i];

	cin >> m;
	while(m--) {
		int u, v; cin >> u >> v;
		e[u][v] = e[v][u] = 1;
	}

	for (int i = 1; i <= n; ++i) {
		a[i] = calc_grundy(i);
	}

	// MEET IN THE MIDDLE
	int n1 = min(25, n), n2 = n - n1;
	vector <int> v1, v2;
	for (int i = 1; i <= n1; ++i) v1.push_back(i);
	for (int i = n1 + 1; i <= n; ++i) v2.push_back(i);

	/* prepare for {v1} */
	// create the mask corresponding to adjacent lists to v2 of vertices in v1
	for (int i = 0; i < n1; ++i) {
		for (int j = 0; j < n2; ++j) {
			if (e[v1[i]][v2[j]]) {
				to_v2[i] |= (1 << j);
			}
		}
		for (int j = 0; j < n1; ++j) {
			if (e[v1[i]][v1[j]]) {
				to_v1[i] |= (1 << j);
			}
		}
	}
	// adjacent list and xor of grundy of a set
	for (int mask = 1; mask < (1 << n1); ++mask) {
		int prv = mask & -mask;
		int k = (int)log2(prv);
		if (adjmask[mask ^ prv] == -1 || (to_v1[k] & mask)) {
			adjmask[mask] = -1; // invalid
			continue;
		}
		adjmask[mask] = adjmask[mask ^ prv] | to_v2[k];
		sxor[mask] = sxor[mask ^ prv] ^ a[v1[k]];
	}

	/* prepare for {v2} */
	for (int mask = 0; mask < (1 << n2); ++mask) {
		// whether {mask} is valid?
		bool invalid = false;
		for (int i = 0; i < n2; ++i) {
			for (int j = 0; j < n2; ++j) {
				if ((mask >> i & 1) && (mask >> j & 1) && e[v2[i]][v2[j]]) invalid = true;
			}
		}
		if (invalid) continue;
		int curxor = 0;
		for (int i = 0; i < n2; ++i) if (mask >> i & 1) curxor ^= a[v2[i]];
		cnt[mask][curxor]++;
	}
	// sum over subset
	for (int i = 0; i < n2; ++i) {
		for (int mask = 0; mask < (1 << n2); ++mask) {
			if (mask >> i & 1) {
				for (int j = 0; j < 64; ++j) {
					cnt[mask][j] += cnt[mask ^ (1 << i)][j];
				}
			}
		}
	}
	for (int mask = 0; mask < (1 << n2); ++mask) {
		for (int j = 0; j < 64; ++j) f[mask] += cnt[mask][j];
	}

	// solve
	long long res1 = 0, res2 = 0;
	for (int mask1 = 0; mask1 < (1 << n1); ++mask1) if (adjmask[mask1] != -1) { // valid mask1
		int mask2 = ((1 << n2) - 1) ^ (adjmask[mask1]);
		res1 += f[mask2] - cnt[mask2][sxor[mask1]]; // xor != 0
		res2 += cnt[mask2][sxor[mask1]]; // xor = 0
	}

	printf("%lld\n%lld\n", res1, res2);
}