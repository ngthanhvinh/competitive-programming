#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 500010;

int n, k, deg[N], h[N], root[N];
vector<int> G[N], R[N];
bool del[N], vis[N];

int par[N][20];
void dfs(int u, int r) {
    root[u] = r;
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i]; if (!del[v]) continue;
        h[v] = h[u] + 1; par[v][0] = u; vis[v] = 1; dfs(v, r);
    }
}

void prep() { for (int j = 1; j < 20; ++j) for (int i = 1; i <= n; ++i) par[i][j] = par[par[i][j-1]][j-1]; }
int lca(int u, int v) {
    if (h[u] < h[v]) swap(u,v);
    for (int i = 19; i >= 0; --i) if (h[par[u][i]] >= h[v]) u = par[u][i];
    for (int i = 19; i >= 0; --i) if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
    return u == v ? u : par[u][0];
}

vector<int> cycle[N];
int cntCycle;
int pos[N], pCycle[N];

void build(int u, int r) {
    vis[u] = 1; cycle[cntCycle].push_back(u); pos[u] = cycle[cntCycle].size(); pCycle[u] = cntCycle;
    for (int i = 0; i < R[u].size(); ++i) {
        int v = R[u][i]; if (del[v]) continue;
        if (v != r) build(v, r);
        else return;
    }
}

int dist(int u, int v) {
    int k = pCycle[u];
    if (pos[u] <= pos[v]) return pos[v] - pos[u];
    else return cycle[k].size() - pos[u] + pos[v];
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) { int x; scanf("%d", &x); deg[x]++; G[x].push_back(i); R[i].push_back(x); }
    queue<int> q;
    for (int i = 1; i <= n; ++i) if (!deg[i]) q.push(i);
    while(!q.empty()) {
        int u = q.front(); q.pop(); del[u] = 1;
        for (int i = 0; i < R[u].size(); ++i) {
            int v = R[u][i]; if (del[v]) continue;
            deg[v]--; if (!deg[v]) q.push(v);
        }
    }

    for (int i = 1; i <= n; ++i) if (deg[i]) par[i][0] = i, dfs(i, i);
    for (int i = 1; i <= n; ++i) if (!vis[i]) ++cntCycle, build(i, i);
    prep();

    for (int i = 1; i <= k; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        if (pCycle[root[u]] != pCycle[root[v]]) { printf("-1 -1\n"); continue; }
        int x = 0, y = 0;
        if (root[u] == root[v]) { int p = lca(u,v); x = h[u] - h[p]; y = h[v] - h[p]; }
        else {
            x = h[u], y = h[v]; u = root[u], v = root[v];
            /// case 1: u -> v
            int x1 = dist(u,v), y1 = 0;
            /// case 2: v -> u
            int x2 = 0, y2 = dist(v,u);
            int mx1 = max(x + x1, y + y1), mx2 = max(x + x2, y + y2);
            if (mx1 < mx2) x += x1, y += y1;
            else if (mx1 > mx2) x += x2, y += y2;
            else {
                int mn1 = min(x + x1, y + y1), mn2 = min(x + x2, y + y2);
                if (mn1 < mn2) x += x1, y += y1; else if (mn1 > mn2) x += x2, y += y2;
                else {
                    x += x1, y += y1;
                    if (!(x1 == x2 && y1 == y2)) {
                        if (x < y) swap(x, y);
                    }
                }
            }
        }
        printf("%d %d\n", x, y);
    }
}
