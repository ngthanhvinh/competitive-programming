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

const int INF = 1e9, N = 260;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef pair <ii, ii> II;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, vis[N], match[N], t, cnt; 
II a[N];
bool type[N];
// 0 horizontal (d): y = a
// 1 vertical   (d): x = a 
vector <vi> G;

void process() {
	cin >> n; G.assign(n + 1, vi());
	ff(i, 1, n) {
		cin >> a[i].fi.fi >> a[i].fi.se >> a[i].se.fi >> a[i].se.se;
		if (a[i].fi.fi == a[i].se.fi) type[i] = 1;
		else type[i] = 0;
	}
	ff(i, 1, n) ff(j, 1, n) {
		if (type[i] && !type[j]) 
			if (1LL * (a[j].fi.se - a[i].fi.se) * (a[i].se.se - a[j].fi.se) >= 0 && 
			1LL * (a[i].fi.fi - a[j].fi.fi) * (a[j].se.fi - a[i].fi.fi) >= 0) G[i].pb(j); // intersect (xi, yj) 
	}
}

bool dfs(int u) {
	if (vis[u] != t) vis[u] = t;
	else return 0;
	fo(i, 0, G[u].size()) {
		int v = G[u][i];
		if (!match[v] || dfs(match[v])) { match[v] = u; return 1; }
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	process();
	/*
	ff(i, 1, n) {
		if (!type[i]) continue;
		cout << "line: " << i << "th\n";
		cout << "intersects with lines: ";
		fo(j, 0, G[i].size()) cout << G[i][j] << ' '; cout << "\n";
	}
	*/
	ff(i, 1, n) {
		if (!type[i]) continue;
		t++;
		cnt += dfs(i);
	}
	printf("%d\n", n - cnt);
}