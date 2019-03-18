#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int INF = 1e8 + 100;
typedef pair<int,int> ii;

struct Query { int s; int t; } query[N];

int n, m, k, q;
vector<int> imp;
vector<ii> G[N];
int d[N];
int par[N];
int low[N], high[N];
vector<ii> events, D;

void dijkstra() {
    for (int i = 1; i <= n; ++i) d[i] = INF;
    
    priority_queue < ii, vector<ii>, greater<ii> > pq;
    for (int u : imp) d[u] = 0, pq.push(ii(0, u));

    while(!pq.empty()) {
        ii top = pq.top(); pq.pop();
        int u = top.second, du = top.first;
        if (du != d[u]) continue;

        for (auto e : G[u]) {
            int v = e.second, w = e.first;
            if (d[v] > du + w) pq.push(ii(d[v] = du + w, v));
        }
    }
}

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) { par[anc(p)] = anc(q); }

void solve() {
    for (int i = 1; i <= n; ++i) par[i] = i;
    sort(events.begin(), events.end());

    int ptr = events.size() - 1;
    for (int i = D.size() - 1; i >= 0; --i) {
        int u = D[i].second;
        for (auto e : G[u]) if (d[e.second] >= d[u]) join(u, e.second);
        while(ptr >= 0 && events[ptr].first >= i) {
            int id = events[ptr].second;
            if (anc(query[id].s) == anc(query[id].t)) {
                low[id] = events[ptr].first;
            } else high[id] = events[ptr].first - 1;
            --ptr;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    while(m--) {
        int u, v, w; cin >> u >> v >> w;
        G[u].push_back(make_pair(w, v));
        G[v].push_back(make_pair(w, u));
    }
    cin >> k;
    for (int i = 1; i <= k; ++i) {
        int x; cin >> x; imp.push_back(x);
    }

    // prepare
    dijkstra();
    for (int i = 1; i <= n; ++i) {
        D.push_back(ii(d[i], i));
    }
    sort(D.begin(), D.end());

    // process queries
    cin >> q;
    for (int i = 1; i <= q; ++i) {
        cin >> query[i].s >> query[i].t;
        low[i] = 0;
        high[i] = D.size() - 1;
    }

    while(true) {
        events.clear();
        for (int i = 1; i <= q; ++i) {
            if (low[i] < high[i]) events.push_back(ii((low[i] + high[i] + 1) >> 1, i));
        }
        if (events.empty()) break;

        solve();
    }

    for (int i = 1; i <= q; ++i) {
        printf("%d\n", D[low[i]].first);
    }
}