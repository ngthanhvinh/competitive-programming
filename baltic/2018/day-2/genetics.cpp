#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 4105;
const int mod = 1e9 + 123;
const int base = 5102000;
 
int n, m, p;
int f[N][4];
int pw[N];
int a[N][N];
 
int to(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    if (c == 'T') return 3;
}
 
void add(int &x, int y) {
    x = x + y >= mod ? x + y - mod : x + y;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> p;
    pw[0] = 1;
    for (int i = 1; i < n; ++i) pw[i] = 1LL * base * pw[i - 1] % mod;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < m; ++j) {
            a[i][j] = to(s[j]);
        }
        for (int j = 0; j < m; ++j) {
            add(f[j][a[i][j]], pw[i]);     
        }
    }
    for (int i = 0; i < n; ++i) {
        long long cur = 0;
        long long all = 0;
        for (int j = 0; j < n; ++j) {
            if (j != i) all += 1LL * pw[j] * p % mod;
        }
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < 4; ++k) {
                if (k != a[i][j]) cur += f[j][k];
            }
        }
        cur %= mod, all %= mod;
        // cout << cur << ' ' << all << '\n';
        if (cur == all) {
            cout << i + 1; return 0;
        }
    }
}