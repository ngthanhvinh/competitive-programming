#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int N = 250010;

int n, m, par[N], d[N], st[N], en[N], step;
vector<int> G[N];

void dfs(int u) {
    st[u] = ++step;
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i]; if (v == par[u]) continue;
        par[v] = u; d[v] = d[u] + 1; dfs(v);
    }
    en[u] = step;
}

// BIT
int t[N];
void upd(int x, int v) { for (; x <= n; x += x & -x) t[x] += v; }
int get(int x) { int r = 0; for (; x > 0; x -= x & -x) r += t[x]; return r; }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }
    dfs(1);
    cin >> m; m += n-1;
    while(m--) {
        char tp; int u, v; cin >> tp;
        if (tp == 'W') {
            cin >> u; printf("%d\n", d[u] - get(st[u]));
        }
        else {
            cin >> u >> v; if (u == par[v]) swap(u,v);
            upd(st[u], 1); upd(en[u]+1, -1);
        }
    }
}
