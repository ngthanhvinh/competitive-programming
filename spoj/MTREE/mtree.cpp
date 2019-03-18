#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int N = 100010, MOD = 1e9 + 7, REV = 5e8 + 4;
typedef pair <int, int> ii;

int n, f[N], g[N], ans;
vector <ii> G[N];

void dfs_down(int u, int p) {
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i].first, w = G[u][i].second; if (v == p) continue;
        dfs_down(v, u);
        int add = 1ll * f[v] * w % MOD, sqradd = 1ll * add * add % MOD;
        f[u] = (f[u] + add) % MOD;
        g[u] = (g[u] + add) % MOD;
        g[u] = (g[u] - 1ll * sqradd * REV) % MOD;
    }
    g[u] = (g[u] + 1ll * (1ll * f[u] * f[u] % MOD) * REV) % MOD;
    ans = (ans + g[u]) % MOD;
    f[u]++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v, w; cin >> u >> v >> w;
        G[u].push_back(ii(v, w));
        G[v].push_back(ii(u, w));
    }
    dfs_down(1, 1);
    if (ans < 0) ans += MOD;
    cout << ans << endl;
}
