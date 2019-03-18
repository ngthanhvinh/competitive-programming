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
#define sz 1000 * 1000
#define EPS (1e-8)
#define INF ((int)1e9 + 9)
#define mp make_pair

int n, m, v, t, x, a[sz];

int main()
{
    freopen(fname"in", "r", stdin);
    freopen(fname"out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= m; i++) {
      cin >> t;
      if (t == 1) {
        cin >> v >> x;
        a[v] = x;
      }
      if (t == 2) {
        cin >> x;
        int res = 0;
        for (int j = 1; j < n; j++) {
          if (min(a[j], a[j + 1]) <= x && x <= max(a[j], a[j + 1])) res++;
        }
        cout << res << "\n";
      }
    }
}
