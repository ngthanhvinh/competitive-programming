#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
#define st first
#define nd second

const int N = 1e5 + 5, M = 220005;

int n, m, root, visited[N], Edge[M], cur, from[M], to[M];
vector<ii> a[N];

void dfs(int u) {
    visited[u] = true;
    for(int i = 0; i < a[u].size(); ++i) {
        int v = a[u][i].st;
        if(!Edge[a[u][i].nd]) Edge[a[u][i].nd] = ++cur;
        if(visited[v]) continue;
        dfs(v);
    }
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        a[u].push_back(ii(v, i));
        a[v].push_back(ii(u, i));
        from[i] = u; to[i] = v;
    }
    //for(int i = 1; i <= n; ++i) if(a[i].size() >= 2) root = i;
    dfs(1);
    for(int i = 1; i <= m; ++i) cout << from[i] << ' ' << to[i] << ' ' << Edge[i] << '\n';
}