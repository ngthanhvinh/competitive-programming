#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n;
int color[N];
vector < pair<int,int> > g[N];
vector < pair<int,int> > p;

void dfs(int u) {
	for (auto &e : g[u]) {
		int v = e.first;
		int i = e.second;
		if (color[v] != -1) {
			assert(color[v] == color[u] ^ i);
			continue; // always valid
		} else {
			color[v] = color[u] ^ i;
			dfs(v);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int l, r; cin >> l >> r;
		p.push_back(make_pair(l, i));
		p.push_back(make_pair(r, -i));
	}

	sort(p.begin(), p.end());

	int c = 0; // cnt
	long long res = 0;

	for (int i = 0; i < (int)p.size() - 1; ++i) {
		c += (p[i].second > 0) ? +1 : -1;
		res += 1LL * (c / 2) * (c - c / 2) * (p[i + 1].first - p[i].first);
		if (i % 2 == 0) {
			int s = (p[i].second > 0) ? +1 : -1;
			int t = (p[i + 1].second > 0) ? +1 : -1;

			if (s * t > 0) { // different color
				g[abs(p[i].second)].push_back(make_pair(abs(p[i + 1].second), 1));
				g[abs(p[i + 1].second)].push_back(make_pair(abs(p[i].second), 1));
			} else { // same color
				g[abs(p[i].second)].push_back(make_pair(abs(p[i + 1].second), 0));
				g[abs(p[i + 1].second)].push_back(make_pair(abs(p[i].second), 0));
			}

		}
	}

	printf("%lld\n", res);
	// bipartite coloring
	memset(color, -1, sizeof color);
	for (int i = 1; i <= n; ++i) {
		if (color[i] == -1) {
			color[i] = 0;
			dfs(i);
		}
	}
	for (int i = 1; i <= n; ++i) {
		printf("%d ", color[i]);
	}
	printf("\n");
}