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

const int INF = 1e9, N = 20010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m, num[N], low[N], Time, nChild[N], cnt;
vector <vi> G, Child;
ll ans;
bool criticalPt[N];
vi curComponent;

void dfs(int u, int p) {
	cout << "dfs: " << u << "\n";
	cnt++; curComponent.pb(u);
	nChild[u] = 0; int nChildren = 0; 
	num[u] = low[u] = ++Time;
	fo(i, 0, G[u].size()) {
		int v = G[u][i];
		if (v == p) continue;
		if (num[v]) low[u] = min(low[u], num[v]);
		else { Child[u].pb(v); dfs(v, u); nChildren++; nChild[u] += (nChild[v] + 1); low[u] = min(low[u], low[v]); }
		if ((u == p && nChildren >= 2) || (u != p && low[v] >= num[u])) criticalPt[u] = 1;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m; G.assign(n + 1, vi()); Child.assign(n + 1, vi());
	while(m--) { int u, v; cin >> u >> v; G[u].pb(v); G[v].pb(u); }
	ff(i, 1, n) if (!num[i]) {
		curComponent.clear(); cnt = 0; dfs(i, i); 
		fo(i, 0, curComponent.size()) {
			int u = curComponent[i];
			if (criticalPt[u]) {
				cout << u << ' ' << "is a critical point!\n";
				ans += 1LL * (cnt - nChild[u] - 1) * nChild[u];
				fo(i, 0, Child[u].size() - 1) {
					fo(j, i + 1, Child[u].size()) {
						ans += 1LL * (nChild[Child[u][i]] + 1) * (nChild[Child[u][j]] + 1);
					}
				}
			}
		}
		cout << "ans = " << ans << "\n";
	}
	printf("%.2lf\n", (double)ans / n);
}