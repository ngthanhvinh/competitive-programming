#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const long long INF = 1e18;
typedef pair<long long, int> li;

int n, m, S, T, U, V;
vector< pair<int,int> > G[N];
vector<int> dag[N];
long long disS[N], disU[N], disV[N];
long long minU[N], minV[N];
long long ans;
bool vis[N];
bool save[N];

void dijkstra(int start, long long d[]) {
    for (int i = 1; i <= n; ++i) d[i] = INF;
    d[start] = 0;
    priority_queue < li, vector<li>, greater<li> > pq;
    pq.push(li(0, start));

    while(!pq.empty()) {
        li top = pq.top(); pq.pop();
        int u = top.second; long long du = top.first;
        if (du != d[u]) continue;
        for (auto e : G[u]) {
            int v = e.second, w = e.first;
            if (d[v] > du + w) pq.push(li(d[v] = du + w, v));
        }
    }
}

bool dfs(int u) {
    if (vis[u]) return save[u]; 
    vis[u] = 1;
    minU[u] = disU[u];
    minV[u] = disV[u];
    if (u == T) return save[u] = true;

    bool res = false;
    for (int v : dag[u]) {
        bool cur = dfs(v);
        res |= cur;
        if (cur) {
            minU[u] = min(minU[u], minU[v]);
            minV[u] = min(minV[u], minV[v]);
        }
    }
    if (res) { // u is included in at least 1 path from S to T
        ans = min(ans, minU[u] + disV[u]);
        ans = min(ans, minV[u] + disU[u]);
    }
    return save[u] = res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> S >> T >> U >> V;
    while(m--) {
        int u, v, w; cin >> u >> v >> w;
        G[u].push_back(make_pair(w, v));
        G[v].push_back(make_pair(w, u));
    }
    dijkstra(S, disS);
    dijkstra(U, disU);
    dijkstra(V, disV);

    for (int i = 1; i <= n; ++i) {
        for (auto e : G[i]) if (disS[e.second] == disS[i] + e.first) {
            dag[i].push_back(e.second);
        }
    }

    ans = disU[V]; // original path from U to V
    dfs(S);
    cout << ans << endl;
}