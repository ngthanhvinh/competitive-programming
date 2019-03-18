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

int main() {
	freopen("input.txt", "w", stdout);
	ios_base::sync_with_stdio(false);
	int n = rand() % 100000 + 1, q = rand() % 100000 + 1;
	cout << n << ' ' << q << "\n";
	ff(i, 2, n) cout << rand() % (i - 1) + 1 << ' ' << i << "\n";
	while(q--) {
		int type = rand() % 2, x = rand() % n + 1;
		cout << type << ' ' << x << "\n";
	}  
}