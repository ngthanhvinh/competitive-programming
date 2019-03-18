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

int a[N], n, q;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("ans.txt", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin >> n >> q; ff(i, 1, n) cin >> a[i];
	sort(a + 1, a + n + 1);
	while(q--) {
		string type; cin >> type;
		if (type == "XOR") {
			int x; cin >> x;
			ff(i, 1, n) a[i] ^= x;
			sort(a + 1, a + n + 1);
		}
		else {
			int k; cin >> k; k = n + 1 - k;
			cout << a[k] << "\n";
		}
	}
}