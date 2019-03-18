#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int MX = 50010;

int N, M, P;
vector <int> G[MX];
int mx[MX], my[MX];
bool check[MX];

bool dfs(int u) {
    if (!u) return 1;
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        if (!check[v]) {
            check[v] = 1;
            if (dfs(my[v])) { mx[u] = v; my[v] = u; return 1; }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> M >> P;
    while(P--) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
    }
    int C_ = N + 1, C = N;
    while(C && C < C_) {
        C_ = C;
        memset(check, 0, sizeof check);
        for (int i = 1; i <= N; ++i) if (!mx[i]) C -= dfs(i);
    }

    int ans = 0;
    for (int i = 1; i <= N; ++i) ans += (mx[i] != 0);

    cout << ans << endl;
}
