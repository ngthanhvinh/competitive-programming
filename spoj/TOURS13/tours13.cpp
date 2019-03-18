#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 1010;
const long long INF = 1e18;
typedef pair <long long, int> T;
typedef pair <int, int> ii;

int n, m;
vector <ii> G[N];
vector <ii> R[N];
long long d[N];

void dijkstra(int s) {
    for (int i = 1; i <= n; ++i) d[i] = INF; d[s] = 0;
    priority_queue < T, vector<T>, greater<T> > q; q.push(T(0, s));
    while(!q.empty()) {
        T t = q.top(); q.pop();
        int u = t.second; long long du = t.first; if (du != d[u]) continue;
        for (int i = 0; i < G[u].size(); ++i) {
            int v = G[u][i].first, w = G[u][i].second;
            if (d[v] > d[u] + w) d[v] = d[u] + w, q.push(T(d[v],v));
        }
    }
}

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) G[i].clear(), R[i].clear();
    while(m--) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(ii(v, w));
        R[v].push_back(ii(u, w));
    }

    for (int i = 1; i <= n; ++i) {
        dijkstra(i);
        long long ans = INF;
        for (int j = 0; j < R[i].size(); ++j) {
            ans = min(ans, d[R[i][j].first] + R[i][j].second);
        }
        if (ans == INF) printf("-1\n");
        else printf("%lld\n", ans);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        solve();
}
