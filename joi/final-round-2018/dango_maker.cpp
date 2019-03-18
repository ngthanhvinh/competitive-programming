#include <bits/stdc++.h>
using namespace std;

const int N = 3005;
const int inf = 1e9;

int n, m;
char a[N][N];
int dp[N + N][N];
int ans;

inline bool check(int x, int y, int state) {
    if (!state) return true;
    if (state == 1) { // top -> bottom
        if (a[x - 1][y] == 'R' && a[x][y] == 'G' && a[x + 1][y] == 'W') return true;
        else return false;
    } else { // left -> right
        if (a[x][y - 1] == 'R' && a[x][y] == 'G' && a[x][y + 1] == 'W') return true;
        else return false;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> a[i][j];
    }
    for (int s = 2; s <= n + m; ++s) {
        dp[max(1, s - m) - 1][0] = 0;
        dp[max(1, s - m) - 1][1] = -inf;
        dp[max(1, s - m) - 1][2] = -inf;
        for (int i = max(1, s - m); i <= min(n, s - 1); ++i) {
            int j = s - i;
            for (int state = 0; state < 3; ++state) 
                dp[i][state] = -inf;
            for (int state = 0; state < 3; ++state) {
                for (int nstate = 0; nstate < 3; ++nstate) {
                    if (state > 0 && nstate > 0 && state != nstate) continue;
                    if (!check(i, j, nstate)) continue;
                    dp[i][nstate] = max(dp[i][nstate], dp[i - 1][state] + (nstate != 0));
                }
            }
        }
        int mx = 0;
        for (int state = 0; state < 3; ++state) mx = max(mx, dp[min(n, s - 1)][state]);
        ans += mx;
    }
    cout << ans << endl;
}