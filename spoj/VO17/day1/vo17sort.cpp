#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int cnt;
int n;
vector <int> a;
map < vector<int>, int > d[2];
map < vector<int>, int > :: iterator it;

vector < vector<int> > G;

void build() {
    G.clear();
    vector <int> u; for (int i = 1; i <= n; ++i) u.push_back(i);

    for (int i = 0; i < n; ++i) for (int j = i; j < n; ++j) {
        vector <int> nxt = u;
        vector <int> del;
        for (int k = i; k <= j; ++k) del.push_back(nxt[k]);
        for (int k = j; k >= i; --k) nxt.erase(nxt.begin() + k);
        for (int pos = 0; pos <= nxt.size(); ++pos) {
            vector <int> Next;
            for (int k = 0; k < pos; ++k) Next.push_back(nxt[k]);
            for (int k = 0; k < del.size(); ++k) Next.push_back(del[k]);
            for (int k = pos; k < nxt.size(); ++k) Next.push_back(nxt[k]);

            G.push_back(Next);
        }
    }
}

void bfs(vector<int> a, int ok) {
    queue < vector<int> > q; q.push(a); d[ok].clear(); d[ok][a] = 0;
    while(!q.empty()) {
        vector<int> u = q.front(); q.pop(); if (d[ok][u] == 2) continue;
        for (int i = 0; i < G.size(); ++i) {
            vector <int> v;
            for (int j = 0; j < n; ++j) v.push_back(u[G[i][j]-1]);
            if (!d[ok].count(v)) d[ok][v] = d[ok][u] + 1, q.push(v);
        }
    }
}

void solve() {
    cin >> n;
    build();
    a.assign(n, 0); for (int i = 0; i < n; ++i) cin >> a[i];
    bfs(a, 0);
    a.assign(n, 0); for (int i = 0; i < n; ++i) a[i] = i+1;
    bfs(a, 1);

    int ans = 1e9;

    for (it = d[1].begin(); it != d[1].end(); ++it) {
        if (d[0].count(it->first)) ans = min(ans, d[0][it->first] + it->second);
    }

    if (ans != 1e9) printf("%d\n", ans); else printf("5 or more\n");
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--)
        solve();
}
