#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

#define int long long

const int N = 110;
const int MOD = 1e9 + 123, BASE = 1e9 + 7;

int val[26];

int n, m, a[N][N], b[N][N];
int pw[N * N];
int ans;

void prep(int x[N][N]) {
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) x[i][j] = (x[i][j-1] * BASE + x[i][j]) % MOD;
    for (int j = 1; j <= m; ++j) for (int i = 1; i <= n; ++i) x[i][j] = (x[i-1][j] * BASE + x[i][j]) % MOD;
}

int get(int H[N][N], int x, int y, int dx, int dy) {
    --x, --y;
    int res1 = (H[x+dx][y+dy] - H[x][y+dy] * pw[dx]) % MOD;
    int res2 = pw[dy] * ((H[x+dx][y] - 1ll * H[x][y] * pw[dx]) % MOD);
    return ((res1 - res2) % MOD + MOD) % MOD;
}

map <int, bool> mp;
bool findRect(int r, int c) {
    mp.clear();
    for (int i = 1; i <= n - r + 1; ++i) for (int j = 1; j <= m - c + 1; ++j) mp[get(a, i, j, r, c)] = 1;
    for (int i = 1; i <= n - r + 1; ++i) for (int j = 1; j <= m - c + 1; ++j) {
        if (mp.count(get(b, i, j, r, c))) { ans = max(ans, r * c); return 1; }
    }
    return 0;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < 26; ++i) val[i] = rand() % BASE;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) { char c; cin >> c; a[i][j] = c - 'a'; a[i][j] = val[a[i][j]]; }
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) { char c; cin >> c; b[i][j] = c - 'a'; b[i][j] = val[b[i][j]]; }
    prep(a); prep(b);
    ans = 0;
    for (int i = 1; i <= n; ++i) {
        int l = 0, r = m;
        while(l != r) {
            int mid = ((l + r + 1) >> 1);
            if (!findRect(i, mid)) r = mid-1;
            else l = mid;
        }
    }
    printf("%lld\n", ans);
}

main() {
    freopen("message1.inp", "r", stdin);
    freopen("message1.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    pw[0] = 1; for (int i = 1; i < N * N; ++i) pw[i] = 1ll * pw[i-1] * BASE % MOD;
    int t; cin >> t;
    while(t--) {
        solve();
    }
}
