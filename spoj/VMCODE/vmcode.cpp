#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int N = 2005, INF = 1e9 + 123;
const int dx[] = {1,1,1}, dy[] = {-1,0,1};

int n, m, k;
vector <int> pos[26][N];
char a[N][N];
string s;
string ans;

int f[N][N], t[2][N][N];
/*
t[0][i][j]: so duong di tu (i,j) ve dich
t[1][i][j]: so duong di tu (i,j) ve dich nhung > suffix cua s
*/
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> k >> s; s = ' ' + s; --k;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> a[i][j], pos[a[i][j]-'a'][i].push_back(j);

    for (int i = 1; i <= m; ++i) { if (a[n][i] > s[n]) t[1][n][i] = 1; t[0][n][i] = 1; }

    for (int i = n-1; i >= 1; --i) for (int j = 1; j <= m; ++j) {
        for (int k = 0; k < 3; ++k) {
            int x = i + dx[k], y = j + dy[k]; if (x < 1 || x > n || y < 1 || y > m) continue;
            t[0][i][j] += t[0][x][y];
            if (a[i][j] > s[i]) t[1][i][j] += t[0][x][y]; else if (a[i][j] == s[i]) t[1][i][j] += t[1][x][y];
            t[0][i][j] = min(t[0][i][j], INF); t[1][i][j] = min(t[1][i][j], INF);
        }
    }

    for (int i = 1; i <= m; ++i) f[1][i] = 1;
    bool ok = 0;
    for (int i = 1; i <= n; ++i) {
        char cur;
        for (int ch = 0; ch < 26; ++ch) {
            if (!ok && ch < s[i] - 'a') continue;
            long long res = 0;
            for (int p: pos[ch][i]) {
                if (!ok) {
                    if (ch == s[i] - 'a') res += 1ll * f[i][p] * t[1][i][p];
                    else res += 1ll * f[i][p] * t[0][i][p];
                }
                else res += 1ll * f[i][p] * t[0][i][p];
                res = min(res, (long long)INF);
            }
            if (k >= res) k -= res;
            else { cur = (char)(ch + 'a'); ans += cur; if (!ok && cur > s[i]) ok = 1; break; }
        }
        // update f[i+1][j]
        for (int j = 1; j <= m; ++j) if (a[i][j] == cur) {
            for (int k = 0; k < 3; ++k) {
                int x = i + dx[k], y = j + dy[k]; if (x < 1 || x > n || y < 1 || y > m) continue;
                f[x][y] += f[i][j];
                f[x][y] = min(f[x][y], INF);
            }
        }
    }

    cout << ans << endl;
}
