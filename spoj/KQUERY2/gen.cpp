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

int n, q, a[N]; 

int main() {
	freopen("input.txt", "w", stdout);
	ios_base::sync_with_stdio(false); srand(time(NULL));
	n = rand() % 100 + 1;
	cout << n << endl;
	ff(i, 1, n) cout << rand() % 1000 + 1 << ' '; cout << endl;
	q = rand() % 1000 + 1;
	cout << q << endl;
	while(q--) {
		int type = rand() % 2; cout << type << ' ';
		if (!type) {
			int pos = rand() % n + 1, val = rand() % 1000 + 1;
			cout << pos << ' ' << val << endl;
		}
		else {
			int l = rand() % n + 1, r = rand() % n + 1;
			if (l > r) swap(l, r); cout << l << ' ' << r << ' ';
			int k = rand() % 100 + 1; cout << k << endl;
		}
	}
}	