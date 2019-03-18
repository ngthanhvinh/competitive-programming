#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 100010;

int n, q, a[N];

int main() {
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q; for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    while(q--) {
        int l, r; cin >> l >> r;
        int L = lower_bound(a + 1, a + n + 1, l) - a;
        int R = upper_bound(a + 1, a + n + 1, r) - a;
        cout << R - L << endl;
    }
}
