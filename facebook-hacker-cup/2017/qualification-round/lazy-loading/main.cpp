#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 110;

int n, w[N];
int Case;

bool check(int x) {
    int res = 0;
    for (int i = n - x + 1; i <= n; ++i) if (50 % w[i] == 0) res += 50 / w[i] - 1; else res += 50 / w[i];
    return res <= n - x;
}

void solve() {
    cin >> n; for (int i = 1; i <= n; ++i) cin >> w[i];
    sort(w + 1, w + n + 1);
    int l = 1, r = n;
    while(l != r) {
        int mid = ((l + r + 1) >> 1);
        if (!check(mid)) r = mid - 1;
        else l = mid;
    }
    printf("Case #%d: %d\n", ++Case, l);
}

int main() {
//    freopen("lazy_loading.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--)
        solve();
}
