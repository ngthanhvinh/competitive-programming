#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int inf = 1e9 + 10;
typedef pair<int,int> ii;

int n, m;
vector<int> rev[N], len[N];
int d[N];

void solve() {
	for (int i = 1; i <= n; ++i) d[i] = inf;
	priority_queue < ii, vector<ii>, greater<ii> > pq;
	pq.push(ii(0, n));
	d[n] = 0;

	while(!pq.empty()) {
		ii top = pq.top(); pq.pop();
		int u = top.second, du = top.first;
		if (du != d[u]) continue;
		
		if (u == 1) {
			printf("%d\n", du); return;
		}

		for (int v : rev[u]) {
			if (!len[v].empty()) {
				int cur = len[v].back(); len[v].pop_back();
				if (d[v] > d[u] + cur) {
					d[v] = d[u] + cur; pq.push(ii(d[v], v));
				}
			}
		}
	}
}

int main() {
	cin >> n >> m;
	while(m--) {
		int u, v, w; cin >> u >> v >> w;
		rev[v].push_back(u);
		len[u].push_back(w);
	}
	for (int i = 1; i <= n; ++i) {
		sort(len[i].begin(), len[i].end());
	}

	solve();
}