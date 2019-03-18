#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int N = 210;

int n;
int x[N], y[N], p[N];
int d[N];
vector <int> G[N];
int ans;

long long dist(int i, int j) { return 1ll * (x[i] - x[j]) * (x[i] - x[j]) + 1ll * (y[i] - y[j]) * (y[i] - y[j]); }

bool ok(int i, int j) { return dist(i, j) <= 1ll * p[i] * p[i]; }

void bfs(int s) {
    for (int i = 1; i <= n; ++i) d[i] = 0;
    queue <int> q; q.push(s); d[s] = 1; int cnt = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < G[u].size(); ++i) {
            int v = G[u][i]; if (d[v]) continue;
            q.push(v); d[v] = 1; ++cnt;
        }
    }
    ans = max(ans, cnt);
}

int main() {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n; for (int i = 1; i <= n; ++i) cin >> x[i] >> y[i] >> p[i];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) if (i != j && ok(i, j)) G[i].push_back(j);
    }
    for (int i = 1; i <= n; ++i) bfs(i);
    cout << ans << endl;
}
