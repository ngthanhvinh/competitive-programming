#include <bits/stdc++.h>
using namespace std;
#define ff(i, a, b) for (int i = a; i <= b; i++)
const int N = 100010;
int n, k, cur;
int w[N];
long long f[N][11], s[N], t[N];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("ans.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k; ff(i, 1, n) cin >> w[i], s[i] = s[i - 1] + i * w[i], t[i] = t[i - 1] + w[i];
    ff(i, 1, n) ff(j, 0, 10) f[i][j] = 1e13;

    ff(cnt, 1, k) ff(i, 1, n) {
        ff(j, 0, i-1) {
            f[i][cnt] = min(f[i][cnt], (s[i] - t[i]) - j * t[i] + (f[j][cnt-1] - s[j] + (j + 1) * t[j]));
        }
        //cout << i << ' ' << cnt << ' ' << f[i][cnt] << "\n";
    }
    cout << f[n][k] << "\n";
}
