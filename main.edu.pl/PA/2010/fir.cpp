#include <bits/stdc++.h>
using namespace std;
typedef vector <int> vi;
typedef pair <int, int> ii;
const int N = 100010;
int m, n, cur;
vector <vi> G;

struct query {
    char type; int u; int v;
} q[N];
vector <ii> E;
int T[N], start[N], finish[N], d[N], pos[N], p[N];
vector <int> s[N], ans;

void dfs(int u) {
    T[++cur] = u; start[u] = cur; pos[u] = cur;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        d[v] = d[u] + 1; dfs(v);
    }
    finish[u] = cur;
}

struct fenwickTree {
    int sz; vector <int> t;
    fenwickTree(int k = 0) { sz = k; t.assign(sz + 1, 0); }
    void upd(int x, int val) { for (; x <= sz; x += x & -x) t[x] += val; }
    int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res += t[x]; return res; }
} tr[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> m; n = 1;
    for (int i = 1; i <= m; i++) {
        cin >> q[i].type >> q[i].u >> q[i].v;
        if (q[i].type == 'Z') E.push_back(ii(q[i].v, q[i].u)), n = max(n, q[i].u), n = max(n, q[i].v);
    }
    G.assign(n + 1, vi());
    for (int i = 0; i < E.size(); i++) G[E[i].first].push_back(E[i].second);
    dfs(1);
    for (int i = 1; i <= n; i++) s[d[i]].push_back(pos[i]);
    for (int i = 0; i <= n; i++) if (s[i].size()) {
        sort(s[i].begin(), s[i].end()); tr[i] = fenwickTree(s[i].size());
        for (int j = 0; j < s[i].size(); j++) p[T[s[i][j]]] = j + 1, tr[i].upd(j + 1, 1);
    }

    for (int i = m; i >= 1; i--) {
        if (q[i].type == 'P') {
            int D = d[q[i].u] + q[i].v + 1, u = q[i].u;
            if (D > n) { ans.push_back(0); continue; }
            int pos1 = lower_bound(s[D].begin(), s[D].end(), finish[u] + 1) - s[D].begin();
            int pos2 = lower_bound(s[D].begin(), s[D].end(), start[u]) - s[D].begin() + 1;

            int r = tr[D].get(pos1) - tr[D].get(pos2 - 1);
            ans.push_back(r);
        }

        else {
            int u = q[i].u, dist = d[u];
            tr[dist].upd(p[u], -1);
        }
    }

    for (int i = ans.size()-1; i >= 0; i--) printf("%d\n", ans[i]);
}
