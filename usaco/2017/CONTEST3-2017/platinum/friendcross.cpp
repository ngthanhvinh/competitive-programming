#include <bits/stdc++.h>
using namespace std;

const int N = 100010, S = 510;
int n, k, a[N], b[N], pos[N], pz[N], w[N];
long long ans;

struct BIT {
    int sz; vector <int> t;
    BIT(int sz=0): sz(sz) { t.assign(sz + 1, 0); }
    void upd(int x, int v) { for (; x <= sz; x += x & -x) t[x] += v; }
    int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res += t[x]; return res; }
} tr[N / S + 10];
vector <int> z[N / S + 10];

void upd(int x) { int bl = x / S; w[x] = b[x]; tr[bl].upd(pz[x], 1); }
int get(int l, int r, int val) {
    if (l > r) return 0;
    int res = 0;
    if (l / S == r / S) for (int i = l; i <= r; ++i) res += (w[i] && w[i] < val);
    else {
        int bl = l / S, br = r / S;
        for (int i = l; i < (bl + 1) * S; ++i) res += (w[i] && w[i] < val);
        for (int i = r; i >= br * S; --i) res += (w[i] && w[i] < val);
        for (int i = bl + 1; i <= br - 1; ++i) {
            int p = lower_bound(z[i].begin(), z[i].end(), val) - z[i].begin();
            res += tr[i].get(p);
        }
    }
    return res;
}

void solve() {
    memset(w, 0, sizeof w);
    for (int i = 0; i < n; ++i) pos[b[i]] = i;
    for (int bl = 0; bl <= (n - 1) / S; ++bl) {
        z[bl].clear();
        int l = bl * S, r = min(n - 1, (bl + 1) * S - 1);
        for (int i = l; i <= r; ++i) z[bl].push_back(b[i]);
        sort(z[bl].begin(), z[bl].end());
        for (int i = l; i <= r; ++i) pz[i] = lower_bound(z[bl].begin(), z[bl].end(), b[i]) - z[bl].begin() + 1;
        tr[bl] = BIT(z[bl].size());
    }

    for (int i = 0; i < n; ++i) {
        int cur = pos[a[i]];
        ans += get(cur + 1, n, a[i] - k);
        upd(cur);
    }

}

int main() {
    freopen("friendcross.in", "r", stdin);
    freopen("friendcross.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    solve();
    for (int i = 0; i < n; ++i) swap(a[i], b[i]);
    solve();

    cout << ans << endl;
    /*
    ans = 0;
    for (int i = 0; i < n; ++i) pos[b[i]] = i;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) if (pos[a[i]] < pos[a[j]] && abs(a[i] - a[j]) > k) ++ans;
    }
    cout << ans << endl;
    */
}
