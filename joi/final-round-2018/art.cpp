#include <bits/stdc++.h>
using namespace std;

const int N = 500005;
const long long inf = 1e18;
#define fi first
#define se second

int n;
pair<long long, int> a[N];
long long B[N];
long long ans;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].fi >> a[i].se;
    sort(a + 1, a + n + 1);

    for (int i = 1; i <= n; ++i) B[i] = B[i - 1] + a[i].se; // b
    
    long long mx = -inf;
    for (int i = n; i >= 1; --i) {
        mx = max(mx, B[i] - a[i].fi); // sumB[i] - A[i]
        ans = max(ans, mx - B[i - 1] + a[i].fi);
    }
    
    cout << ans << endl;
}