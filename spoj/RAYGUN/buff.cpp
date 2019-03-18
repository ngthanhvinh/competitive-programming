#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define ff(i, a, b) for(int i = a; i <= b; i++)
#define fo(i, a, b) for(int i = a; i < b; i++)
#define fod(i, a, b) for(int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

const int INF = 1e9, N = 100010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("ans.txt", "w", stdout);
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for (int Case = 1; Case <= t; ++Case) {
		cin >> n >> m;
		int cnt = 0;
		ff(i, 0, n) ff(j, 0, m) if (__gcd(i, j) == 1) cnt++;
		printf("Case %d: %d\n", Case, cnt);
	}
}