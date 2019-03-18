#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int n, m, a, b, k, h[N][N];
bool check[N][N];
long long ans = -1e18;
int main() {
    freopen("voland.inp", "r", stdin);
    freopen("voland.ans", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> a >> b >> k;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> h[i][j];

    for (int i1=1; i1<=n; ++i1) for (int j1=1; j1<=m; ++j1) for (int i2=1; i2<=n; ++i2) for (int j2=1; j2<=m; ++j2) {
        long long sum = 0; int cnt = 0; memset(check, 0, sizeof check);
        for (int i = i1; i <= min(n,i1+a-1); ++i) for (int j = j1; j <= min(m,j1+b-1); ++j) check[i][j] = 1, sum += h[i][j], ++cnt;
        for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) if (abs(i-i2) + abs(j-j2) <= k) {
            if (!check[i][j]) ++cnt;
            sum += h[i][j];
        }
        if (cnt == a * b + (k+1) * (k+1) + k * k) ans = max(ans, sum);
    }
    cout << ans << endl;
}
