#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
const int inf = 1e9 + 123;
typedef pair<int,int> ii;

int n, m;
vector<ii> G[N];
int d[N];
int ans = inf;

void dijkstra(int s, int t, int weight) {
	for (int i = 1; i <= n; ++i) d[i] = inf;
	d[s] = 0; 
	priority_queue < ii, vector<ii>, greater<ii> > q; q.push(ii(0, s));
	while(!q.empty()) {
		ii _top = q.top(); q.pop();
		int u = _top.second, du = _top.first;
		if (du != d[u]) continue;
		if (u == t) return;
		if (du + weight > ans) return;

		for (auto &edge : G[u]) {
			int v = edge.second, w = edge.first;
			if ((v == s && u == t) || (u == s && v == t)) continue;

			if (d[v] > du + w) {
				d[v] = du + w;
				q.push(ii(d[v], v));
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	while(m--) {
		int u, v, w1, w2; scanf("%d%d%d%d", &u, &v, &w1, &w2);
		G[u].push_back(make_pair(w1, v));
		G[v].push_back(make_pair(w2, u));
	}

	for (auto &edge : G[1]) {
		int u = edge.second, w = edge.first;
		dijkstra(u, 1, w);

		ans = min(ans, w + d[1]);
	}
	cout << ans << "\n";
}