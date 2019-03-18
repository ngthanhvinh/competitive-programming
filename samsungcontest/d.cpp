#include <bits/stdc++.h>
using namespace std;

int n, m;
int perm[105];
bool e[105][105];
vector < pair<int,int> > ed;

int get(vector<int> &p) {
	int ret = 0;
	for (auto &e : ed) {
		ret += abs(p[e.first] - p[e.second]);
	}
	return ret;
}

void solve() {
	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			e[i][j] = false;
		}
	}

	ed.clear();
	while(m--) {
		int u, v; cin >> u >> v;
		ed.push_back(make_pair(u, v));
		e[u][v] = e[v][u] = true;
	}

	vector <int> vp(n, 0);
	vector <int> p(n, 0);
	for (int i = 0; i < n; ++i) vp[i] = p[i] = i;
	int res = 1e9;

	if (n < 9) {
		do {
			int cur = get(p);
			if (res > cur) {
				vp = p;
				res = cur;
			}
		} while(next_permutation(p.begin(), p.end()));
	}

	else {
		int NTIME = 300;
		res = get(p);

		while(NTIME--) {
			int tmp = res;

			int u = rand() % n;
			vector <int> r;
			for (int i = 0; i < n; ++i) r.push_back(i);
			random_shuffle(r.begin(), r.end());

			int cnt = 80;
			int bestv = -1;
			for (int &v : r) {
				if (cnt == 0) break;
				// swap u and v
				int cur = tmp;
				for (int i = 0; i < n; ++i) if (e[u][i] && v != i) {
					cur += abs(p[v] - p[i]) - abs(p[u] - p[i]);
				}
				for (int i = 0; i < n; ++i) if (e[v][i] && u != i) {
					cur += abs(p[u] - p[i]) - abs(p[v] - p[i]);
				}

				if (res > cur) {
					bestv = v;
					res = cur;
				}
				--cnt;
			}

			if (bestv != -1) {
				swap(p[u], p[bestv]);
			}
		}

		vp = p;
	}

	cout << res << endl;
	for (int i = 0; i < n; ++i) {
		perm[vp[i]] = i;
	}
	for (int i = 0; i < n; ++i) {
		cout << perm[i] << ' ';
	}
	cout << endl;
}

int main() {
	srand(1997);
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int ntest; cin >> ntest;
	for (int itest = 1; itest <= ntest; ++itest) {
		cout << "Case #" << itest << endl;
		solve();
	}
}