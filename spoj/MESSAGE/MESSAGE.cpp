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

const int INF = 1e9, N = 810;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m, num[N], low[N], cnt, Time, pos[N], par[N];
stack <int> st;
vector <vi> G;

void dfs(int u) {
	num[u] = low[u] = ++Time;
	st.push(u);
	fo(i, 0, G[u].size()) {
		int v = G[u][i];
		if (num[v]) low[u] = min(low[u], num[v]);
		else { dfs(v); low[u] = min(low[u], low[v]); }
	}
	if (num[u] == low[u]) {
		cnt++; int v;
		do {
			v = st.top(); st.pop();
			pos[v] = cnt; //cout << v << ' ';
			num[v] = low[v] = INF;
		} while(v != u);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m; G.assign(n + 1, vi());
	while(m--) {
		int u, v; cin >> u >> v;
		G[u].pb(v);
	}
	ff(i, 1, n) if (!num[i]) dfs(i);
	//cout << cnt << "\n";
	//ff(i, 1, n) cout << i << ' ' << pos[i] << "\n";
	ff(i, 1, n) fo(j, 0, G[i].size()) if (pos[i] != pos[G[i][j]]) par[pos[G[i][j]]] = pos[i];
	int ans = 0;
	//ff(i, 1, cnt) cout << i << ' ' << par[i] << "\n";
	ff(i, 1, cnt) if (!par[i]) ans++;
	printf("%d\n", ans); 
}