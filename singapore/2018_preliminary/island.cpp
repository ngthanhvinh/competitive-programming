#include <bits/stdc++.h>
using namespace std;

const int N = 200105;

int n, m;
vector<int> g[N];
int f[N];

void dfs(int u, int p) {
    int nchild = 0;
    for (int &v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
        ++nchild;
    }

    if (!nchild) return;
    if (u == n + m) --nchild;

    // * (nchild!)
    f[nchild + 1]--;
    f[2]++;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i < n + m; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(n + m, 0);

    for (int i = 2; i < N; ++i) {
        f[i] += f[i - 1];
        if (f[i] > 0) printf("%d %d\n", i, f[i]);
    }
}