#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MX = 210, INF =  1e9;

int N, P, C[MX];
vector <int> G[MX];
int f[MX][MX];
int g[MX][MX];

void dfs(int u, int p) {
    f[u][1] = C[u]; f[u][0] = 0;
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i]; if (v == p) continue;
        dfs(v, u);
        for (int j = 0; j <= P; ++j) g[u][j] = f[u][j], f[u][j] = -INF;
        for (int j = 1; j <= P; ++j) {
            for (int k = 1; k <= j; ++k) f[u][j] = max(f[u][j], g[u][k] + f[v][j - k]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> P;
    for (int i = 1; i <= N; ++i) cin >> C[i];
    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }

    for (int i = 1; i <= N; ++i) for (int j = 0; j <= P; ++j) f[i][j] = -INF;

    dfs(1, 1);

    int ans = -INF;
    for (int i = 1; i <= N; ++i) ans = max(ans, f[i][P]);
    cout << ans << endl;
}
