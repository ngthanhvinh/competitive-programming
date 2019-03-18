#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 100010;

int n, st[N], en[N], p[N];
vector <int> G[N];
int cnt;
vector <int> z;
vector < pair<int,int> > zz;

void dfs(int u) {
    st[u] = ++cnt;
    for (int i = 0; i < G[u].size(); ++i) dfs(G[u][i]);
    en[u] = cnt;
}

int T[N], ans[N];
void upd(int x) { for (; x < N; x += x & -x) T[x]++; }
int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res += T[x]; return res; }

int main() {
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> p[i], z.push_back(p[i]);
    for (int i = 2; i <= n; ++i) {
        int x; cin >> x;
        G[x].push_back(i);
    }
    dfs(1);
    sort(z.begin(), z.end()); z.resize(distance(z.begin(), unique(z.begin(), z.end())));
    for (int i = 1; i <= n; ++i) p[i] = lower_bound(z.begin(), z.end(), p[i]) - z.begin() + 1, zz.push_back(make_pair(p[i], i));
    sort(zz.begin(), zz.end(), greater < pair<int,int> >());

    for (int i = 0; i < zz.size(); ++i) {
        int u = zz[i].second, val = zz[i].first;
        ans[u] = get(en[u]) - get(st[u] - 1);
        upd(st[u]);
    }
    for (int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
}
