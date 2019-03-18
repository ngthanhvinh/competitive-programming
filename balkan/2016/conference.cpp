#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int n, m, k;
int a[N], b[N];
int par[N];
int found[N];
int latest[N];
int newest[N], fi[N];
bool check[N];

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) {
	p = anc(p), q = anc(q);
	if (found[p]) swap(p, q);
	par[p] = q; 
	found[p] = found[q];
	fi[p] = newest[q];
}

void upd(int x, int v) {
	x = anc(x), newest[x] = v;
}

void _join(int p, int q) {
	p = anc(p), q = anc(q);
	par[p] = q;
	found[q] = max(found[p], found[q]);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= k; ++i) par[i] = i;
	for (int i = 1; i <= m; ++i) cin >> a[i] >> b[i];
	for (int i = m; i >= 1; --i) {
		int u = a[i], v = b[i];
		if (u > k && v > k) continue;
		if (u > v) swap(u, v);

		if (v > k) {
			if (!found[u]) found[u] = 1, latest[u] = i, fi[u] = v; 
			upd(u, v);
		} else {
			if (!found[u] && !found[v]) continue;
			if (found[u] && found[v]) continue;
			if (found[u]) swap(u, v);
			latest[u] = i;
			join(u, v);
		}
	}

	for (int i = 1; i <= n; ++i) par[i] = i, found[i] = 0;
	for (int i = 1; i <= m; ++i) {
		int u = a[i], v = b[i];
		if (u > v) swap(u, v);
		if (latest[u] == i) found[anc(u)] = 1;
		if (latest[v] == i) found[anc(v)] = 1;
		if (!found[anc(u)] && !found[anc(v)]) continue;
		_join(u, v);
		if (u > k && found[anc(u)]) check[u] = 1;
		if (v > k && found[anc(v)]) check[v] = 1;
	}

	for (int i = 1; i <= k; ++i) printf("%d ", latest[i] ? latest[i] : -1); printf("\n");
	int cnt = 0; for (int i = k + 1; i <= n; ++i) if (check[i]) ++cnt;
	printf("%d ", cnt); for (int i = k + 1; i <= n; ++i) if (check[i]) printf("%d ", i); printf("\n");
	for (int i = 1; i <= k; ++i) printf("%d ", fi[i] ? fi[i] : -1); printf("\n");
}