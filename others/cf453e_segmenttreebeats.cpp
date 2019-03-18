#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, q;
int start[N], max_mana[N], regen[N], need[N];
int minT[N << 2], maxT[N << 2], remS[N << 2], lz[N << 2];
vector< pair<int,int> > vneed[N << 2];
vector<long long> vm[N << 2], vr[N << 2];

#define mid ((l + r) >> 1)
void merge(int v) {
    minT[v] = min(minT[v << 1], minT[v << 1 | 1]);
    maxT[v] = max(maxT[v << 1], maxT[v << 1 | 1]);
    remS[v] = remS[v << 1] + remS[v << 1 | 1];
}

void build(int v, int l, int r) {
    vneed[v].push_back(make_pair(-1, 0));
    vm[v].push_back(0);
    vr[v].push_back(0);
    for (int i = l; i <= r; ++i) if (regen[i] != 0 && max_mana[i] != 0) {
        vneed[v].push_back(make_pair(need[i], i));
    }
    sort(vneed[v].begin(), vneed[v].end());
    for (int i = 1; i < vneed[v].size(); ++i) {
        vm[v].push_back(vm[v].back() + max_mana[vneed[v][i].second]);
        vr[v].push_back(vr[v].back() + regen[vneed[v][i].second]);
    }
    lz[v] = -1;

    if (l == r) {
        remS[v] = (start[l] > 0);
        return;
    }
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
    merge(v);
}

void push(int v, int l, int r) {
    if (lz[v] == -1) return;
    if (l < r) lz[v << 1] = lz[v], lz[v << 1 | 1] = lz[v];
    minT[v] = maxT[v] = lz[v];
    lz[v] = -1;
}

long long query(int v, int l, int r, int L, int R, int t) {
    push(v, l, r);
    if (R < l || L > r) return 0;
    if (L <= l && r <= R) {
        if (remS[v]) {
            if (l == r) {
                remS[v] = 0;
                minT[v] = maxT[v] = t;
                return min(1LL * regen[l] * t + start[l], (long long)max_mana[l]);
            }
        } else {
            if (minT[v] == maxT[v]) {
                int last = minT[v]; // = maxT[v]
                // last + need > t
                // <-> need > t - last
                int pos = upper_bound(vneed[v].begin(), vneed[v].end(), make_pair(t - last, N)) - vneed[v].begin(); // pos > 0
                long long ret = 1LL * (t - last) * (vr[v][vneed[v].size() - 1] - vr[v][pos - 1]) + vm[v][pos - 1];
                lz[v] = t;
                push(v, l, r);
                return ret;
            }
        }
    }
    long long lef = query(v << 1, l, mid, L, R, t);
    long long rig = query(v << 1 | 1, mid + 1, r, L, R, t);
    merge(v);
    return lef + rig;
}
#undef mid

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> start[i] >> max_mana[i] >> regen[i];
        if (regen[i]) need[i] = (max_mana[i] + regen[i] - 1) / regen[i];
    }
    build(1, 1, n);

    cin >> q;
    while(q--) {
        int t, l, r; cin >> t >> l >> r;
        printf("%lld\n", query(1, 1, n, l, r, t));
    }
}