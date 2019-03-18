#include <iostream>
#include <cstdio>
using namespace std;

const int MX = 2010;
const int md = 1e9 + 7;

int inverse(int a) {
    int r = 1;
    for (int i = 0; (1ll << i) <= md - 2; ++i) {
        if ((md - 2) & (1ll << i)) r = 1ll * r * a % md;
        a = 1ll * a * a % md;
    }
    return r;
}

int N, M, R[MX], S, f[2 * MX], ft;
int nCase;
int ans;

void solve() {
    cin >> N >> M; S = 0;
    for (int i = 1; i <= N; ++i) cin >> R[i], S += 2 * R[i];
    if (N == 1) { printf("Case #%d: %d\n", ++nCase, M); return; }

    int base = N + M - S - 1;
    ft = 1; for (int i = 1; i <= N; ++i) ft = 1ll * ft * i % md; ft = inverse(ft);
    f[4000] = ft; for (int i = 0; i <= N - 1; ++i) f[4000] = 1ll * f[4000] * (max(base + 4000 - i, 0)) % md;

    for (int i = 3999; i >= 0; --i) {
        f[i] = 1ll * f[i+1] * (1ll * inverse(max(0, base + i + 1)) * (max(0, base + i - N + 1)) % md) % md;
    }

    ans = 0;
    for (int i = 1; i < N; ++i) for (int j = i + 1; j <= N; ++j) {
        ans = (ans + 2ll * f[R[i] + R[j]] % md) % md;
    }
    for (int i = 1; i <= N - 2; ++i) ans = 1ll * ans * i % md;
    printf("Case #%d: %d\n", ++nCase, ans);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while(T--)
        solve();
}
