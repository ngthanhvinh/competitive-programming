#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int MAGIC = 150;
const int INF = 1e9;

int n, m, q;
vector <int> g[N], rev[N];
int res[N];
vector < pair<int,int> > s[N];

int f[N];
bool check[N];
vector <int> vec[N];
vector <int> queries_id[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> m >> q;
	while(m--) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		rev[v].push_back(u);
	}

	for (int i = 0; i < q; ++i) {
		res[i] = -INF;
		int t, y; cin >> t >> y;
		for (int j = 0; j < y; ++j) {
			int k; cin >> k;
			vec[i].push_back(k);
		}

		if (y >= MAGIC) {
			for (int &pos : vec[i]) check[pos] = true;

			f[t] = 0;
			int mx = -INF;
			if (!check[t]) mx = 0;
			for (int pos = t - 1; pos >= 1; --pos) {
				f[pos] = -INF;
				for (int &j : g[pos]) {
					if (j <= t) f[pos] = max(f[pos], f[j] + 1);
					if (!check[pos]) mx = max(mx, f[pos]);
				}
			}

			res[i] = mx;
			for (int &pos : vec[i]) check[pos] = false;
		}
		else {
			queries_id[t].push_back(i);
		}
	}

	// solve small queries
	vector < pair<int,int> > buf;
	for (int t = 1; t <= n; ++t) {
		vector< pair<int,int> > cur; // candidates
		cur.push_back(make_pair(0, t));
		for (int &i : rev[t]) {
			for (auto &j : s[i]) {
				cur.push_back(make_pair(j.first + 1, j.second));
			}
		}
		sort(cur.begin(), cur.end());
		
		int ptr = cur.size() - 1;
		int taken = 0;

		// choose the largest candidates (up to MAGIC elements)
		while(ptr >= 0 && taken < MAGIC) {
			if (!check[cur[ptr].second]) {
				check[cur[ptr].second] = true;
				++taken;
				s[t].push_back(cur[ptr]);
			}
			--ptr;
		}
		for (auto &j : s[t]) check[j.second] = false;
		reverse(s[t].begin(), s[t].end());

		// answer queries
		for (int i = 0; i < queries_id[t].size(); ++i) {
			int id = queries_id[t][i];
			for (int &j : vec[id]) check[j] = true;

			while(!s[t].empty()) {
				auto j = s[t].back();
				if (check[j.second]) {
					buf.push_back(j);
					s[t].pop_back();
				} else {
					res[id] = j.first;
					break;
				}
			}

			while(buf.size()) s[t].push_back(buf.back()), buf.pop_back();
			for (int &j : vec[id]) check[j] = false;		
		}
	}

	for (int i = 0; i < q; ++i) {
		printf("%d\n", res[i] < 0 ? -1 : res[i]);
	}
}