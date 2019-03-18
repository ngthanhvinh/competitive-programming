#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int n, a[N], b[N];
int x[N], pos[N];
int t[N];
long long ans = 1e18;

void upd(int x, int v) { for (; x <= n; x += x & -x) t[x] += v; }
int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res += t[x]; return res; }

void solve() {
    memset(t, 0, sizeof t);
    long long inv = 0;
    for (int i = 1; i <= n; ++i) pos[a[i]] = i; for (int i = 1; i <= n; ++i) x[pos[b[i]]] = i;
    for (int i = n; i >= 1; --i) inv += get(x[i]), upd(x[i], 1);
    ans = min(ans, inv);
    for (int i = n; i >= 2; --i) {
        inv -= (n - x[i]); inv += (x[i] - 1);
        //cerr << inv << endl;
        ans = min(ans, inv);
    }
}

int main() {
    freopen("mincross.in", "r", stdin);
    freopen("mincross.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    solve();
    for (int i = 1; i <= n; ++i) swap(a[i], b[i]);
    solve();
    cout << ans << endl;
}
