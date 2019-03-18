//Solution by Zhusupov Nurlan
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef map<string , int> MSI;
typedef vector<int> VI;
typedef pair<int, int> PII;

#define endl '\n'
#define pb(x) push_back(x)
#define sqr(x) ((x) * (x))
#define F first
#define S second
#define SZ(t) ((int) t.size())
#define len(t) ((int) t.length())
#define base LL(1e9 + 7)
#define fname "game."
#define sz 5000 * 1000
#define EPS (1e-8)
#define INF ((int)1e9 + 9)
#define mp make_pair

int n, m, v, t, x, ans[sz], cnt, cur, a[sz];
PII g[sz];

int main()
{
    freopen(fname"in", "r", stdin);
    freopen(fname"out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      if (i > 1) {
        g[++cnt] = mp(min(a[i], a[i - 1]), 0);
        g[++cnt] = mp(max(a[i], a[i - 1]), INF);
      }
    }

    for (int i = 1; i <= m; i++) {
      cin >> t;
      if (t == 2) {
        cin >> x;
        g[++cnt] = mp(x, i);
      }
    }

    sort(g + 1, g + 1 + cnt);

    for (int i = 1; i <= cnt; i++) {
      if (g[i].S == 0) cur++;
      if (g[i].S && g[i].S != INF) ans[g[i].S] = cur;
      if (g[i].S == INF) cur--;
    }

    for (int i = 1; i <= m; i++)
      cout << ans[i] << "\n";

}

