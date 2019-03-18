#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define int long long
const int N = 100010, MOD = 1000000009;

int n, k, a[N];
int f[N][2][2];
int ans;

void add(int &x, int y) { x += y; while(x >= MOD) x -= MOD; if (x < 0) x += MOD; }

void solve() {
    ans = 0; k = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], k ^= a[i];

    for (int bit = 31; bit >= 0; --bit) {
        memset(f, 0, sizeof f);
        f[0][0][0] = 1;
        int MAX = (1LL << bit);
        for (int i = 1; i <= n; ++i) for (int x = 0; x < 2; ++x) for (int ok = 0; ok < 2; ++ok) {
            if (a[i] < MAX) add(f[i][x][ok], 1LL * f[i-1][x][ok] * (a[i]+1) % MOD);
            else {
                // choose 0
                if (!ok) add(f[i][x][1], f[i-1][x][0]);
                else add(f[i][x][ok], 1LL * f[i-1][x][ok] * MAX % MOD);
                // choose 1
                add(f[i][x^1][ok], 1LL * f[i-1][x][ok] * (a[i]-MAX+1) % MOD);
            }
        }
        int kb = ((k>>bit) & 1);
        add(ans, f[n][kb][1]);
        bool Xor = 0;
        for (int i = 1; i <= n; ++i) {
            if (a[i] >= MAX) Xor ^= 1, a[i] -= MAX;
        }
        if (Xor != kb) break;
        if (bit == 0) add(ans, 1);
    }
    printf("%lld\n", ans);
}

main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--)
        solve();
}
/*
4
1
5
2
3 3
3
3 3 3
4
1 2 3 4
*/


