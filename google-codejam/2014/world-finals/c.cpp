#include <bits/stdc++.h>
using namespace std;

const int N = 10005;
int n, color[N];
vector<int> G[N];

map < pair<int,int>, int > mhash;
map < vector<int>, int > mv;
map < pair<int,int>, bool > mok;
bool symmetric;

int get_hash(int u, int p) {
	if (mhash.find(make_pair(u, p)) != mhash.end()) {
		return mhash[make_pair(u, p)];
	}
	// naive hashes
	vector<int> hashes;
	hashes.push_back(color[u]);
	for (int v : G[u]) {
		if (v != p) hashes.push_back(get_hash(v, u));
	}
	sort(hashes.begin(), hashes.end());

	if (mv.find(hashes) != mv.end()) return mv[hashes];
	else {
		int ret = mv.size();
		mv[hashes] = ret;
		return ret;
	}
}

bool ok(int u, int p) {
	if (mok.find(make_pair(u, p)) != mok.end()) {
		return mok[make_pair(u, p)];
	}
	vector< pair<int,int> > hashes;
	for (int v : G[u]) if (v != p)
		hashes.push_back(make_pair(get_hash(v, u), v));

	sort(hashes.begin(), hashes.end());
	int sz = hashes.size();
	// u has only two children which are located on the symmetric line

	bool ret = true;
	if (sz % 2 == 0) {
		for (int i = 0; i < sz; i += 2) 
			if (hashes[i].first != hashes[i + 1].first) ret = false;
	} else {
		int i = 0;
		while(i + 1 < sz && hashes[i].first == hashes[i + 1].first) i += 2;
		for (int j = i + 1; j < sz; j += 2) {
			if (hashes[j].first != hashes[j + 1].first) ret = false;
		}
		if (ret) {
			ret = ok(hashes[i].second, u);
		}
	}
	mok[make_pair(u, p)] = ret;
	return ret;
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) G[i].clear();
	for (int i = 1; i <= n; ++i) {
		char ch; cin >> ch; color[i] = ch - 'A';
	}
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		G[u].push_back(v); G[v].push_back(u);
	}
		
	mhash.clear();
	mv.clear();
	mok.clear();
	symmetric = false;
	for (int i = 1; i <= n; ++i) {
		if (symmetric) break;
		for (int j : G[i]) if (get_hash(i, j) == get_hash(j, i)) { symmetric = true; break; }
	}
	if (!symmetric) {
		for (int i = 1; i <= n; ++i) {
			if (symmetric) break;
			if (ok(i, -1)) symmetric = true;
		}
	}
	if (symmetric) printf("SYMMETRIC\n");
	else printf("NOT SYMMETRIC\n");
}

int main() {
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int tc = 1; tc <= tt; ++tc) {
		printf("Case #%d: ", tc);
		solve();
		fprintf(stderr, "test %d solved\n");
	}
}