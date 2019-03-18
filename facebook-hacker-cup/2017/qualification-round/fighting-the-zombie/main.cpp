#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;

int T, H, S, nCase, X[11], Y[11], Z[11];
double f[21][21 * 21], sum[21 * 21];
double ans;

void solve() {
    cin >> H >> S;
    for (int i = 1; i <= S; ++i) {
        string str; cin >> str;
        X[i] = Y[i] = Z[i] = 0;
        int cur = 0; int sign = 0;
        for (int j = 0; j < str.size(); ++j) {
            if (str[j] != 'd' && str[j] != '-' && str[j] != '+') {
                if (cur == 0) X[i] = 10 * X[i] + str[j] - '0';
                if (cur == 1) Y[i] = 10 * Y[i] + str[j] - '0';
                if (cur == 2) Z[i] = 10 * Z[i] + str[j] - '0';
            }
            else cur++;
            if (str[j] == '-') sign = -1; else if (str[j] == '+') sign = 1;
        }
        Z[i] = sign * Z[i];
    }

    ans = 0.0;

    for (int t = 1; t <= S; ++t) {
        int x = X[t], y = Y[t], z = H - Z[t];
        f[0][0] = 1.0;
        for (int i = 1; i <= x; ++i) for (int j = 0; j <= x * y; ++j) f[i][j] = 0.0;
        for (int i = 1; i <= x; ++i) {
            for (int j = 0; j <= i * y; ++j) sum[j + 1] = sum[j] + f[i - 1][j];
            for (int j = 1; j <= i * y; ++j) {
                int l = max(0, j - y), r = j - 1;
                f[i][j] = (sum[r + 1] - sum[l]) * (double)1.0 / y;
            }
        }
        double res = 0.0; for (int i = max(0, z); i <= x * y; ++i) res += f[x][i];
        ans = max(ans, res);
    }

    cout << "Case #" << ++nCase << ": " << setprecision(6) << fixed << ans << endl;
}

int main() {
//    freopen("fighting_the_zombie.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--)
        solve();
}
