#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, m, q;
int a[N];
vector<int> G[N];
int dep[N], par[N][18];
set<int> v1[N], v2[N];

void dfs(int u) {
    for (int v : G[u]) if (v != par[u][0]) {
        par[v][0] = u;
        dep[v] = dep[u] + 1;
        dfs(v);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 17; i >= 0; --i) if (dep[par[u][i]] >= dep[v]) u = par[u][i];
    for (int i = 17; i >= 0; --i) if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
    return u == v ? u : par[u][0];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> q;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    par[1][0] = 1;
    dfs(1);
    for (int j = 1; j <= 17; ++j) {
        for (int i = 1; i <= n; ++i) par[i][j] = par[par[i][j - 1]][j - 1];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> a[i];
        v1[a[i]].insert(i);
    }
    for (int i = 1; i < m; ++i) {
        v2[lca(a[i], a[i + 1])].insert(i);
    }

    while(q--) {
        int type; cin >> type;
        if (type == 1) {
            int pos, u; cin >> pos >> u;

            v1[a[pos]].erase(pos);
            if (pos > 1) v2[lca(a[pos], a[pos - 1])].erase(pos - 1);
            if (pos < m) v2[lca(a[pos], a[pos + 1])].erase(pos);

            a[pos] = u;

            v1[a[pos]].insert(pos);
            if (pos > 1) v2[lca(a[pos], a[pos - 1])].insert(pos - 1);
            if (pos < m) v2[lca(a[pos], a[pos + 1])].insert(pos);
        } else {
            int l, r, u; cin >> l >> r >> u;
            set<int>::iterator it1 = v1[u].lower_bound(l);
            set<int>::iterator it2 = v2[u].lower_bound(l);

            int x = -1, y = -1;
            if (it1 != v1[u].end() && (*it1) <= r) x = (*it1), y = (*it1);
            if (it2 != v2[u].end() && (*it2) < r) x = (*it2), y = (*it2) + 1;

            printf("%d %d\n", x, y);
        }
    }
}