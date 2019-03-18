#include <iostream>
#include <cstdio>
using namespace std;

const int MOD = 1e9 + 9;
const int N = 1010;

int n, m, k;
int f[N][N][11];
int a[N], b[N];

int main() {
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int j = 1; j <= m; ++j) cin >> b[j];

    for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) f[i][j][0] = 1;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) for (int l = 1; l <= k; ++l) {
        f[i][j][l] = ((f[i-1][j][l] + f[i][j-1][l]) % MOD - f[i-1][j-1][l]) % MOD;
        if (l > 0 && a[i] > b[j]) f[i][j][l] = (f[i-1][j-1][l-1] + f[i][j][l]) % MOD;
        if (f[i][j][l] < 0) f[i][j][l] += MOD;
    }

    cout << f[n][m][k] << endl;
}
