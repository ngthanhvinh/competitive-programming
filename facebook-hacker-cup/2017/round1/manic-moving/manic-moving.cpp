#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

const int INF = 1e9;

int N, M, K;
int a[110][110];
int s[5010], d[5010];
int f[110][5010][3];
int ans;

struct data {
    int u; int i; int j;
    data(int u=0, int i=0, int j=0): u(u), i(i), j(j) {}
};
queue <data> q;

void bfs() {
    for (int i = 1; i <= N; ++i) for (int j = 0; j <= K; ++j) for (int k = 0; k < 3; ++k) f[i][j][k] = INF; ans = INF;
    f[1][0][0] = 0; q.push(data(1, 0, 0));
    while(!q.empty()) {
        data t = q.front(); q.pop();
        int u = t.u, i = t.i, j = t.j;
        if (i == K && j == 0) { ans = min(ans, f[u][i][j]); continue; }
        if (j == 0) {
            if (i < K && f[s[i+1]][i+1][1] > f[u][i][j] + a[u][s[i+1]]) f[s[i+1]][i+1][1] = f[u][i][j] + a[u][s[i+1]], q.push(data(s[i+1], i+1, 1));
        }
        else if (j == 2) {
            if (f[d[i-1]][i][1] > f[u][i][j] + a[u][d[i-1]]) f[d[i-1]][i][1] = f[u][i][j] + a[u][d[i-1]], q.push(data(d[i-1], i, 1));
        }
        else {
            if (f[d[i]][i][0] > f[u][i][j] + a[u][d[i]]) f[d[i]][i][0] = f[u][i][j] + a[u][d[i]], q.push(data(d[i], i, 0));
            if (i < K && f[s[i+1]][i+1][2] > f[u][i][j] + a[u][s[i+1]]) f[s[i+1]][i+1][2] = f[u][i][j] + a[u][s[i+1]], q.push(data(s[i+1], i+1, 2));
        }
    }
}

int nCase;
void solve() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) a[i][j] = (i == j ? 0 : INF);
    while(M--) {
        int u, v, w; cin >> u >> v >> w;
        a[u][v] = min(a[u][v], w); a[v][u] = min(a[v][u], w);
    }
    for (int i = 1; i <= K; ++i) cin >> s[i] >> d[i];

    for (int k = 1; k <= N; ++k) for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) a[i][j] = min(a[i][j], a[i][k] + a[k][j]);

    bfs();

    printf("Case #%d: %d\n", ++nCase, (ans == INF ? -1 : ans));
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while(T--) solve();
}
