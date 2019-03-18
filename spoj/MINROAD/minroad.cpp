#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 300010;
typedef pair<int,int> ii;

ii x[N];
int n, a, b;
int sa[N], sb[N];
int ans = 1e9 + 123;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> a >> b;
    for (int i = 1; i <= n; ++i) cin >> x[i].first >> x[i].second;
    sort(x + 1, x + n + 1);
    for (int i = 1; i <= n; ++i) sa[i] = sa[i-1] + (x[i].second == 1), sb[i] = sb[i-1] + (x[i].second == 2);

    for (int i = 1; i <= n; ++i) {
        int l = 1, r = i;
        while(l != r) {
            int mid = ((l + r + 1) >> 1);
            if (sa[i] - sa[mid - 1] >= a) l = mid; else r = mid - 1;
        }
        int ptra = l;
        l = 1, r = i;
        while(l != r) {
            int mid = ((l + r + 1) >> 1);
            if (sb[i] - sb[mid - 1] >= b) l = mid;  else r = mid - 1;
        }
        int ptrb = l;
        if (sa[i] - sa[ptra-1] < a || sb[i] - sb[ptrb-1] < b) continue;
        ptra = min(ptra, ptrb);
        ans = min(ans, x[i].first - x[ptra].first);
    }
    if (ans != 1e9 + 123) cout << ans << endl; else cout << -1 << endl;
}
