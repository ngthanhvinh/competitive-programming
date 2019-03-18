#include <bits/stdc++.h>
using namespace std;
typedef vector <int> vi;
const int N = 51;

int n, m, mx[N], my[N];
vector <vi> G;
char E[N][N];
bool check[N], vx[N], vy[N];
int Case;
int v1, v2;

bool dfs(int u) {
    if (u == 0) return 1;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i]; if (check[v] || !vy[v]) continue;
        check[v] = 1;
        if (dfs(my[v])) { mx[u] = v; my[v] = u; return 1; }
    }
    return 0;
}

void solve() {
    cin >> n >> m; G.assign(n + 1, vi());
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        cin >> E[i][j];
        if (E[i][j] == '0') G[i].push_back(j);
    }
    int ans = 0;
    for (v1 = 1; v1 <= n; v1++) for (int v2 = 1; v2 <= m; v2++) if (E[v1][v2] == '1') {
        memset(mx, 0, sizeof mx); memset(my, 0, sizeof my);
        int x = 0, y = 0;
        for (int i = 1; i <= n; i++) if (E[i][v2] == '1') vx[i] = 1, x++; else vx[i] = 0;
        for (int i = 1; i <= m; i++) if (E[v1][i] == '1') vy[i] = 1, y++; else vy[i] = 0;
        vx[v1] = 0; vy[v2] = 0; x--; y--;
        int C = x, C_ = x + 1;
        while(C && C < C_) {
            C_ = C; memset(check, 0, sizeof check);
            for (int i = 1; i <= n; i++) if (vx[i] && !mx[i]) C -= dfs(i);
        }
        int cnt = 0;
        for (int i = 1; i <= n; i++) if (mx[i]) ++cnt;
        ans = max(ans, 2 + x + y - cnt);
    }
    printf("Case %d: %d\n", ++Case, ans);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    //freopen("scchem.inp", "r", stdin);
    //freopen("scchem.out", "w", stdout);
    int t; cin >> t;
    while(t--)
        solve();
}
