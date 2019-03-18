#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const long long inf = 1e18;

int n, m;
long long dep[N], maxdep[N];
int nchild[N];
bool del[N];
vector< pair<int,int> > G[N];
long long ans;

void dfs(int u, int p) {
	nchild[u] = 1;
	maxdep[u] = 0;
	for (auto e : G[u]) if (e.second != p && !del[e.second]) {
		dep[e.second] = dep[u] + e.first;
		dfs(e.second, u);
		maxdep[u] = max(maxdep[u], maxdep[e.second] + e.first);
		nchild[u] += nchild[e.second];
	}
}

int findcen(int u, int p, int r) {
	for (auto e : G[u]) if (e.second != p && !del[e.second]) {
		if (nchild[e.second] * 2 >= nchild[r]) return findcen(e.second, u, r);
	}
	return u;
}

void upd(int u, int p, long long &mx) {
	ans = max(ans, maxdep[u] + dep[u] + mx + min(maxdep[u], dep[u] + mx));
	for (auto e : G[u]) if (e.second != p && !del[e.second]) {
		upd(e.second, u, mx);
	}
} 

void solve(int u) {
	dep[u] = 0; dfs(u, u);
	u = findcen(u, u, u); del[u] = 1;
	dep[u] = 0; dfs(u, u);

	vector<int> ch;
	vector<long long> val, L, R;
	for (auto e : G[u]) if (!del[e.second]) {
		ch.push_back(e.second), val.push_back(maxdep[e.second] + e.first);
	}

	L.assign(ch.size() + 2, 0); R.assign(ch.size() + 2, 0);
	for (int i = 1; i <= (int)val.size(); ++i) L[i] = max(L[i - 1], val[i - 1]);
	for (int i = (int)val.size(); i >= 1; --i) R[i] = max(R[i + 1], val[i - 1]);

	for (int i = 0; i < ch.size(); ++i) {
		int v = ch[i];
		long long mx = max(L[i], R[i + 2]);
		upd(v, u, mx);	
		ans = max(ans, val[i] + mx + min(val[i], mx));
	}

	// children
	for (int v : ch) solve(v);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v, w; cin >> u >> v >> w;
		G[u].push_back(make_pair(w, v));
		G[v].push_back(make_pair(w, u));
	}

	solve(1);

	cout << ans << endl;
}