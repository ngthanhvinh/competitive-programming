#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 2010, OFFSET = 1000;
typedef pair<int,int> ii;

int n, m;
int a[N][N];

// START COMPUTING NUMBER OF STARS IN A DIAMOND
int b[N][N], sum[N][N];
void build() {
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) b[i - j + OFFSET][i + j] = a[i][j];
    for (int i = 1; i < N; ++i) for (int j = 1; j < N; ++j) sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + b[i][j];
}

int makeRes(int x, int y, int k) {
    int xx = x - y + OFFSET, yy = x + y;
    return sum[xx][yy] - sum[xx-k][yy] - sum[xx][yy-k] + sum[xx-k][yy-k];
}

int numStar(int x, int y, int k) {
    x = x + k;
    return makeRes(x, y, 2 * k + 1);
}

// END OF COMPUTING STARS IN A DIAMOND

int L[N][N], R[N][N], U[N][N], D[N][N];
int fl[N][N], fr[N][N], fu[N][N], fd[N][N], f[N][N];

int main() {
    //freopen("rbull.inp", "r", stdin);
    //freopen("rbull.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) { char c; cin >> c; a[i][j] = (c == '*'); }
    build();

    for (int i = 1; i <= n; ++i) L[i][0] = R[i][m+1] = -1;
    for (int j = 1; j <= m; ++j) U[0][j] = D[n+1][j] = -1;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) L[i][j] = (a[i][j] && a[i][j-1]) ? 0 : L[i][j-1] + 1;
    for (int i = 1; i <= n; ++i) for (int j = m; j >= 1; --j) R[i][j] = (a[i][j] && a[i][j+1]) ? 0 : R[i][j+1] + 1;
    for (int j = 1; j <= m; ++j) for (int i = 1; i <= n; ++i) U[i][j] = (a[i][j] && a[i-1][j]) ? 0 : U[i-1][j] + 1;
    for (int j = 1; j <= m; ++j) for (int i = n; i >= 1; --i) D[i][j] = (a[i][j] && a[i+1][j]) ? 0 : D[i+1][j] + 1;

    for (int j = 1; j <= m; ++j) fu[0][j] = fd[n+1][j] = 1e9;
    for (int i = 1; i <= n; ++i) fl[i][0] = fd[i][m+1] = 1e9;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) fu[i][j] = min( min(L[i][j], R[i][j]), fu[i-1][j] + 1 );
    for (int i = n; i >= 1; --i) for (int j = 1; j <= m; ++j) fd[i][j] = min( min(L[i][j], R[i][j]), fd[i+1][j] + 1 );
    for (int j = 1; j <= m; ++j) for (int i = 1; i <= n; ++i) fl[i][j] = min( min(U[i][j], D[i][j]), fl[i][j-1] + 1 );
    for (int j = m; j >= 1; --j) for (int i = 1; i <= n; ++i) fr[i][j] = min( min(U[i][j], D[i][j]), fr[i][j+1] + 1 );

    int ans = 0, x = 1, y = 1;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        f[i][j] = min( min(fl[i][j], fr[i][j]), min(fu[i][j], fd[i][j]) );
        int cur = numStar(i, j, f[i][j]);
        if (ans < cur) x = i, y = j, ans = cur;
    }
    printf("%d %d %d %d\n", ans, x, y, f[x][y]);
}
