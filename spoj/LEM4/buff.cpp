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

int n, m, a[N];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("ans.txt", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin >> n >> m;
	while(m--) {
		int type; cin >> type;
		if (type != 3) { int u, v; cin >> u >> v; ff(i, u, v) a[i] = type - 1; }
		else {
			int ans = 0, cnt = 0;
			ff(i, 1, n) {
				if (a[i] == 0) cnt++;
				else { ans = max(ans, cnt); cnt = 0; } 
			}
			ans = max(ans, cnt);
			printf("%d\n", ans);
		}
	} 
}