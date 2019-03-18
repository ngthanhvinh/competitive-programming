#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n;
int par[N], ver[N], edge[N];
int cnt;

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) {
	edge[q] += edge[p]; edge[q]++; edge[p] = 0;
	ver[q] += ver[p]; ver[p] = 0;
	par[p] = q;
} 

int main() {
	// number of rooms: n + 1
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n + 1; ++i) par[i] = i, ver[i] = 1, edge[i] = 0;
	for (int i = 1; i <= n; ++i) {
		int u, v; cin >> u >> v;
		u = anc(u), v = anc(v);
		if (u == v) ++edge[u];
		else join(u, v);
	}

	for (int i = 1; i <= n + 1; ++i) if (i == anc(i)) {
		if (edge[i] > ver[i]) return printf("0\n"), 0;
		if (edge[i] < ver[i]) cnt += ver[i];
	}

	printf("%lld\n", 1LL * cnt * (cnt - 1) / 2 + 1LL * cnt * (n + 1 - cnt));
}