#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
const int N = 200005;

int n, m;
vector <int> g[N];
map <int, bool> e[N];
int deg[N];
bool del[N];

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		g[i].clear();
		e[i].clear();
		del[i] = false;
		deg[i] = 0;
	}
	while(m--) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
		deg[u]++;
		deg[v]++;
		e[u][v] = e[v][u] = true;
	}

	priority_queue < ii, vector<ii>, greater<ii> > pq;
	for (int i = 1; i <= n; ++i) {
		pq.push(ii(deg[i], i));
	}

	int res = n;
	while(!pq.empty()) {
		ii top = pq.top(); pq.pop();
		int u = top.second;
		if (del[u]) continue;

		if (deg[u] == 2) {
			int x = -1, y = -1;
			for (int &v : g[u]) if (!del[v]) {
				if (x == -1) x = v;
				else y = v;
			}
			if (e[x][y]) {
				--res;
				del[u] = true;
				for (int &v : g[u]) if (!del[v]) {
					--deg[v];
					pq.push(ii(deg[v], v));
				}
			}
		}
	}

	printf("%d\n", res);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int ntest; cin >> ntest;
	for (int itest = 1; itest <= ntest; ++itest) {
		printf("Case #%d\n", itest);
		solve();
	}
}