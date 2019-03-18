#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, c[N];
vector < pair<int,int> > ed;
vector <int> z; // compression
vector <int> g[N];
int skip[N], par[N], dep[N], nchild[N];

struct data {
	int low; int cnt; int val;
	bool operator < (const data &other) const {
		return low < other.low;
	}
};
deque <data> dq[N]; // (lowest_depth, cnt, val)

void dfs(int u) {
	nchild[u] = 1;
	skip[u] = u;
	for (int &v : g[u]) {
		dep[v] = dep[u] + 1;
		par[v] = u;
		dfs(v);
		nchild[u] += nchild[v];
	}
}

void hld(int u) {
	for (int &v : g[u]) {
		if (nchild[v] * 2 >= nchild[u]) {
			skip[v] = skip[u];
		}
		hld(v);
	}
}

// -----------------------------------------------
// BIT
int T[N];
void upd(int x, int v) { for (; x < N; x += x & -x) T[x] += v; }
int get(int x) { int ret = 0; for (; x > 0; x -= x & -x) ret += T[x]; return ret; }

vector < pair<int,int> > buf;
long long calc_inv(int u) {
	long long ret = 0;

	while(u) {
		int root = skip[u];
		assert(dq[root].size() > 0);
		int pos = upper_bound(dq[root].begin(), dq[root].end(), data({dep[u], 0, 0})) - dq[root].begin() - 1;

		int curdep = dep[u];
		while(pos >= 0) {
			int curcnt = curdep - dq[root][pos].low + 1;
			// get
			ret += 1LL * curcnt * get(dq[root][pos].val - 1);
			// update the current segment to BIT
			upd(dq[root][pos].val, curcnt);
			buf.push_back(make_pair(dq[root][pos].val, curcnt));
			// -> new position
			curdep = dq[root][pos].low - 1;
			--pos;
		}

		u = par[skip[u]];
	}

	// reset
	while(buf.size()) {
		int x = buf.back().first, v = buf.back().second;
		upd(x, -v);
		buf.pop_back();
	}

	return ret;
}

void add(int u) {
	int val = c[u];

	// climb up
	while(u) { // par[1] = 0
		int curdep = dep[u];
		int cnt = 0;
		while(dq[skip[u]].size() > 1 && dq[skip[u]][1].low <= curdep) {
			cnt += dq[skip[u]].front().cnt;
			dq[skip[u]].pop_front();
		}
		if (dq[skip[u]].size()) {
			cnt += curdep - dq[skip[u]][0].low + 1;
			dq[skip[u]][0].cnt -= curdep - dq[skip[u]][0].low + 1;
			dq[skip[u]][0].low = curdep + 1;
			if (dq[skip[u]][0].cnt <= 0) {
				dq[skip[u]].pop_front();
			}
		} else {
			cnt = 1;
		}

		dq[skip[u]].push_front({dep[skip[u]], cnt, val});
		u = par[skip[u]];
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> c[i];
		z.push_back(c[i]);
	}
	sort(z.begin(), z.end());
	z.erase(unique(z.begin(), z.end()), z.end());

	for (int i = 1; i <= n; ++i) {
		c[i] = lower_bound(z.begin(), z.end(), c[i]) - z.begin() + 1;
	}

	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		ed.push_back(make_pair(u, v));
		g[u].push_back(v);
	}	

	// solve
	dfs(1);
	hld(1);
	dq[1].push_back({0, 1, c[1]});

	for (auto &e : ed) {
		int u = e.first, v = e.second;
		printf("%lld\n", calc_inv(u));
		add(v);
	}
}