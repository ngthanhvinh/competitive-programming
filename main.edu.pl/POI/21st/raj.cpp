#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
const int inf = 1e9;

int n, m;
int pos[N];
vector<int> G[N], GG[N], R[N];
bool vis[N];
vector<int> topo;
int l[N], r[N], mxL[N], mxR[N];
int res[N];
vector<int> segL[N], segR[N];
multiset<int> s;

void del(int val) {
	multiset<int>::iterator iter = s.find(val);
	s.erase(iter);
}

void dfs(int u) {
	vis[u] = 1;
	for (int v : GG[u]) if (!vis[v]) dfs(v);
	topo.push_back(u);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	while(m--) {
		int u, v; cin >> u >> v;
		GG[u].push_back(v);
	}
	for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i);
	reverse(topo.begin(), topo.end());
	for (int i = 0; i < (int)topo.size(); ++i) pos[topo[i]] = i + 1;

	for (int i = 1; i <= n; ++i) {
		int u = pos[i];
		for (int j : GG[i]) {
			int v = pos[j];
			G[u].push_back(v); R[v].push_back(u); 
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j : R[i]) l[i] = max(l[i], l[j] + 1);
		mxL[i] = max(mxL[i - 1], l[i]);
	}
	for (int i = n; i >= 1; --i) {
		for (int j : G[i]) r[i] = max(r[i], r[j] + 1);
		mxR[i] = max(mxR[i + 1], r[i]);
	}

	for (int i = 1; i <= n; ++i) {
		for (int j : G[i]) {
			segL[i].push_back(l[i] + 1 + r[j]);
			segR[j].push_back(l[i] + 1 + r[j]);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int val : segR[i]) del(val);
		res[i] = max(mxL[i - 1], mxR[i + 1]);
		if (!s.empty()) {
			multiset<int>::iterator it = s.end(); --it;
			res[i] = max(res[i], (*it));
		}
		for (int val : segL[i]) s.insert(val);
	}

	int ver = 1;
	for (int i = 1; i <= n; ++i) if (res[i] < res[ver]) ver = i;
	cout << topo[ver - 1] << ' ' << res[ver] << endl;
}