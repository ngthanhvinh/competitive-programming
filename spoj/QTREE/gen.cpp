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

int n;
string query[] = {"QUERY", "CHANGE"};

int main() {
	freopen("input.txt", "w", stdout); srand(time(NULL));
	ios_base::sync_with_stdio(false);
	int t = 20; cout << t << "\n\n";
	while(t--) {
		n = rand() % 10000 + 2;
		cout << n << "\n";
		ff(i, 2, n) {
			int par = rand() % (i - 1) + 1;
			cout << par << ' ' << i << ' ' << rand() % 1000000 + 1 << "\n";
		}
		int q = rand() % 100000 + 1;
		while(q--) {
			int stt = rand() % 2; string s = query[stt];
			if (s == "CHANGE") { cout << s << ' ' << rand() % (n - 1) + 1 << ' ' << rand() % 1000000 + 1 << "\n"; }
			else {
				int u = 0, v = 0; while(u == v) { u = rand() % n + 1, v = rand() % n + 1; }
				cout << s << ' ' << u << ' ' << v << "\n";
			}
		}
		cout << "DONE\n\n";
	}
}