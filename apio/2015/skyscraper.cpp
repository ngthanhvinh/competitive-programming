#include <bits/stdc++.h>
using namespace std;

const int N = 30005;
const int inf = 1e9;

int n, m;
int b[N], p[N];
vector<int> G[N], a[N];
vector< pair<int,int> > imp;
int *f[N];
int pt[N], *le[N], *ri[N];

int pos(int val, int d) {
	int it = lower_bound(G[d].begin(), G[d].end(), val) - G[d].begin();
	assert(G[d][it] == val);
	return it;
} 

int bfs() {
	for (int i = 1; i < N; ++i) {
		f[i] = new int[G[i].size()];
		for (int j = 0; j < G[i].size(); ++j) f[i][j] = inf;
	}

	deque < pair<int,int> > q;
	f[p[0]][pos(b[0], p[0])] = 0; 
	q.push_back(make_pair(p[0], pos(b[0], p[0])));
	
	while(!q.empty()) {
		int d = q.front().first, x = q.front().second; q.pop_front();
		int cur = f[d][x];
		int realX = G[d][x];
		if (realX == b[1]) return cur;

		if (le[d][x] > -1) {
			if (f[d][le[d][x]] == inf) f[d][le[d][x]] = cur + 1, q.push_back(make_pair(d, le[d][x]));
		}
		if (ri[d][x] < G[d].size()) {
			if (f[d][ri[d][x]] == inf) f[d][ri[d][x]] = cur + 1, q.push_back(make_pair(d, ri[d][x]));
		}
		while(!a[realX].empty()) {
			int new_d = a[realX].back(); a[realX].pop_back();
			int new_pos = pos(realX, new_d);
			if (f[new_d][new_pos] == inf) {
				f[new_d][new_pos] = cur;
				q.push_front(make_pair(new_d, new_pos));
			}
		}
	}

	return -1;
}

void reset(int d, int val) { for (int u : G[d]) pt[u % d] = val; }

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		cin >> b[i] >> p[i];
		imp.push_back(make_pair(p[i], b[i] % p[i]));
		a[b[i]].push_back(p[i]);
	}
	sort(imp.begin(), imp.end());
	imp.resize(distance(imp.begin(), unique(imp.begin(), imp.end())));

	for (auto &it : imp) {
		int d = it.first, mod = it.second;
		for (int i = mod; i < n; i += d) {
			G[d].push_back(i);
		}
	}

	for (int i = 1; i < N; ++i) {
		sort(G[i].begin(), G[i].end());
		le[i] = new int[G[i].size()];
		ri[i] = new int[G[i].size()];

		reset(i, -1);
		for (int j = 0; j < G[i].size(); ++j) {
			int cur = G[i][j]; le[i][j] = pt[cur % i]; pt[cur % i] = j;
		}

		reset(i, G[i].size());
		for (int j = G[i].size() - 1; j >= 0; --j) {
			int cur = G[i][j]; ri[i][j] = pt[cur % i]; pt[cur % i] = j;
		}
	}

	printf("%d\n", bfs());
}