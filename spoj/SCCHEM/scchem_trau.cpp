#include <bits/stdc++.h>
using namespace std;
typedef vector <int> vi;
const int N = 51;

int n, m, mx[N], my[N];
vector <vi> G;
char E[N][N];
int Case;

void solve() {
    cin >> n >> m; int ans = 0;
    for (int i = 0; i <= n-1; i++) for (int j = 0; j <= m-1; j++) cin >> E[i][j];
    for (int mask1 = 1; mask1 < (1 << n); mask1++) for (int mask2 = 1; mask2 < (1 << m); mask2++) {
        bool ok = 1;
        for (int i = 0; i < n; i++) if ((mask1 & (1 << i)) && ok) for (int j = 0; j < m; j++) if ((mask2 & (1 << j)) && ok) {
            if (E[i][j] == '0') { ok = 0; break; }
        }
        if (ok) ans = max(ans, __builtin_popcount(mask1) + __builtin_popcount(mask2));
    }
    printf("Case %d: %d\n", ++Case, ans + 1);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    freopen("scchem.inp", "r", stdin);
    freopen("scchem.ans", "w", stdout);
    int t; cin >> t;
    while(t--)
        solve();
}

