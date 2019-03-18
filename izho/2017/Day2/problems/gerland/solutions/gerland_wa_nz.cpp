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
int t[sz * 2], add[sz * 2];


void upd(int v, int tl, int tr, int l, int r, int x) {
  if (r < tl || tr < l) return;
  if (l <= tl && tr <= r) {
    add[v] += x;
    return;
  }
  int m = (tl + tr) >> 1;
  upd(v + v, tl, m, l, r, x);
  upd(v + v + 1, m + 1, tr, l, r, x);
}

int get(int v, int tl, int tr, int p) {
  if (tl == tr) {
    return add[v];
  }
  int m = (tl + tr) >> 1;
  if (p <= m)
    return add[v] + get(v + v, tl, m, p);
  return add[v] + get(v + v + 1, m + 1, tr, p);
}

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
        int x = min(a[i - 1], a[i]), y = max(a[i - 1], a[i]);
        upd(1, 1, 100000, x, y, 1);
      }
    }
    for (int i = 1; i <= m; i++) {
      cin >> T;
      if (T == 1) {
        cin >> v >> x;
        if (v > 1)
          upd(1, 1, 1000000, L(a[v - 1], a[v]), R(a[v], a[v - 1]), -1);
        if (v < n)
          upd(1, 1, 1000000, L(a[v + 1], a[v]), R(a[v], a[v + 1]), -1);
        a[v] = x;
        if (v > 1)
          upd(1, 1, 1000000, L(a[v - 1], a[v]), R(a[v], a[v - 1]), +1);
        if (v < n)
          upd(1, 1, 1000000, L(a[v + 1], a[v]), R(a[v], a[v + 1]), +1);
      }
      if (T == 2) {
        cin >> x;
        cout << get(1, 1, 1000000, x) << "\n";
      }
    }
}

