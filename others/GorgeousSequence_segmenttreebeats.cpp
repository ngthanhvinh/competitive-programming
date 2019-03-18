// http://acm.hdu.edu.cn/showproblem.php?pid=5306

#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int n, nquery, a[N];
// for Segment Tree
int max_val[N << 2], second_val[N << 2], cnt_max[N << 2];
long long sum[N << 2];
int lz[N << 2];

#define mid ((l + r) >> 1)

void merge(int v) {
    int le = (v << 1), ri = (v << 1 | 1);
    if (max_val[le] < max_val[ri]) swap(le, ri);

    if (max_val[le] == max_val[ri]) {
        max_val[v] = max_val[le]; cnt_max[v] = cnt_max[le] + cnt_max[ri];
        second_val[v] = max(second_val[le], second_val[ri]);
    } else {
        max_val[v] = max_val[le]; cnt_max[v] = cnt_max[le];
        second_val[v] = max(second_val[le], max_val[ri]);
    }
    sum[v] = sum[le] + sum[ri];
}

void build(int v, int l, int r) {
    if (l == r) {
        max_val[v] = a[l]; cnt_max[v] = 1;
        second_val[v] = -1; 
        sum[v] = a[l];
        lz[v] = -1;
        return;
    }
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
    merge(v);
    lz[v] = -1;
}

void push(int v, int l, int r) {
    if (lz[v] == -1) return;
    if (l < r) {
        if (lz[v << 1] == -1) lz[v << 1] = lz[v]; else lz[v << 1] = min(lz[v << 1], lz[v]);
        if (lz[v << 1 | 1] == -1) lz[v << 1 | 1] = lz[v]; else lz[v << 1 | 1] = min(lz[v << 1 | 1], lz[v]);
    }
    if (lz[v] < max_val[v]) {
        sum[v] -= 1LL * cnt_max[v] * max_val[v];
        max_val[v] = lz[v]; 
        sum[v] += 1LL * cnt_max[v] * max_val[v];
    }
    lz[v] = -1;
}

void upd(int v, int l, int r, int L, int R, int val) {
    push(v, l, r);
    if (R < l || L > r || max_val[v] < val) return;
    if (L <= l && r <= R && second_val[v] < val) {
        lz[v] = val; push(v, l, r); return;
    }
    upd(v << 1, l, mid, L, R, val);
    upd(v << 1 | 1, mid + 1, r, L, R, val);
    merge(v);
    //printf("l = %d r = %d max_val = %d second_val = %d cnt_max = %d sum = %lld\n", l, r, max_val[v], second_val[v], cnt_max[v], sum[v]);
}

int get_max(int v, int l, int r, int L, int R) {
    push(v, l, r);
    if (R < l || L > r) return -1;
    if (L <= l && r <= R) return max_val[v];
    return max(get_max(v << 1, l, mid, L, R), get_max(v << 1 | 1, mid + 1, r, L, R));
}

long long get_sum(int v, int l, int r, int L, int R) {
    push(v, l, r);
    if (R < l || L > r) return 0;
    if (L <= l && r <= R) return sum[v];
    return get_sum(v << 1, l, mid, L, R) + get_sum(v << 1 | 1, mid + 1, r, L, R);
}

#undef mid

void solve() {
    cin >> n >> nquery;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);

    while(nquery--) {
        int type; cin >> type;
        if (type == 0) {
            int l, r, val; cin >> l >> r >> val;
            upd(1, 1, n, l, r, val);
        } else if (type == 1) {
            int l, r; cin >> l >> r;
            printf("%d\n", get_max(1, 1, n, l, r));
        } else {
            int l, r; cin >> l >> r;
            printf("%lld\n", get_sum(1, 1, n, l, r));
        }
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    int tt; cin >> tt;
    while(tt--) {
        solve();
    }
}