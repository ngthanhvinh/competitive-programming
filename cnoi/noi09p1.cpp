// http://wcipeg.com/problem/noi09p1
// Day 1, Problem 1 - Transformed Sequence

#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

int n, deg[N], fr[N], to[N];
int min_id;
int res[N];
int par[N], cnt[N], nedge[N];
vector< pair<int,int> > G[N];
bool vis[N];
bool vis2[N];
vector<int> cyc;

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) {
	p = anc(p); q = anc(q);
	if (p != q) {
		par[p] = q; cnt[q] += cnt[p]; nedge[q] += nedge[p]; cnt[p] = 0; nedge[p] = 0;
	}
	nedge[q]++;
}

void find_cycle(int u) {
	vis[u] = 1;
	cyc.push_back(u);
	for (auto e : G[u]) {
		if (deg[e.second] != 1) {
			if (!vis[e.second]) { min_id = min(min_id, e.first); return find_cycle(e.second); }
		}
	}
	for (auto e : G[u]) {
		if (deg[e.second] != 1) min_id = min(min_id, e.first);
	}
}

void trace(int u) {
	vis[u] = 1;
	for (auto e : G[u]) {
		int v = e.second, id = e.first;
		if (!vis[v] && deg[v] != 1 && !vis2[e.first]) {
			res[id] = v;
			vis2[e.first] = 1;
			return trace(v);
		}
 	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) par[i] = i, cnt[i] = 1, res[i] = -1;
	for (int i = 0; i < n; ++i) {
		int d; cin >> d;
		int u = (i + d) % n;
		int v = (i - d + n) % n;
		fr[i] = u; to[i] = v;
		join(u, v);
		G[u].push_back(make_pair(i, v)); ++deg[u];
		G[v].push_back(make_pair(i, u)); ++deg[v];
	}

	for (int i = 0; i < n; ++i) if (anc(i) == i) {
		if (cnt[i] != nedge[i]) return cout << "No Answer\n", 0;
	}

	queue<int> que;
	for (int i = 0; i < n; ++i) if (deg[i] == 1) que.push(i);

	while(!que.empty()) {
		int u = que.front(); que.pop();
		for (auto e : G[u]) {
			int v = e.second, id = e.first;
			if (deg[v] == 1) continue;
			--deg[v]; res[id] = u;
			if (deg[v] == 1) {
				que.push(v);
			}
		}
	}

	for (int i = 0; i < n; ++i) if (!vis[i] && deg[i] != 1) { // in cycle
		cyc.clear();
		min_id = n;
		find_cycle(i);
		for (int v : cyc) vis[v] = 0;

		res[min_id] = min(fr[min_id], to[min_id]);

		vis2[min_id] = 1;
		trace(min(fr[min_id], to[min_id]));
	}

	for (int i = 0; i < n; ++i) {
		if (i == n - 1) cout << res[i];
		else cout << res[i] << ' ';
	}
}