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

const int INF = 1e9, N = 100010, mod = 1e9 + 1;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int t = 10, n = 100000;

int main() {
	freopen("RGAME.in", "w", stdout);
	ios_base::sync_with_stdio(false);
	srand(time(NULL));
	cout << t << "\n";
	while(t--) {
		cout << n << "\n";
		ff(i, 0, n) cout << rand() % mod << " "; cout << "\n";
	}
}