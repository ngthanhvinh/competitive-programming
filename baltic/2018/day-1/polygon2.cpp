#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, deg[N], p[N];
bool del[N], vis[N];
vector <int> g[N];
int res;
vector <int> comp;
map <string, int> mp; int id;

void dfs(int u) {
    comp.push_back(u);
    for (auto &v : g[u]) {
        if (deg[v] == 0) dfs(v);
    }
}

int calc(int u) {
    int ret = 0;
    for (auto &v : g[u]) if (deg[v] == 0) {
        ret += calc(v);
        if (!del[v] && !del[u]) ++ret, del[v] = del[u] = true;
    }
    return ret;
}

void find(int u, int r) {
    vis[u] = true;
    comp.push_back(u);
    int v = p[u];
    if (deg[v] > 0 && !vis[v] && !del[v]) {
        return find(v, r);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    if (n & 1) return printf("-1\n"), 0;

    for (int i = 1; i <= n; ++i) {
        string s, t; cin >> s >> t;
        if (mp.find(s) == mp.end()) mp[s] = ++id;
        if (mp.find(t) == mp.end()) mp[t] = ++id;

        int u = mp[s], v = mp[t];
        p[u] = v;
        g[v].push_back(u);
        ++deg[v];
    }

    queue <int> q;
    for (int i = 1; i <= n; ++i) if (!deg[i]) q.push(i);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        int v = p[u];
        if (--deg[v] == 0) {
            q.push(v);
        }
    }

    for (int i = 1; i <= n; ++i) if (deg[i] > 0) { // root
        comp.clear();
        dfs(i);
        int c1 = calc(i);
        
        for (auto &v : comp) del[v] = false;
        int c0 = 0;
        for (auto &v : g[i]) if (deg[v] == 0) c0 += calc(v);

        if (c1 > c0) {
            for (auto &v : comp) del[v] = false;
            calc(i);
            res += c1;
        } else {
            res += c0;
        }
    }


    for (int i = 1; i <= n; ++i) if (deg[i] == 1 && !del[i] && !vis[i]) {
        // route
        // check
        bool ok = true;
        for (auto &v : g[i]) {
            ok &= (!deg[v] || del[v]);
        }
        if (!ok) continue;
        // solve
        comp.clear();
        find(i, i);
        // cerr << i << ' ' << comp.size() << ' ' << iscycle << endl;
        res += (int)comp.size() / 2;
    }

    for (int i = 1; i <= n; ++i) if (deg[i] == 1 && !del[i] && !vis[i]) {
        // cycle
        comp.clear();
        find(i, i);
        if (comp.size() == 1) continue;
        if (comp.size() == 2) res += 2;
        else res += (int)comp.size() / 2;
    }

    printf("%d\n", n - res);
}