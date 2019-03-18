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

int n, m;

int main(int argc, char* argv[])
{
//    freopen(fname"in", "r", stdin);
//    freopen(fname"out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    registerGen(argc, argv, 1);
    int n = m = atoi(argv[1]);
    cout << n << " " << m << "\n";
    for (int i = 1; i <= n; i++) {
      if (i & 1) cout << 1;
        else cout << 1000000;
      if (i < n) cout << " ";
    }
    cout << "\n";
    for (int i = 1; i <= n; i++) {
      cout << 2 << " " << rnd.next(2, 1000000 - 1) << "\n";
    }


}
