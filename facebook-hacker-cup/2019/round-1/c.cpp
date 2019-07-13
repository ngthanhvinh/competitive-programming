#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 123;

// Max Flow template (NKFLOW)
typedef vector<int> vi;
struct MaxFlow {
	int n, src, snk, m;
	struct edge {
		int c; int f; int u; int v;
		edge(int u, int v, int c, int f): u (u), v (v), c (c), f (f) {}
	};
	vector <vi> G;
	vector <edge> e;
	MaxFlow(int n = 0, int src = 0, int snk = 0): n (n), src (src), snk (snk) { e.clear(); G.assign(n + 1, vi()); }
	void add(int u, int v, int c) {
		G[u].push_back(e.size()); e.push_back(edge(u, v, c, 0));
		G[v].push_back(e.size()); e.push_back(edge(v, u, 0, 0));
	}
	vector <int> d, head;
	bool bfs() {
		d.assign(n + 1, 0); head.assign(n + 1, 0); d[src] = INF;
		queue <int> q; q.push(src);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int id : G[u]) if (!d[e[id].v] && e[id].c > e[id].f) head[e[id].v] = id, d[e[id].v] = u, q.push(e[id].v);
		}
		return (d[snk] != 0);
	}
	int mxm() {
		int delta = INF, v = 0;
		for (int u = snk; u != src; u = d[u]) {
			int id = head[u];
			delta = min(delta, e[id].c - e[id].f);
		}
		for (int u = snk; u != src; u = d[u]) {
			int id = head[u];
			e[id].f += delta; e[id ^ 1].f -= delta;
		}
		return delta;
	}
	long long maxFlow() {
		long long r = 0;
		while (bfs()) r += mxm();
		return r;
	}
} mf;
// -------------------------------------------------------------

const int N = 205;

int n, h, x[N], a[N], b[N];
vector < pair<int, int> > vecSeg[N];

void solve() {
	cin >> n >> h;

	vector <int> zy;
	for (int i = 1; i <= n; ++i) {
		cin >> x[i] >> a[i] >> b[i];
		zy.push_back(a[i]);
		zy.push_back(b[i]);
	}
	zy.push_back(0);
	zy.push_back(h);
	sort(zy.begin(), zy.end());
	zy.erase(unique(zy.begin(), zy.end()), zy.end());

	int cntSeg = 0;
	vector < pair<int, int> > consecutive;

	for (int i = 1; i <= n; ++i) {
		int l = lower_bound(zy.begin(), zy.end(), a[i]) - zy.begin();
		int r = lower_bound(zy.begin(), zy.end(), b[i]) - zy.begin() - 1;
		for (int j = l; j <= r; ++j) {
			vecSeg[j].push_back({x[i], cntSeg + j - l + 1});
		}
		for (int j = l; j < r; ++j) {
			consecutive.push_back({cntSeg + j - l + 1, cntSeg + j - l + 2});
			consecutive.push_back({cntSeg + j - l + 2, cntSeg + j - l + 1});
		}
		cntSeg += r - l + 1;
	}

	// add vertically consecutive edges
	int s = cntSeg + 1, t = cntSeg + 2;
	mf = MaxFlow(cntSeg + 2, cntSeg + 1, cntSeg + 2);
	for (auto &p : consecutive) {
		mf.add(p.first, p.second, INF);
	}

	// add horizontally consecutive edges
	for (int i = 0; i + 1 < zy.size(); ++i) {
		int len = zy[i + 1] - zy[i];
		sort(vecSeg[i].begin(), vecSeg[i].end());
		for (int j = 0; j + 1 < vecSeg[i].size(); ++j) {
			mf.add(vecSeg[i][j].second, vecSeg[i][j + 1].second, len);
			mf.add(vecSeg[i][j + 1].second, vecSeg[i][j].second, len);
		}
	}

	// add edges from source and edges to sink
	for (auto &p : vecSeg[0]) {
		mf.add(s, p.second, INF);
	}
	for (auto &p : vecSeg[(int)zy.size() - 2]) {
		mf.add(p.second, t, INF);
	}

	long long res = mf.maxFlow();
	printf("%lld\n", res >= INF ? -1 : res);

	// reset
	for (int i = 0; i < zy.size(); ++i) {
		vecSeg[i].clear();
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		printf("Case #%d: ", it);
		solve();
	}
}