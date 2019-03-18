#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int n, m;
char a[N][N];
int x, y, k;

const int dx[] = {0,0,1,-1}, dy[] = {-1,1,0,0};

int main() {
    freopen("rbull.inp", "r", stdin);
    freopen("rbull.ans", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> a[i][j];
    int ress = 0, resx = 1, resy = 1, resk = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        int kmax = 0, res = 0;
        for (int k = 0; k <= min(min(i-1,j-1), min(n-i, m-j)); ++k) {
            bool ok = 1; int ans = 0;
            for (int x = 1; x <= n; ++x) for (int y = 1; y <= m; ++y) if (abs(x-i) + abs(y-j) <= k && a[x][y] == '*') {
                for (int t = 0; t < 4; ++t) {
                    int X = x + dx[t], Y = y + dy[t];
                    if (X >= 1 && X <= n && Y >= 1 && Y <= m && abs(X-i) + abs(Y-j) <= k && a[X][Y] == '*') ok = 0;
                }
                if (!ok) break;
                ++ans;
            }
            if (ok) kmax = max(kmax, k), res = max(res, ans);
        }
        if (i == 58 && j == 102) cerr << res << endl;
        if (ress < res) ress = res, resx = i, resy = j, resk = kmax;
    }
    cout << ress << ' ' << resx << ' ' << resy << ' ' << resk << endl;
}
