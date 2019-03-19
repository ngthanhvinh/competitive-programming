#include <iostream>
using namespace std;

const int N = 1000010;

int n, t, a[N];
long long ans;
long long s;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> t; for (int i = 1; i <= n; ++i) cin >> a[i];
    ans = 1LL * (t / 2 + 1) * a[1]; s = a[1];

    for (int i = 2; i <= min(n, t + 1); ++i) {
        s += a[i]; int nt = t - i + 1;
        ans = max(ans, s + 1LL * a[i - 1] * ((nt + 1) / 2) + 1LL * a[i] * (nt / 2));
    }

    cout << ans << endl;
}
