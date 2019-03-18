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

map <ii, bool> check;

int main() {
	freopen("input.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	srand(time(NULL));
	int test = 10; cout << test << "\n";
	while(test--) {
		int n, m;
		n = rand() % 100000 + 1, m = rand() % 8;
		cout << n << ' ' << m << "\n";
		check.clear(); 
		while(m--) {
			while(1) {
				int u = rand() % n + 1, v = rand() % n + 1;
				if (u == v) continue;
				if (check[ii(u, v)]) continue;
				else {
					check[ii(u, v)] = check[ii(v, u)] = 1;
					cout << u << ' ' << v << "\n";
					break;
				}
			}
		}
	}
}