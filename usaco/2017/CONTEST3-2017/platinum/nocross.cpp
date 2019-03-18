#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int n, a[N], b[N];
int t[N];
int pos[N];
int ans;

void upd(int x, int v) { for (; x <= n; x += x & -x) t[x] = max(t[x], v); }
int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res = max(res, t[x]); return res; }

int main() {
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 1; i <= n; ++i) pos[b[i]] = i;

    for (int i = 1; i <= n; ++i) {
        vector <int> p;
        for (int j = max(1, a[i] - 4); j <= min(n, a[i] + 4); ++j) p.push_back(pos[j]);
        sort(p.begin(), p.end(), greater<int>());
        for (int j = 0; j < p.size(); ++j) {
            int dp = get(p[j] - 1) + 1;
            upd(p[j], dp);
            ans = max(ans, dp);
        }
    }

    cout << ans << endl;
}
