// http://wcipeg.com/problem/noi07p1
// Day 1, Problem 1 - Social Network

#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const long long inf = 1e18;
typedef pair<long long, int> li;

int n, m;
vector< pair<int,int> > G[N];
long long d[N][N];
long long C[N][N];
double ans[N];

void dijkstra(int s) {
	for (int i = 1; i <= n; ++i) d[s][i] = inf;
	d[s][s] = 0; C[s][s] = 1;
	priority_queue < li, vector<li>, greater<li> > pq;
	pq.push(li(0, s));

	while(!pq.empty()) {
		li top = pq.top(); pq.pop();
		int u = top.second; long long du = top.first;
		if (du != d[s][u]) continue;

		for (auto e : G[u]) {
			int v = e.second, w = e.first;
			if (d[s][v] > du + w) {
				pq.push(li(d[s][v] = du + w, v));
				C[s][v] = C[s][u];
			} else if (d[s][v] == du + w) C[s][v] += C[s][u];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	while(m--) {
		int u, v, w; cin >> u >> v >> w;
		G[u].push_back(make_pair(w, v));
		G[v].push_back(make_pair(w, u));
	}

	for (int i = 1; i <= n; ++i) dijkstra(i);

	for (int s = 1; s <= n; ++s) {
		for (int t = 1; t <= n; ++t) {
			for (int i = 1; i <= n; ++i) if (i != s && i != t) {
				if (d[s][i] + d[t][i] == d[s][t]) {
					ans[i] += ((double)C[s][i] / C[s][t]) * C[t][i];
				}
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		cout << setprecision(3) << fixed << ans[i] << endl;
	}
}