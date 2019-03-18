#include <bits/stdc++.h>
using namespace std;
typedef vector <int> vi;
typedef pair<int, int> ii;
const int N = 50010;

int n, m, par[N], f[N][17], d[N], link[N], res;
vector <vi> G;
vector <ii> E;

void dfs(int u) {
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i]; if (v == f[u][0]) continue;
        f[v][0] = u; d[v] = d[u] + 1; dfs(v);
    }
}

int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    for (int i = 16; i >= 0; i--) if (d[f[u][i]] >= d[v]) u = f[u][i];
    for (int i = 16; i >= 0; i--) if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
    return u == v ? u : f[u][0];
}

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) { par[anc(p)] = anc(q); }

int cycle(int p) { return p == link[p] ? p : link[p] = cycle(link[p]); }

void solve() {
    scanf("%d%d", &n, &m); G.assign(n + 1, vi()); E.clear(); res = 0;
    // init
    for (int i = 1; i <= n; i++) par[i] = i;
    for (int i = 0; i < m; i++) {
        int u, v; scanf("%d%d", &u, &v); u++; v++;
        E.push_back(ii(u,v));
        if (anc(u) != anc(v)) join(u, v), G[u].push_back(v), G[v].push_back(u); // find bridges
    }
    // dfs
    for (int i = 1; i <= n; i++) f[i][0] = 0;
    for (int i = 1; i <= n; i++) if (!f[i][0]) f[i][0] = i, d[i] = 0, dfs(i);
    for (int j = 1; j < 17; j++) for (int i = 1; i <= n; i++) f[i][j] = f[f[i][j-1]][j-1];

    // solve
    for (int i = 1; i <= n; i++) par[i] = i, link[i] = i;
    for (int i = 0; i < m; i++) {
        int u = E[i].first, v = E[i].second;
        int x = anc(u), y = anc(v);
        if (x != y) join(u, v), res++;
        else {
            x = cycle(u), y = cycle(v);
            int k = cycle(lca(u,v));
            while(x != k) {
                int nxt = cycle(f[x][0]);
                link[x] = k;
                x = nxt; res--;
            }
            while(y != k) {
                int nxt = cycle(f[y][0]);
                link[y] = k;
                y = nxt; res--;
            }
        }
        printf("%d\n", res);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        solve();
}
/*
1
7 9
3 2
0 2
1 6
1 3
1 5
3 4
4 5
5 6
6 2
*/
