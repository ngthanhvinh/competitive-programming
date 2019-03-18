#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 2010, OFFSET = 1000;
const long long INF = 1e18;

int n, m, a, b, k;
int h[N][N], tmp[N][N];

long long rect[N][N];
long long diamond[N][N];
long long ans = -INF;

void prep() {
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) tmp[i-j+OFFSET][i+j] = h[i][j];
    for (int i = 1; i < N; ++i) for (int j = 1; j < N; ++j)
        rect[i][j] = rect[i-1][j] + rect[i][j-1] - rect[i-1][j-1] + h[i][j],
        diamond[i][j] = diamond[i-1][j] + diamond[i][j-1] - diamond[i-1][j-1] + tmp[i][j];
}

long long calRect(int x, int y) {
    if (x-a < 0 || y-b < 0) return -INF;
    return rect[x][y] - rect[x-a][y] - rect[x][y-b] + rect[x-a][y-b];
}

long long calDiamond(int x, int y) {
    if (y + k > m || y - k <= 0 || x + 2 * k > n) return -INF;
    x += 2 * k;
    int kk = 2 * k + 1, xx = x-y+OFFSET, yy = x+y;
    if (xx < kk || yy < kk) return -INF;
    return diamond[xx][yy] - diamond[xx-kk][yy] - diamond[xx][yy-kk] + diamond[xx-kk][yy-kk];
}

void do_rotate() {
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) tmp[j][n+1-i] = h[i][j];
    swap(n, m); swap(a, b);
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) h[i][j] = tmp[i][j];
}

long long U[N], D[N];
void solve1() {
    U[0] = -INF;
    for (int i = 1; i <= n; ++i) {
        U[i] = U[i-1];
        for (int j = 1; j <= m; ++j) U[i] = max(U[i], calRect(i,j));
    }
    D[n+1] = -INF;
    for (int i = n; i >= 1; --i) {
        D[i] = D[i+1];
        for (int j = 1; j <= m; ++j) D[i] = max(D[i], calDiamond(i,j));
    }
    for (int i = 0; i < n; ++i) ans = max(ans, U[i] + D[i+1]);
}

void solve2() {
    U[1] = -INF;
    for (int d = 2; d <= n+m; ++d) {
        U[d] = U[d-1];
        for (int i = 1; i <= n; ++i) if (d-i >= 1 && d-i <= m) U[d] = max(U[d], calRect(i,d-i));
    }
    D[n+m+1] = -INF;
    for (int d = n+m; d >= 2; --d) {
        D[d] = D[d+1];
        for (int i = 1; i <= n; ++i) if (d-i >= 1 && d-i <= m) D[d] = max(D[d], calDiamond(i,d-i));
    }
    for (int d = 1; d < n+m; ++d) ans = max(ans, U[d] + D[d+1]);
}

void solve() {
    prep();
    solve1();
    solve2();
}

int main() {
    freopen("voland.inp", "r", stdin);
    freopen("voland.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> a >> b >> k;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> h[i][j];
    solve();
    do_rotate(); solve();
    do_rotate(); solve();
    do_rotate(); solve();

    if (ans > -1e15) cout << ans << endl;
    else cout << "no solution" << endl;
}
