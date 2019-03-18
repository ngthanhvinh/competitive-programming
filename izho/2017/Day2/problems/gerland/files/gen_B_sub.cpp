//Solution by Zhusupov Nurlan
#include <bits/stdc++.h>
#include "testlib.h"

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
#define fname ""
#define sz 1000 * 1000
#define EPS (1e-8)
#define INF ((int)1e9 + 9)
#define mp make_pair

int n, m, was[sz*2];

int main(int argc, char* argv[])
{
//    freopen(fname"in", "r", stdin);
//    freopen(fname"out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    registerGen(argc, argv, 1);
    n = m = 1e5;
    int L = atoi(argv[1]);
    int R = atoi(argv[2]);

    cout << n << " " << m << "\n";
    for (int i = 1; i <= n; i++) {
      int x;
      cout << (x = rnd.next(L, R));
      was[x] = 1;
      if (i < n) cout << " ";
    }
    cout << "\n";
    for (int i = 1; i <= n; i++) {
        int x;
        while (was[x = rnd.next(max(1, L - 1), min(R + 1, int(1e6)))]);
      cout << 2 << " " << x << "\n";
    }


}
