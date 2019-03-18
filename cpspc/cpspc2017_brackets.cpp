#include <bits/stdc++.h>
using namespace std;

const char ch[] = {'(', ')', '[', ']', '{', '}', '<', '>'};
typedef pair<int,int> ii;
typedef pair<long long, ii> II;

int id(char w) {
	for (int i = 0; i < 8; ++i) if (w == ch[i]) return i;
}

const int N = 210;
const long long inf = 2e18;

int n, m, s, t;
vector<int> G[N][8];
long long d[N][N];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cin >> n >> m >> s >> t;
  while(m--) {
  	int u, v; char w; cin >> u >> v >> w;
  	int id_w = id(w);
  	G[u][id_w].push_back(v);
  	G[v][id_w].push_back(u);
  }

  priority_queue < II, vector<II>, greater<II> > pq;
  for (int i = 1; i <= n; ++i) {
  	for (int j = 1; j <= n; ++j) if (i != j) d[i][j] = inf;
  	pq.push(II(0, ii(i, i)));
  }

  while(!pq.empty()) {
  	II top = pq.top(); pq.pop();
  	int x = top.second.first, y = top.second.second;
    long long dist = top.first;
  	if (dist != d[x][y]) continue;
  	if (x == s && y == t) return printf("%lld\n", dist), 0;

  	// {open}{brackets}{close}
  	for (int o = 0; o < 8; o += 2) { // open
  		int c = (o ^ 1);
  		for (int u : G[x][o]) {
  			for (int v : G[y][c]) {
  				if (d[u][v] > dist + 2) {
  					d[u][v] = dist + 2; pq.push(II(d[u][v], ii(u, v)));
  				}
  			}
  		}
  	}
  	// {brackets}{brackets}
  	for (int nw = 1; nw <= n; ++nw) {
  		if (d[x][nw] > dist + d[y][nw]) {
  			d[x][nw] = dist + d[y][nw], pq.push(II(d[x][nw], ii(x, nw)));
  		}
  		if (d[nw][y] > d[nw][x] + dist) {
  			d[nw][y] = d[nw][x] + dist, pq.push(II(d[nw][y], ii(nw, y)));
  		}
  	}
  }

  printf("-1\n");
}
