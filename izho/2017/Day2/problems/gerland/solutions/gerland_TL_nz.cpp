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
#define L(xx, yy) min((xx), (yy))
#define R(xx, yy) max((xx), (yy))

int n, m, v, T, x, a[sz];
multiset <PII> S;

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
        S.insert(mp(L(a[i - 1], a[i]), R(a[i - 1], a[i])));
      }
    }
    for (int i = 1; i <= m; i++) {
      cin >> T;
      if (T == 1) {
        cin >> v >> x;
        if (v > 1)
          S.erase(S.find(mp(L(a[v - 1], a[v]), R(a[v - 1], a[v]))));
        if (v < n)
          S.erase(S.find(mp(L(a[v + 1], a[v]), R(a[v], a[v + 1]))));
        a[v] = x;
        if (v > 1)
          S.insert(mp(L(a[v - 1], a[v]), R(a[v - 1], a[v])));
        if (v < n)
          S.insert(mp(L(a[v], a[v + 1]), R(a[v], a[v + 1])));
      }
      if (T == 2) {
        cin >> x;
        int res = 0;
        multiset <PII> :: iterator it = S.lower_bound(mp(x, 0));
        while (1) {
          if (it != S.end())
            res += (*it).F <= x && x <= (*it).S;
          if (it == S.begin()) break;
          it--;
        }
        cout << res << "\n";
      }
    }
}
