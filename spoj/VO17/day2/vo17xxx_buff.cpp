#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7, MAX = 1000010;

int N, C, a[100010];
int pw[100], pw2[100010], d[1000010], cPrime[1000010];
int ans;

void sieve() {
    d[0] = d[1] = 1;
    for (int i = 2; i < MAX; ++i) if (!d[i]) {
        for (int j = i; j < MAX; j += i) d[j] = i, cPrime[j]++;
    }
}

int main() {
    freopen("vo17xxx.inp", "r", stdin);
    freopen("vo17xxx.ans", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> C;
    sieve();
    for (int i = 0; i < N; ++i) cin >> a[i];
    pw[0] = 1; for (int i = 1; i < 100; ++i) pw[i] = 1LL * pw[i-1] * C % MOD;
    pw2[0] = 1; for (int i = 1; i <= N; ++i) pw2[i] = 2LL * pw2[i-1] % MOD;

    for (int mask = 1; mask < (1<<N); ++mask) {
        int g = 0;
        for (int i = 0; i < N; ++i) if (mask & (1<<i)) g = __gcd(g, a[i]);
        ans = (ans + pw[cPrime[g]]) % MOD;
    }
    cout << ans << endl;
}
