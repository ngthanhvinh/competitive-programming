#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, m;
vector<int> G[N], queries[N];
int nchild[N], dep[N];
bool del[N];
long long ans[N];

long long sum[N]; int cnt[N];
vector<int> buf; // to reset

void dfs(int u, int p) {
	nchild[u] = 1;
	for (int v : G[u]) if (v != p && !del[v]) {
		dep[v] = dep[u] + 1;
		dfs(v, u);
		nchild[u] += nchild[v];
	}
}

int find_centroid(int u, int p, int r) {
	for (int v : G[u]) if (v != p && !del[v]) {
		if (nchild[v] * 2 >= nchild[r]) return find_centroid(v, u, r);
	}
	return u;
}

void upd(int u) {
	for (int p : queries[u]) {
		p = max(0, p - dep[u]);
		int h = min(n, p) + 1;
		sum[0] += p; sum[h] -= p;
		cnt[0]++; cnt[h]--;
		buf.push_back(h);
	}
}

void dfs_upd(int u, int p) {
	upd(u);
	for (int v : G[u]) if (v != p && !del[v]) {
		dfs_upd(v, u);
	}
}

void dfs_get(int u, int p, int &maxdep, int val) {
	if (dep[u] > maxdep) {
		maxdep = dep[u];
		cnt[maxdep] += cnt[maxdep - 1];
		sum[maxdep] += sum[maxdep - 1];
		buf.push_back(maxdep);
	}
	long long cur = sum[dep[u]] - 1LL * cnt[dep[u]] * dep[u];
	ans[u] += 1LL * val * cur;

	for (int v : G[u]) if (v != p && !del[v]) {
		dfs_get(v, u, maxdep, val);
	}
}

void reset() {
	sum[0] = cnt[0] = 0;
	while(buf.size()) sum[buf.back()] = 0, cnt[buf.back()] = 0, buf.pop_back();
}

void go(int u, int val) {
	int maxdep = 0;
	if (val == +1) upd(u);
	for (int v : G[u]) if (!del[v]) {
		dfs_upd(v, u);
		if (val == -1) {
			maxdep = 0;
			dfs_get(v, u, maxdep, -1);
			reset();
		}
	}
	if (val == +1) {
		dfs_get(u, u, maxdep, +1); reset();
	}
}

void solve(int u) {
	dep[u] = 0; dfs(u, u); 
	u = find_centroid(u, u, u); 
	dep[u] = 0; dfs(u, u);
	del[u] = true;

	go(u, +1);
	go(u, -1);

	for (int v : G[u]) if (!del[v]) solve(v);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 2; i <= n; ++i) {
		int p; cin >> p; 
		G[p].push_back(i); G[i].push_back(p);
	}
	while(m--) {
		int u, p; cin >> u >> p;
		queries[u].push_back(p);
	}

	solve(1);
	for (int i = 1; i <= n; ++i) printf("%lld\n", ans[i]);
}