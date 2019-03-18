#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int INF = 1e9;
typedef pair<int,int> ii;

int n, q, a[N];
int bigger[N];
vector <int> segL[N], segR[N];
vector <ii> seg[N];

struct segment {
    int l; int r; int val;
    bool operator < (const segment &other) const {
        return val < other.val;
    }
};
vector <segment> new_seg;

void die() {
    for (int i = 1; i <= n; ++i) printf("-1 "); printf("\n");
    exit(0);
}

// SEGMENT TREE
#define mid ((l + r) >> 1)
ii T[N << 2];

void build(int v, int l, int r) {
    if (l == r) { T[v] = make_pair(bigger[l], l); return; }
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
    T[v] = min(T[v << 1], T[v << 1 | 1]);
}

void upd(int v, int l, int r, int pos, int val) {
    if (pos < l || pos > r) return;
    if (l == r) { T[v] = make_pair(val, pos); return; }
    upd(v << 1, l, mid, pos, val);
    upd(v << 1 | 1, mid + 1, r, pos, val);
    T[v] = min(T[v << 1], T[v << 1 | 1]);
}

ii get(int v, int l, int r, int L, int R) {
    if (R < l || L > r) return ii(INF, -1);
    if (L <= l && r <= R) return T[v];
    return min(get(v << 1, l, mid, L, R), get(v << 1 | 1, mid + 1, r, L, R));
}
#undef mid
// END OF SEGMENT TREE

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= q; ++i) {
        int l, r, minval; cin >> l >> r >> minval;
        seg[minval].push_back(make_pair(l, r));
        segL[l].push_back(minval);
        segR[r + 1].push_back(minval);
    }

    for (int val = 0; val < n; ++val) if (seg[val].size()) {
        // find the intersection of all segments in {seg[val]}
        int maxL = -INF;
        int minR = INF;
        for (auto &e : seg[val]) {
            maxL = max(maxL, e.first);
            minR = min(minR, e.second);
        }
    
        if (maxL > minR) die();

        new_seg.push_back({maxL, minR, val});
    }

    sort(new_seg.begin(), new_seg.end()); // by val

    // build the array
    for (int i = 0; i < n; ++i) a[i] = -1; // init

    // find bigger[]
    multiset<int> s;
    for (int i = 0; i < n; ++i) {
        for (int &j : segR[i]) {
            multiset<int>::iterator iter = s.find(j);
            s.erase(iter);
        }
        for (int &j : segL[i]) s.insert(j);

        if (!s.empty()) {
            set<int>::iterator iter = s.end();
            --iter;
            bigger[i] = (*iter); 
        }// else bigger[i] = 0;
    }

    build(1, 0, n - 1);

    for (auto &e : new_seg) {
        ii g = get(1, 0, n - 1, e.l, e.r);
        if (g.first > e.val) die();

        a[g.second] = e.val;
        upd(1, 0, n - 1, g.second, INF);
    }

    // remaining elements
    vector <int> cand;
    vector <int> rem;
    vector <bool> check(n, false);
    for (int i = 0; i < n; ++i) 
        if (a[i] != -1) check[a[i]] = true;
        else rem.push_back(i);
    for (int i = 0; i < n; ++i) 
        if (!check[i]) cand.push_back(i);
    sort(rem.begin(), rem.end(), [&](int x, int y) {
        return bigger[x] < bigger[y];
    });

    assert(rem.size() == cand.size());
    for (int i = 0; i < rem.size(); ++i) {
        if (bigger[rem[i]] > cand[i]) die();
        a[rem[i]] = cand[i];
    }

    // print
    for (int i = 0; i < n; ++i) printf("%d ", a[i]); printf("\n");
}