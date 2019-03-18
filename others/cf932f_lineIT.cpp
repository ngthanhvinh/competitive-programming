#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const long long INF = 1e18;

struct Line {
    int a; long long b; // ax + b
    // -1e5 <= a <= 1e5, |F| <= 1e15
    Line(int a = 0, long long b = INF) : a(a), b(b) {}
    long long f(int x) { return 1LL * a * x + b; }
};

struct LineIT {
    #define mid ((l + r) >> 1)

    struct Node {
        int l; int r;
        Node *le, *ri;
        Line opt;
        Node() { le = NULL; ri = NULL; }
        void push() {
            if (l < r && le == NULL) {
                le = new Node(); le->l = l; le->r = mid;
                ri = new Node(); ri->l = mid + 1; ri->r = r;
            }
        }
    } *root;

    LineIT() { root = new Node(); root->l = -1e5; root->r = 1e5; }

    void upd(Node *v, int L, int R, Line d) {
        v->push();
        int l = v->l, r = v->r;
        if (R < l || L > r) return;
        if (L <= l && r <= R) {
            if (d.f(l) >= (v->opt).f(l) && d.f(r) >= (v->opt).f(r)) { // d is located above the current line
                return;
            } else if (d.f(l) <= (v->opt).f(l) && d.f(r) <= (v->opt).f(r)) { // d is located below the current line
                v->opt = d; return;
            }
        }
        upd(v->le, L, R, d);
        upd(v->ri, L, R, d);
    }

    long long get(Node *v, int x) {
        if (v == NULL) return INF;
        int l = v->l, r = v->r;
        if (x < l || x > r) return INF;
        long long res = (v->opt).f(x);
        res = min(res, get(v->le, x));
        res = min(res, get(v->ri, x));
        return res;
    }
} *it[N];

int n, A[N], B[N];
long long F[N];
vector<Line> vals[N];
vector<int> G[N];

void dfs(int u, int p = 0) {
    int big = u;
    it[u] = new LineIT();
    for (int v : G[u]) if (v != p) {
        dfs(v, u);
        if (vals[v].size() > vals[big].size()) big = v;
    }

    vals[u].swap(vals[big]);
    it[u] = it[big];

    for (int v : G[u]) if (v != p && v != big) {
        for (Line &d : vals[v]) {
            it[u]->upd(it[u]->root, -1e5, 1e5, d);
            vals[u].push_back(d);
        }
    }
    
    // get F
    F[u] = it[u]->get(it[u]->root, A[u]);
    if (F[u] == INF) F[u] = 0; // u is a leaf

    // update vals[u] and it[u]
    vals[u].push_back(Line(B[u], F[u]));
    it[u]->upd(it[u]->root, -1e5, 1e5, Line(B[u], F[u]));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> A[i];
    for (int i = 1; i <= n; ++i) cin >> B[i];
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }

    dfs(1);

    for (int i = 1; i <= n; ++i) printf("%lld ", F[i]); printf("\n");
}