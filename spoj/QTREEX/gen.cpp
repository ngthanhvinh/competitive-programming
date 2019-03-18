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

const int INF = 1e9, N = 10010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, q, par[N]; 
const string query[] = {"QUERY", "CHANGE", "NEGATE"};

void genTest() {
	n = rand() % 10000 + 2;
	cout << n << endl;
	ff(i, 2, n) par[i] = rand() % (i - 1) + 1, cout << par[i] << ' ' << i << ' ' << rand() % 100 + 1 << endl;
	q = rand() % 50000 + 1;
	
	while(q--) {
		string s = query[rand() % 3]; cout << s << ' ';

		if (s == "QUERY" || s == "NEGATE") {
			int u = 0, v = 0; while(u == v) { u = rand() % n + 1, v = rand() % n + 1; }
			cout << u << ' ' << v << endl;
		}	
		
		else {
			int pos = rand() % (n - 1) + 1; 
			int cost = 10000;
			cout << pos << ' ' << cost << '\n';
		}
		
	}
	cout << "DONE\n\n";
}

int main() {
	freopen("input.txt", "w", stdout);
	ios_base::sync_with_stdio(false); srand(time(NULL));
	int t = 20; cout << t << "\n\n";
	while(t--) {
		genTest();
	}
}