#include <iostream>
#include <cstdio>
using namespace std;

const int N = 1010, INF = 1e9;

int n, m;
int f[N][N][2], a[N][N];

void mnm(int &a, int b) { if (a>b) a = b; }

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> a[i][j];
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) f[i][j][0] = f[i][j][1] = INF;
    for (int i = 0; i <= n; ++i) f[i][0][0] = 0; for (int i = 0; i <= m; ++i) f[0][i][1] = 0;

    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        if (i > 0) {
            mnm(f[i][j][0], f[i-1][j][0]); if (j > 0) mnm(f[i][j][0], f[i-1][j][1] + a[i][j]);
        }
        if (j > 0) {
            mnm(f[i][j][1], f[i][j-1][1]); if (i > 0) mnm(f[i][j][1], f[i][j-1][0] + a[i][j]);
        }
    }
    cout << min(f[n][m][0], f[n][m][1]) << endl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--)
        solve();
}
