#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100010;
const long long INF = 1e18;
typedef pair<int,int> ii;
typedef pair<long long, int> T;

int n, m, a[N];
vector <ii> G[N];
vector <int> adj[N], rev[N];
long long d[N];
long long f[N];

void dijkstra() {
    priority_queue < T, vector<T>, greater<T> > q; for (int i = 1; i <= n; ++i) d[i] = INF; d[1] = 0; q.push(T(0, 1));
    while(!q.empty()) {
        T cur = q.top(); q.pop(); long long du = cur.first; int u = cur.second;
        if (du != d[u]) continue;
        for (int i = 0; i < G[u].size(); ++i) {
            int v = G[u][i].first, c = G[u][i].second;
            if (d[v] > du + c) d[v] = du + c, q.push(T(d[v], v));
        }
    }
}

vector <int> topo;
bool vis[N];
void dfs(int u) {
    vis[u] = 1;
    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i]; if (!vis[v]) dfs(v);
    }
    topo.push_back(u);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n; for (int i = 1; i <= n; ++i) cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, c; cin >> u >> v >> c;
        G[u].push_back(ii(v, c));
        G[v].push_back(ii(u, c));
    }
    dijkstra();
    if (d[n] == INF) return printf("impossible\n"), 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < G[i].size(); ++j) if (d[i] == d[G[i][j].first] - G[i][j].second) adj[i].push_back(G[i][j].first), rev[G[i][j].first].push_back(i);
    }

    dfs(1);
    reverse(topo.begin(), topo.end());

    for (int i = 0; i < topo.size(); ++i) {
        int u = topo[i];
        f[u] = a[u];
        for (int j = 0; j < (int)rev[u].size(); ++j) f[u] = max(f[u], f[rev[u][j]] + a[u]);
    }
    printf("%lld %lld\n", d[n], f[n]);
}
