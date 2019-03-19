#include <iostream>
#include <cstdio>
using namespace std;

const int N = 1000010;

int n, a[N], par[N];
bool check[N];
int ans;

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) { p = anc(p); q = anc(q); if (p != q) par[p] = q; }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], par[i] = i;
    for (int i = 1; i <= n; ++i) join(a[i], i);

    for (int i = 1; i <= n; ++i) check[anc(i)] = 1;
    for (int i = 1; i <= n; ++i) ans += check[i];

    printf("%d\n", ans);
}
