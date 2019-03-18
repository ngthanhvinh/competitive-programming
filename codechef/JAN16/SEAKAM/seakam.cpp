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

const int INF = 1e9, N = 100010, mod = 1e9 + 7;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m, pos[N], num, cnt;
int f[N], dp[1 << 14];
vector <vi> G; vii cond;
vi par, child, vis;
bool check;

void Factorial() { f[0] = 1; fo(i, 1, N) f[i] = (1LL * f[i - 1] * i) % mod; }

void dfs(int u) {
	vis[u] = 1; num++;
	if (!child[u]) return;
	if (!vis[child[u]]) return dfs(child[u]); else check = 0;
}	

int main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	Factorial();
	int test; cin >> test;
	while(test--) {
		cin >> n >> m; memset(dp, 0, sizeof dp); memset(pos, 0, sizeof pos);
		cond.clear(); int c = 0, ans = 0;
		ff(i, 1, m) {
			int u, v; cin >> u >> v;
			cond.pb(ii(u, v)); cond.pb(ii(v, u));
			if (!pos[u]) pos[u] = ++c; if (!pos[v]) pos[v] = ++c;
		}
		fo(mask, 0, 1 << (2 * m)) {
			if (__builtin_popcount(mask) > m) continue;
			check = 1; cnt = 0, num = 0; // dp[mask]
			par.assign(c + 1, 0); child.assign(c + 1, 0); vis.assign(c + 1, 0);
			vector <bool> used(c + 1, 0);
			ff(i, 1, c) par[i] = i;
			fo(i, 0, 2 * m) {
				if (!(mask & (1<<i))) continue;
				ii cur = cond[i]; int u = pos[cur.fi], v = pos[cur.se];
				if (par[v] == v && !child[u]) { par[v] = u; child[u] = v; used[u] = used[v] = 1; }
				else check = 0;
			}
			if (!check) continue;
			
			ff(i, 1, c) {
				if (!check) break;
				if (par[i] == i && used[i] && !vis[i]) { cnt++; dfs(i); }
			}
			if (!check) continue;

			ff(i, 1, c) {
				if (par[i] != i && used[i] && !vis[i]) { check = 0; break; }
			}
			if (!check) continue;
			num = n - num;
			dp[mask] = f[num];
			ff(i, 1, cnt) {
				dp[mask] = (1LL * dp[mask] * (num + 1)) % mod;
				num++;
			}
		}	
		//dp[0] = f[n];
		fo(mask, 1, 1 << (2 * m)) {
			if (__builtin_popcount(mask) & 1) ans = (ans + dp[mask]) % mod;
			else ans = (ans - dp[mask]) % mod;
		}
		ans = (dp[0] - ans) % mod;
		if (ans < 0) ans += mod;
		printf("%d\n", ans);
		
	}
}
