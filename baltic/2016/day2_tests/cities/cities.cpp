#include <bits/stdc++.h>
using namespace std;

const int N = 100005, K = 5;
const long long inf = 1e18;

long long f[N][1 << K];
int n, m, k;
int pos[N];

typedef pair<int,int> ii;
typedef pair<long long, ii> data;
#define fi first 
#define se second
vector<ii> G[N];
vector<int> ch[1 << K];

void dijkstra() {
	priority_queue < data, vector<data>, greater<data> > qu;
	for (int i = 1; i <= n; ++i) for (int mask = 0; mask < (1 << k); ++mask) f[i][mask] = inf;
	for (int i = 1; i <= n; ++i) {
		if (pos[i] == -1) f[i][0] = 0, qu.push(data(0, ii(i, 0))); 
		else f[i][1 << pos[i]] = 0, qu.push(data(0, ii(i, 1 << pos[i])));
	}
	while(!qu.empty()) {
		data T = qu.top(); qu.pop();
		int u = T.se.fi, mask = T.se.se; long long d = T.fi;
		if (d != f[u][mask]) continue;

		for (int i = 0; i < (int)ch[mask].size(); ++i) {
			int cmask = ch[mask][i];
			if ((mask & cmask) != cmask) continue;
			f[u][mask] = min(f[u][mask], f[u][cmask] + f[u][mask ^ cmask]);
		}
		d = f[u][mask];

		for (int i = 0; i < (int)G[u].size(); ++i) {
			int v = G[u][i].se, w = G[u][i].fi, nw = mask;
			if (pos[v] != -1) nw |= (1 << pos[v]);
			if (f[v][nw] > d + w) {
				f[v][nw] = d + w;
				qu.push(data(f[v][nw], ii(v, nw)));
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k >> m;
	memset(pos, -1, sizeof pos);
	for (int i = 1; i <= k; ++i) { int x; cin >> x; pos[x] = i - 1; }
	while(m--) {
		int u, v, w; cin >> u >> v >> w;
		G[u].push_back(make_pair(w, v));
		G[v].push_back(make_pair(w, u));
	} 
	for (int mask = 0; mask < (1 << k); ++mask) {
		for (int cmask = 0; cmask < mask; ++cmask) if ((mask & cmask) == cmask) {
			ch[mask].push_back(cmask);
		}
	}
	dijkstra();

	long long ans = inf;
	for (int i = 1; i <= n; ++i) ans = min(ans, f[i][(1 << k) - 1]);
	cout << ans << endl;
}