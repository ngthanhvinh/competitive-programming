#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
using namespace std;

const int N = 100010;

int n, sz[N];
int st[N], en[N], ver[N], step;
vector<int> G[N];
int color[N];
int ans;

void print_answer() {
    for (int i = 1; i <= n; ++i) printf("%d ", color[i]);
    printf("\n");
    exit(0);
}

typedef pair<int,int> ii;
vector<ii> ch[N];
bool found = 0;

void dfs(int u, int p) {
    sz[u] = 1; bool ok = 1; st[u] = ++step; ver[step] = u;
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i]; if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > n / 2) ok = 0; ch[u].push_back(ii(sz[v], v));
    }
    en[u] = step;
    if (sz[u] < n) ch[u].push_back(ii(n - sz[u], 0)); if (n - sz[u] > n / 2) ok = 0;
    if (!ok || ch[u].size() < 3) return;
    if (!found) color[u] = 0, ans = u, found = 1;
}

vector<int> c[4];


void process(int co) {
    for (int i = 0; i < c[co].size(); ++i) {
        int v = c[co][i]; color[v] = co;
        if (v) for (int j = st[v]; j <= en[v]; ++j) color[ver[j]] = co;
        else {
            for (int j = 1; j < st[ans]; ++j) color[ver[j]] = co;
            for (int j = en[ans]+1; j <= n; ++j) color[ver[j]] = co;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    memset(color, -1, sizeof color);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }
    dfs(1, 1);
    if (!found) { printf("-1\n"); return 0; }
    int sz1 = 0, sz2 = 0, sz3 = 0;
    for (int i = 0; i < ch[ans].size(); ++i) {
        int v = ch[ans][i].second;
        if (sz1 + ch[ans][i].first <= n / 2) c[1].push_back(v), sz1 += ch[ans][i].first;
        else if (sz2 + ch[ans][i].first <= n / 2) c[2].push_back(v), sz2 += ch[ans][i].first;
        else c[3].push_back(v), sz3 += ch[ans][i].first;
    }
    if (c[3].empty()) {
        if (c[1].size() > 1) c[3].push_back(c[1].back()), c[1].pop_back();
        else if (c[2].size() > 1) c[3].push_back(c[2].back()), c[2].pop_back();
    }
    for (int i = 1; i <= 3; ++i) process(i);
    print_answer();
}
