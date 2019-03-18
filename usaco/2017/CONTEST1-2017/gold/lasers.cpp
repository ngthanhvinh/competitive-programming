#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef pair<int, int> ii;
typedef pair<ii, int> II;
const int N = 1e5 + 15;

int n;
int x[N], y[N], dis[N][5];
vector<int> val;
vector<II> G[N][5];
vector<ii> xx[N * 4], yy[N * 4];

void bfs() {
    deque<ii> dq; for (int i = 0; i <= n + 1; ++i) for (int j = 0; j <= 3; ++j) dis[i][j] = 1e9;
    for (int i = 0; i <= 3; ++i) dq.push_back(ii(0, i)), dis[0][i] = 0;
    while (dq.size()) {
        ii u = dq.front(); dq.pop_front();
        for (int i = 0; i < G[u.fi][u.se].size(); ++i) {
            ii v = G[u.fi][u.se][i].fi; int dv = G[u.fi][u.se][i].se;
            if (dis[v.fi][v.se] > dis[u.fi][u.se] + dv) {
                dis[v.fi][v.se] = dis[u.fi][u.se] + dv;
                if (dv) dq.push_back(v); else dq.push_front(v);
            }
        }
    }
}

int main() {
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    cin >> x[0] >> y[0] >> x[n + 1] >> y[n + 1];
    for (int i = 1; i <= n; ++i) cin >> x[i] >> y[i];
    for (int i = 0; i <= n + 1; ++i) {
        val.push_back(x[i]); val.push_back(y[i]);
    }
    sort(val.begin(), val.end());
    val.resize(distance(val.begin(), unique(val.begin(), val.end())));
    for (int i = 0; i <= n + 1; ++i) {
        x[i] = lower_bound(val.begin(), val.end(), x[i]) - val.begin();
        y[i] = lower_bound(val.begin(), val.end(), y[i]) - val.begin();
        xx[x[i]].push_back(ii(y[i], i));
        yy[y[i]].push_back(ii(x[i], i));
    }
    // 0 up 1 down 2 left 3 right
    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= 1; ++j) for (int k = 2; k <= 3; ++k) {
            G[i][j].push_back(II(ii(i, k), 1));
            G[i][k].push_back(II(ii(i, j), 1));
        }
    }
    for (int i = 0; i < val.size(); ++i) {
        sort(xx[i].begin(), xx[i].end());
        sort(yy[i].begin(), yy[i].end());
        int xxn = xx[i].size(), yyn = yy[i].size();
        for (int j = 0; j < xxn - 1; ++j) {
            int p0 = xx[i][j].se, p1 = xx[i][j + 1].se;
            G[p0][0].push_back(II(ii(p1, 0), 0));
        }
        for (int j = 1; j < xxn; ++j) {
            int p0 = xx[i][j].se, p1 = xx[i][j - 1].se;
            G[p0][1].push_back(II(ii(p1, 1), 0));
        }
        for (int j = 0; j < yyn - 1; ++j) {
            int p0 = yy[i][j].se, p1 = yy[i][j + 1].se;
            G[p0][2].push_back(II(ii(p1, 2), 0));
        }
        for (int j = 1; j < yyn; ++j) {
            int p0 = yy[i][j].se, p1 = yy[i][j - 1].se;
            G[p0][3].push_back(II(ii(p1, 3), 0));
        }
    }
    bfs(); int mn = 1e9;
    for (int i = 0; i <= 3; ++i) mn = min(mn, dis[n + 1][i]);
    if (mn == 1e9) cout << -1;
    else cout << mn;
}
