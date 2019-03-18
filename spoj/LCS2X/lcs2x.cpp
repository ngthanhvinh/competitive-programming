#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1510;
int n, m, a[N], b[N], f[N][N];

struct BIT {
    int sz; vector <int> t;
    BIT(int sz=0): sz(sz) { t.assign(sz + 10, 0); }
    void upd(int x, int v) { for (; x <= sz; x += x & -x) t[x] = max(t[x], v); }
    int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res = max(res, t[x]); return res; }
} tr[N];

vector <int> z;

void solve() {
    cin >> n >> m; z.clear();
    for (int i = 1; i <= n; ++i) cin >> a[i], z.push_back(a[i]);
    for (int i = 1; i <= m; ++i) cin >> b[i];

    sort(z.begin(), z.end());
    z.resize(distance(z.begin(), unique(z.begin(), z.end())));

    int ans = 0;

    for (int i = 0; i <= m; ++i) tr[i] = BIT(z.size());

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            f[i][j] = f[i][j-1];
            if (a[i] == b[j]) {
                f[i][j] = max(f[i][j], tr[j-1].get(upper_bound(z.begin(), z.end(), a[i]/2) - z.begin()) + 1);
            }
            ans = max(ans, f[i][j]);
            //cerr << i << ' ' << j << ' ' << f[i][j] << endl;
        }
        for (int j = 1; j <= m; ++j) tr[j].upd(lower_bound(z.begin(), z.end(), a[i]) - z.begin() + 1, f[i][j]);
    }

    printf("%d\n", ans);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--)
        solve();
}
