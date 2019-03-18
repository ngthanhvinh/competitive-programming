#include <bits/stdc++.h>
using namespace std;

const int N = 755;
const int inf = 1e9;

int n, a[N];
int dp[2][N][N];

void mnm(int &x, int y) { x = (x > y) ? y : x; }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1, greater<int>());
    for (int i = n; i >= 1; --i) a[i] += a[i + 1];

    for (int t = 0; t < 2; ++t) {
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) dp[t][i][j] = inf;
        }
    }
    dp[0][0][1] = 0;

    for (int i = 0; i <= n; ++i) {
        int t = i & 1;
        for (int c0 = 0; c0 <= n - (i + 1); ++c0) {
            for (int c1 = 0; c1 <= n - (i + 1) - c0; ++c1) {
                dp[t ^ 1][c0][c1] = inf;
            }
        }
        for (int c0 = 0; c0 <= n - i; ++c0) {
            for (int c1 = 0; c1 <= n - i - c0; ++c1) if (dp[t][c0][c1] != inf) {
                // fix a node
                if (c0 > 0) {
                    mnm(dp[t ^ 1][c0 - 1][c1], dp[t][c0][c1]);
                }
                // expand c0 nodes -> c0 + c0 nodes
                mnm(dp[t][c0 + c1][c0], dp[t][c0][c1] + a[i + 1]);
            }
        }
    }

    cout << dp[n & 1][0][0] - a[1] << endl;
}
