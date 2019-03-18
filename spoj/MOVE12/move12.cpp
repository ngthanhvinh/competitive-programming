#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <deque>
#include <queue>
#include <utility>

//#include "segment_tree.h"
//#include "fenwick_tree.h"
//#include "union_find.h"
//#include "geometry.h"
using namespace std;

#define FOR(i,a,b) for(int i = (a); i <= (b); i++)
#define DOW(i,a,b) for(int i = (a); i >= (b); i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; ++i)
#define FORI(it, x) for (__typeof((x).begin()) it = (x).begin(); it != (x).end(); it++)
#define RESET(c,val) memset(c,val,sizeof(c))

#define ALL(x) x.begin(), x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())

#define sz(a) int(a.size())
#define pb push_back
#define mp make_pair
#define fi first
#define se second

// bitmask
#define isOn(S, j) (S & (1 << j))
#define setBit(S, j) (S |= (1 << j))
#define clearBit(S, j) (S &= ~(1 << j))
#define toggleBit(S, j) (S ^= (1 << j))
#define lowBit(S) (S & (-S))
#define setAll(S, n) (S = (1 << n) - 1)

// other manipulation
#define modulo(S, N) ((S) & (N - 1)) // return S % N, where N = 2^k
#define isPowerOfTwo(S) (!(S & (S - 1))
#define nearestPowerOfTwo(S) ((int)pow(2.0, (int)((log((double)S) / log(2.0)) + 0.5)))
#define turnOffLastBit(S) ((S) & (S-1))
#define turnOnLastZero(S) ((S) | (S+1))
#define turnOffLastConsecutiveBits(S) ((S) & (S + 1))
#define turnOnLastConsecutiveZeroes(S) ((S) & (S - 1))


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;

/*---------------------------*/

const int MAXN = 1e4 + 5;

int n, c[MAXN], t[MAXN];
pair< int, int > a[MAXN];
multiset<int> rset;

bool ok(int res) {
    rset.clear();
    FOR(i,1,n) {
        a[i].fi = max(1, c[i] - res / t[i]);
        a[i].se = min(n, c[i] + res / t[i]);
    }

    sort(a + 1, a + n + 1);
    int p = 1;
    FOR(i,1,n) {
        while(p <= n && a[p].fi <= i) rset.insert(a[p++].se);
        if (rset.empty() || *rset.begin() < i) return 0;
        rset.erase(rset.begin());
    }
    return 1;
}

int main() {

    cin >> n;
    FOR(i,1,n) cin >> c[i] >> t[i];
    int l = 0;
    int r = 1e8 + 1;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (ok(m)) r = m - 1;
        else l = m + 1;
    }
    if (ok(l)) cout << l;
    else cout << r;

    return 0;
}
