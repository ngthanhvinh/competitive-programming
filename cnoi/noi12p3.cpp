// http://wcipeg.com/problem/noi12p3
// Day 1, Problem 3 - Magic Chessboard

#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int sz;
    vector<long long> T;
    SegmentTree() {}
    void init(int SIZE = 0) {
        sz = SIZE; T.assign(4 * sz + 5, 0);
    }
    #define mid ((l + r) >> 1)
    void upd(int v, int l, int r, int pos, long long val) {
        if (l > r || pos < l || pos > r) return;
        if (l == r) { T[v] = val; return; }
        upd(v << 1, l, mid, pos, val); upd(v << 1 | 1, mid + 1, r, pos, val);
        T[v] = __gcd(T[v << 1], T[v << 1 | 1]);
    }
    long long get(int v, int l, int r, int L, int R) {
        if (l > r || R < l || L > r) return 0;
        if (L <= l && r <= R) return T[v];
        return __gcd(get(v << 1, l, mid, L, R), get(v << 1 | 1, mid + 1, r, L, R));
    }
    void upd(int pos, long long val) { return upd(1, 1, sz, pos, val); }
    long long get(int l, int r) { return get(1, 1, sz, l, r); }
    #undef mid
} seg_row, seg_col;

struct SegmentTree2D {
    int nr, nc;
    vector<SegmentTree> tree;
    void init(int _nr = 0, int _nc = 0) {
        nr = _nr; nc = _nc;
        tree.assign(4 * nr + 5, SegmentTree());
        for (int i = 0; i < tree.size(); ++i) {
            tree[i].init(nc);
        }
    }

    void merge(int v, int v2, int ly, int ry, int py) {
        if (ly > ry || py < ly || py > ry) return;
        tree[v].T[v2] = __gcd(tree[v << 1].T[v2], tree[v << 1 | 1].T[v2]);
        if (ly == ry) return;
        merge(v, v2 << 1, ly, ((ly + ry) >> 1), py);
        merge(v, v2 << 1 | 1, ((ly + ry) >> 1) + 1, ry, py);
    }

    #define mid ((l + r) >> 1)
    void upd(int v, int l, int r, int px, int py, long long val) { // update a[px][py] = val
        //printf("v = %d l = %d r = %d px = %d py = %d val = %d\n", v, l, r, px, py, val);
        if (l > r || px < l || px > r) return;
        if (l == r) { // == px
            tree[v].upd(py, val); return;
        }
        upd(v << 1, l, mid, px, py, val); upd(v << 1 | 1, mid + 1, r, px, py, val);
        merge(v, 1, 1, nc, py);
    }

    long long get(int v, int l, int r, int lx, int rx, int ly, int ry) {
        if (l > r || rx < l || lx > r) return 0;
        if (lx <= l && r <= rx) return tree[v].get(ly, ry);
        return __gcd(get(v << 1, l, mid, lx, rx, ly, ry), get(v << 1 | 1, mid + 1, r, lx, rx, ly, ry));
    }
    #undef mid

    void upd(int px, int py, long long val) { return upd(1, 1, nr, px, py, val); }
    long long get(int lx, int rx, int ly, int ry) { return get(1, 1, nr, lx, rx, ly, ry); }
} seg2d;

const int N = 500005;
int n, m, x, y;
vector< vector<long long> > a;
long long difx[N], dify[N];
long long xy;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> x >> y;
    int tt; cin >> tt;

    a.assign(n + 2, vector<long long>(m + 2, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j]; 
            if (i == x && j == y) xy = a[i][j];
        }
    }
    seg_row.init(m);
    for (int i = 1; i <= m; ++i) {
        difx[i] = a[x][i] - a[x][i-1]; seg_row.upd(i, difx[i]);
    }
    seg_col.init(n);
    for (int i = 1; i <= n; ++i) {
        dify[i] = a[i][y] - a[i-1][y]; seg_col.upd(i, dify[i]);
    }

    seg2d.init(n, m);
    for (int i = n; i >= 1; --i) {
        for (int j = m; j >= 1; --j) {
            a[i][j] = a[i][j] + a[i-1][j-1] - a[i-1][j] - a[i][j-1];
            seg2d.upd(i, j, a[i][j]);
        }
    }
    
    // solve
    while(tt--) {
        int type; cin >> type;
        if (type == 0) { // get
            int lx, ly, rx, ry;
            cin >> lx >> ly >> rx >> ry;
            lx = x - lx; ly = y - ly; rx = x + rx; ry = y + ry;
            long long res = xy;
            res = __gcd(res, seg2d.get(lx + 1, rx, ly + 1, ry));
            res = __gcd(res, seg_row.get(ly + 1, ry)); // in row x: (x, ly+1) -> (x, ry)
            res = __gcd(res, seg_col.get(lx + 1, rx)); // in col y: (lx+1, y) -> (rx, y)
            printf("%lld\n", abs(res));
        } else { // type == 1: update
            int lx, ly, rx, ry;
            long long c;
            cin >> lx >> ly >> rx >> ry >> c;
            seg2d.upd(lx, ly, a[lx][ly] += c);
            seg2d.upd(lx, ry + 1, a[lx][ry + 1] -= c);
            seg2d.upd(rx + 1, ly, a[rx + 1][ly] -= c);
            seg2d.upd(rx + 1, ry + 1, a[rx + 1][ry + 1] += c);

            if (lx <= x && x <= rx) {
                seg_row.upd(ly, difx[ly] += c);
                seg_row.upd(ry + 1, difx[ry + 1] -= c);
            }
            if (ly <= y && y <= ry) {
                seg_col.upd(lx, dify[lx] += c);
                seg_col.upd(rx + 1, dify[rx + 1] -= c);
            }
            if (lx <= x && x <= rx && ly <= y && y <= ry) xy += c;
        }
    }
}