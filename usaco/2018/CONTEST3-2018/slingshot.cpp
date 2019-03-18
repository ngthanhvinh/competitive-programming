#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const long long INF = 1e12;

struct FenwickTree {
    long long T1[N], T2[N];
    
    void reset() {
        for (int i = 0; i < N; ++i) T1[i] = T2[i] = INF;
    }

    void upd_lef(int x, long long v) { for (; x > 0; x -= x & -x) T1[x] = min(T1[x], v); }
    long long get_rig(int x) { long long ret = INF; for (; x < N; x += x & -x) ret = min(ret, T1[x]); return ret; }
    void upd_rig(int x, long long v) { for (; x < N; x += x & -x) T2[x] = min(T2[x], v); }
    long long get_lef(int x) { long long ret = INF; for (; x > 0; x -= x & -x) ret = min(ret, T2[x]); return ret; }
} BIT;

struct Query { long long l; long long r; int zr; int id; } query[N];
struct Segment { long long x; long long y; int zy; long long t; } seg[N];
vector<Query> A[2];
vector<Segment> B[2];
int n, m;
long long res[N];
vector<long long> z;

void solve(vector<Query> &queries, vector<Segment> &segments) {
    z.clear();
    for (auto &e : queries) z.push_back(e.r);
    for (auto &e : segments) z.push_back(e.y);
    sort(z.begin(), z.end());
    z.erase(unique(z.begin(), z.end()), z.end());
    
    for (auto &e : queries) e.zr = lower_bound(z.begin(), z.end(), e.r) - z.begin() + 1;
    for (auto &e : segments) e.zy = lower_bound(z.begin(), z.end(), e.y) - z.begin() + 1;

    // solve
    sort(queries.begin(), queries.end(), [&](Query p, Query q) {
        return p.l < q.l || (p.l == q.l && p.r < q.r);
    });
    sort(segments.begin(), segments.end(), [&](Segment p, Segment q) {
        return p.x < q.x || (p.x == q.x && p.y < q.y);
    });
    for (auto &e : queries) {
        res[e.id] = e.r - e.l;
    }

    // x <= l
    BIT.reset();
    int ptr = 0;
    for (auto &e : queries) {
        while(ptr < segments.size() && segments[ptr].x <= e.l) {
            auto c = segments[ptr];
            BIT.upd_rig(c.zy, c.t - c.x - c.y);
            BIT.upd_lef(c.zy, c.t - c.x + c.y);
            ++ptr;
        }
        res[e.id] = min(res[e.id], e.l + e.r + BIT.get_lef(e.zr));
        res[e.id] = min(res[e.id], e.l - e.r + BIT.get_rig(e.zr));
    }

    // x >= l
    BIT.reset();
    ptr = segments.size() - 1;
    for (int i = queries.size() - 1; i >= 0; --i) {
        auto e = queries[i];
        while(ptr >= 0 && segments[ptr].x >= e.l) {
            auto c = segments[ptr];
            BIT.upd_rig(c.zy, c.t + c.x - c.y);
            BIT.upd_lef(c.zy, c.t + c.x + c.y);
            --ptr;
        }
        res[e.id] = min(res[e.id], -e.l + e.r + BIT.get_lef(e.zr));
        res[e.id] = min(res[e.id], -e.l - e.r + BIT.get_rig(e.zr));
    }
}

int main() {
    freopen("slingshot.in", "r", stdin);
    freopen("slingshot.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> seg[i].x >> seg[i].y >> seg[i].t;
        if (seg[i].x < seg[i].y) {
            B[0].push_back(seg[i]);
        } else {
            seg[i].x = 1e9 - seg[i].x;
            seg[i].y = 1e9 - seg[i].y;
            B[1].push_back(seg[i]);
        }
    }
    for (int i = 0; i < m; ++i) {
        cin >> query[i].l >> query[i].r;
        query[i].id = i;

        if (query[i].l < query[i].r) {
            A[0].push_back(query[i]);
        } else {
            query[i].l = 1e9 - query[i].l;
            query[i].r = 1e9 - query[i].r;
            A[1].push_back(query[i]);
        }
    }

    solve(A[0], B[0]);
    solve(A[1], B[1]);

    for (int i = 0; i < m; ++i) {
        printf("%lld\n", res[i]);
    }
}