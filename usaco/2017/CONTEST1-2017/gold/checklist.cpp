#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1010;
const long long INF = 1e18;

int h, g;
int x[2][N], y[2][N];

// 0: H
// 1: G

long long dist(int ci, int i, int cj, int j) {
    return 1ll * (x[ci][i]-x[cj][j]) * (x[ci][i]-x[cj][j]) + 1ll * (y[ci][i]-y[cj][j]) * (y[ci][i]-y[cj][j]);
}
long long f[N][N][2];
// f[H][G][H / G]

void mnm(long long &a, long long b) { if (a > b) a = b; }

int main() {
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> h >> g;
    for (int i = 1; i <= h; ++i) cin >> x[0][i] >> y[0][i];
    for (int i = 1; i <= g; ++i) cin >> x[1][i] >> y[1][i];

    for (int i = 0; i <= h; ++i) for (int j = 0; j <= g; ++j) for (int k = 0; k < 2; ++k) f[i][j][k] = INF;
    f[1][0][0] = 0;
    for (int i = 1; i <= h; ++i) for (int j = 0; j <= g; ++j) for (int k = 0; k < 2; ++k) {
        if (i == 1 && j == 0 && k == 0) continue;
        if (k == 0) {
            if (i >= 1) mnm(f[i][j][k], f[i-1][j][0] + dist(0, i-1, 0, i)), mnm(f[i][j][k], f[i-1][j][1] + dist(1, j, 0, i));
        }
        else {
            if (j >= 1) mnm(f[i][j][k], f[i][j-1][0] + dist(0, i, 1, j)), mnm(f[i][j][k], f[i][j-1][1] + dist(1, j-1, 1, j));
        }
        //cerr << i << ' ' << j << ' ' << k << ' ' << f[i][j][k] << endl;
    }

    cout << f[h][g][0] << endl;
}
