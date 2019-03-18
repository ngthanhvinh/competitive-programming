#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 100010, M = 1000010;
int par[N];
int t, n, m, q;
int fr[M], to[M], w[M], oldW[M];
int tp[110], cp[110];

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) { par[anc(p)] = anc(q); }

void solve() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; ++i) scanf("%d%d%d", &fr[i], &to[i], &oldW[i]), w[i] = oldW[i];
    while(q--) {
        for (int i = 1; i <= n; ++i) par[i] = i;
        int k; scanf("%d", &k);
        int s; scanf("%d", &s);
        for (int i = 1; i <= s; ++i) { scanf("%d%d", &tp[i], &cp[i]); w[tp[i]] = cp[i]; }
        for (int i = 1; i <= m; ++i) if (w[i] < w[k]) join(fr[i], to[i]);
        if (anc(fr[k]) != anc(to[k])) printf("NO\n"); else printf("YES\n");
        for (int i = 1; i <= s; ++i) w[tp[i]] = oldW[tp[i]];
    }
}

int main() {
    scanf("%d", &t);
    while(t--)
        solve();
}
