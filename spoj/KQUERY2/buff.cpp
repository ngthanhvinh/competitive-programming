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

int n, a[N], q;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("answer.txt", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin >> n; ff(i, 1, n) cin >> a[i];
	cin >> q;
	while(q--) {
		int type; cin >> type;
		if (!type) {
			int pos, val; cin >> pos >> val; a[pos] = val;
		}
		else {
			int ans = 0;
			int l, r, k; cin >> l >> r >> k; ff(i, l, r) if (a[i] > k) ans++;
			printf("%d\n", ans);
		}
	}
}