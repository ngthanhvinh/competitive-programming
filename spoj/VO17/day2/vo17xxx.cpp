#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const int MAX = 30000001, MOD = 1e9 + 7;

int N, C, a[100010];
int d[MAX], nPrime[MAX], cnt[MAX], f[10], comb[10][10];
int pw2[100010], pwC[10];
int lg[1 << 10];

void add(int &x, int y) { x += y; while(x >= MOD) x -= MOD; }

void prep() {
    d[0] = d[1] = 1;
    for (int i = 2; i < MAX; ++i) if (!d[i])
        for (int j = i; j < MAX; j += i) d[j] = i;
    for (int i = 2; i < MAX; ++i) nPrime[i] = nPrime[i / d[i]] + ((i / d[i]) % d[i] != 0);

    for (int i = 0; i <= 9; ++i) comb[i][0] = 1;
    for (int i = 1; i <= 9; ++i) for (int j = 1; j <= i; ++j) comb[i][j] = comb[i-1][j] + comb[i-1][j-1];

    pw2[0] = 1; for (int i = 1; i <= N; ++i) pw2[i] = pw2[i-1], add(pw2[i], pw2[i]);
    pwC[0] = 1; for (int i = 1; i < 10; ++i) pwC[i] = 1ll * pwC[i-1] * C % MOD;
}

int main() {
    //freopen("vo17xxx.inp", "r", stdin);
    //freopen("vo17xxx.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> C;
    prep();
    for (int i = 1; i <= N; ++i) cin >> a[i];
    for (int i = 0; i < 10; ++i) lg[1 << i] = i;

    for (int i = 1; i <= N; ++i) {
        int x = a[i], sz = 0;
        vector <int> dvs;
        while(x != 1) { int t = d[x]; while(x % t == 0) x /= t; dvs.push_back(t); ++sz; }

        ++cnt[1]; vector <int> num(1 << sz, 1);
        for (int mask = 1; mask < (1<<sz); ++mask) {
            num[mask] = num[mask ^ (mask & -mask)] * dvs[lg[mask & -mask]];
            ++cnt[num[mask]];
        }
    }
    for (int i = 1; i < MAX; ++i) if (cnt[i]) add(f[nPrime[i]], pw2[cnt[i]] - 1);
    for (int i = 9; i >= 0; --i) {
        int sub = 0;
        for (int j = i+1; j < 10; ++j) if (f[j]) sub = (sub + 1ll * f[j] * comb[j][i]) % MOD;
        add(f[i], MOD - sub);
    }

    int ans = 0;
    for (int i = 0; i <= 9; ++i) if (f[i]) ans = (ans + 1ll * f[i] * pwC[i]) % MOD;
    printf("%d\n", ans);
}
