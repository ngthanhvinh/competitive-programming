#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1000010;
const long long INF = 1e18;

int n, p, q, x, y;
string s;
int pre[N], suf[N], sum[N];
long long ans = INF;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> p >> q >> x >> y;
    cin >> s; s = ' ' + s;
    p = -p; q = q + p;
    for (int i = 1; i <= n; ++i) sum[i] = sum[i-1] + (s[i] == '+' ? 1 : -1);
    for (int i = 1; i <= n; ++i) pre[i] = min(pre[i-1], sum[i]);
    suf[n+1] = 1e9; for (int i = n; i >= 1; --i) suf[i] = min(suf[i+1] + (s[i] == '+' ? 1 : -1), sum[n] - sum[i-1]);

    for (int i = 1; i <= n; ++i) {
        long long res = 0; int curSum = sum[n]; res += 1ll * (n-i) * y;
        int need = max(0, max(p - (sum[n] - sum[i] + pre[i]), p - suf[i]));
        need += need % 2; need /= 2; curSum += need * 2;
        need += abs(curSum - q) / 2; res += 1ll * x * need;
        ans = min(ans, res);
    }

    cout << ans << endl;
}
