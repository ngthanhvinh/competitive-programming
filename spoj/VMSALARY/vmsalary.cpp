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

int n, par[N], c[N], nChild[N], s[N], cur, T[N];
vector <vi> children;
vii salary;
ll ans;

void dfs(int u) {
	++cur; s[u] = cur;
	fo(i, 0, children[u].size()) {
		int v = children[u][i];
		dfs(v); nChild[u] += nChild[v];
	}
	nChild[u]++;
}

void upd(int x) { for(; x <= n; x += x & -x) T[x]++; }
int get(int x) { int res = 0; for(; x > 0; x -= x & -x) res += T[x]; return res; } 

int main() {
	//freopen("test.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin >> n >> c[1]; salary.pb(ii(c[1], 1)); children.assign(n + 1, vi());
	ff(i, 2, n) cin >> par[i] >> c[i], children[par[i]].pb(i), salary.pb(ii(c[i], i)); 
	dfs(1);
	sort(salary.begin(), salary.end());
	int i = 0;
	while(i < salary.size()) {
		cur = salary[i].fi; int j = i;
		while(j < salary.size() && salary[j].fi == cur) {
			int u = salary[j].se;
			int res = get(s[u] + nChild[u] - 1) - get(s[u]);
			++j;
			if (res < 2) continue;
			ans += (1LL * res * (res - 1)) / 2;
		}
		ff(k, i, j - 1) upd(s[salary[k].se]);
		i = j;
	}	
	printf("%lld\n", ans);
} 