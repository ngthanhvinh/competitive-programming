#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

struct Query {
    char type;
    int u;
} query[N];

int n, q, dep[N], par[N][18];
vector<int> g[N];
bool is_root[N];
int root[N];
int best_u[N], best_v[N], best_dist[N];

void dfs(int u, int r) {
    root[u] = r;
    for (int &v : g[u]) {
        dep[v] = dep[u] + 1;
        par[v][0] = u;
        dfs(v, r);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 17; i >= 0; --i) if (dep[par[u][i]] >= dep[v]) u = par[u][i];
    for (int i = 17; i >= 0; --i) if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
    return u == v ? u : par[u][0];
}

int dist(int u, int v) {
    int x = lca(u, v);
    return dep[u] + dep[v] - dep[x] - dep[x];
}

int main() {
    freopen("newbarn.in", "r", stdin);
    freopen("newbarn.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> query[i].type >> query[i].u;
    }

    for (int i = 0; i < q; ++i) {
        if (query[i].type == 'B') {
            ++n;
            if (query[i].u != -1) g[query[i].u].push_back(n);
            else is_root[n] = true;
        }
    }

    for (int i = 1; i <= n; ++i) if (is_root[i]) {
        par[i][0] = i;
        dfs(i, i);
        best_u[i] = i;
        best_v[i] = i;
        best_dist[i] = 0;
    }
    for (int j = 1; j <= 17; ++j) {
        for (int i = 1; i <= n; ++i) par[i][j] = par[par[i][j - 1]][j - 1];
    }

    int cur = 0;
    for (int i = 0; i < q; ++i) {
        if (query[i].type == 'B') {
            ++cur;
            if (query[i].u == -1) continue;
            
            int r = root[cur];
            if (dist(best_u[r], cur) > best_dist[r]) {
                best_dist[r] = dist(best_u[r], cur);
                best_v[r] = cur;    
            } else if (dist(best_v[r], cur) > best_dist[r]) {
                best_dist[r] = dist(best_v[r], cur);
                best_u[r] = cur;    
            }

            //printf("best_u = %d best_v = %d\n", best_u, best_v);
        }

        else { // 'Q'
            int u = query[i].u;
            int r = root[u];
            printf("%d\n", max(dist(best_u[r], u), dist(best_v[r], u)));
        }
    }
}