#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const long long INF = 1e18;

int N, M;
int C[310][310];
long long f[310][310], sum[310][310];

void mnm(long long &a, long long b) { if (a > b) a = b; }

int nCase;
void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) cin >> C[i][j];
    for (int i = 1; i <= N; ++i) {
        sort(C[i] + 1, C[i] + M + 1);
        for (int j = 1; j <= M; ++j) sum[i][j] = sum[i][j-1] + C[i][j];
    }
    for (int i = 0; i <= N; ++i) for (int j = 0; j <= N; ++j) f[i][j] = INF;
    f[0][0] = 0;
    for (int i = 1; i <= N; ++i) for (int j = 0; j <= N; ++j) if (f[i-1][j] != INF) {
        for (int k = 0; k <= min(M, N-j); ++k) mnm(f[i][j + k], f[i-1][j] + sum[i][k] + k * k);
    }

    printf("Case #%d: %lld\n", ++nCase, f[N][N]);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while(T--)
        solve();
}
