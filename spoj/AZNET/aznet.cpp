#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 10010;

struct edge {
    int u; int v; int w; int id;
    edge(int u=0, int v=0, int w=0, int id=0): u(u), v(v), w(w), id(id) {}
    bool operator < (const edge &other) const {
        return w < other.w;
    }
    bool operator > (const edge &other) const {
        return w > other.w;
    }
};

int n, m, k, a[N], b[N];
vector <edge> e;
bool check[10 * N];
int cnt[2], par[N];
long long ans;

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) { par[anc(p)] = anc(q); }

void solve() {
    cin >> n >> m; e.clear(); cnt[0] = cnt[1] = 0;
    for (int i = 1; i < n; ++i) cin >> a[i];
    for (int i = 1; i < n; ++i) cin >> b[i];
    for (int i = 1; i <= m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        e.push_back(edge(u,v,w,i));
        check[i] = 0;
        cnt[w-1]++;
    }
    for (int i = 1; i <= n; ++i) par[i] = i;
    sort(e.begin(), e.end()); k = 0;
    for (int i = 0; i < e.size(); ++i) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if (anc(u) != anc(v)) { join(u, v); if (w == 2) ++k, check[e[i].id] = 1; }
    }
    ans = 1e18;
    int mx = k;
    for (int i = k; i <= min(n-1, min(cnt[1], k+cnt[0])); ++i) if (ans > b[i] + a[n-1-i]) ans = b[i] + a[n-1-i], mx = i;

    for (int i = 1; i <= n; ++i) par[i] = i;
    for (int i = 0; i < e.size(); ++i) if (check[e[i].id]) join(e[i].u, e[i].v);
    sort(e.begin(), e.end(), greater<edge>());
    int remB = mx-k;
    for (int i = 0; i < e.size(); ++i) {
        if (e[i].w == 2 && !check[e[i].id] && anc(e[i].u) != anc(e[i].v)) {
            if (!remB) continue;
            --remB; check[e[i].id] = 1;
            join(e[i].u, e[i].v);
        }
        else if (e[i].w == 1 && anc(e[i].u) != anc(e[i].v)) {
            check[e[i].id] = 1;
            join(e[i].u, e[i].v);
        }
    }
    for (int i = 1; i <= m; ++i) if (check[i]) printf("%d ", i); printf("\n");
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--)
        solve();
}
