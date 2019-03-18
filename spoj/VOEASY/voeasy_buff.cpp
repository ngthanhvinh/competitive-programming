#include <bits/stdc++.h>
using namespace std;

struct query {
    int u; int v; char c;
    query(int u=0, int v=0, char c='a'): u(u), v(v), c(c) {}
};

query q[110][11];
int n, m, k, a[11], b[11];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int u, v; string op; cin >> u >> op >> v;
            q[i][j] = query(u-1, v-1, op[0]);
        }
    }

    for (int i = 0; i < k; ++i) {
        int t = i % m;
        for (int j = 0; j < n; ++j) {
            int u = q[t][j].u, v = q[t][j].v; char c = q[t][j].c;
            if (c == 'a') b[j] = (a[u]&a[v]);
            if (c == 'o') b[j] = (a[u]|a[v]);
            if (c == 'x') b[j] = (a[u]^a[v]);
        }
        for (int j = 0; j < n; ++j) a[j] = b[j];
    }
    for (int i = 0; i < n; ++i) cout << a[i] << ' '; cout << endl;
}
