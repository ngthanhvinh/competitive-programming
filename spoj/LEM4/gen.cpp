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
	freopen("input.txt", "w", stdout); 
	ios_base::sync_with_stdio(false); cin.tie(0); srand(time(NULL));
	n = 10; m = rand() % 20 + 1;
	cout << n << endl << m << endl;
	while(m--) {
		int type = rand() % 3 + 1;
		cout << type << ' ';
		if (type == 3) { cout << endl; continue; }	
		else { int u = rand() % n + 1, v = rand() % n + 1; if (u > v) swap(u, v); cout << u << ' ' << v << endl; }
	}
}