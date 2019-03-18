#include <bits/stdc++.h>
using namespace std;

const int N = 100020;

int T[N * 80], L[N * 80], R[N * 80];
int add;
int n, m;
vector < pair<int,int> > Z;
vector <int> val;
int ver[N];

#define mid ((l + r) >> 1)
void build(int v, int l, int r) {
	if (l > r) return;
	if (l == r) { T[v] = 0; L[v] = R[v] = v; return; }
	L[v] = ++add; R[v] = ++add; T[v] = 0;
	build(L[v], l, mid); build(R[v], mid + 1, r);
}

int upd(int v, int l, int r, int x) {
	if (l > r || x < l || r < x) return v;
	if (l == r) { ++add; T[add] = 1; L[add] = R[add] = add; return add; }
	int u = ++add;
	L[u] = upd(L[v], l, mid, x), R[u] = upd(R[v], mid + 1, r, x);
	T[u] = T[L[u]] + T[R[u]];
	return u;
}

int get(int v, int l, int r, int i, int j) {
	if (l > r || l > j || r < i) return 0;
	if (i <= l && r <= j) return T[v];
	return get(L[v], l, mid, i, j) + get(R[v], mid + 1, r, i, j);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) { int x; cin >> x; Z.push_back(make_pair(x, i)); }
	sort(Z.begin(), Z.end());
	add = 1; build(1, 1, n);
	ver[0] = 1;

	for (int i = 0; i < (int)Z.size(); ++i) {
		int j = i;
		while(j < (int)Z.size() && Z[j].first == Z[i].first) ++j; --j;
		val.push_back(j);

		while(i <= j) {
			ver[i + 1] = upd(ver[i], 1, n, Z[i].second);
			//cerr << i << ' ' << ver[i+1] << endl;
			++i;
		}
		--i;
	}

	while(m--) {
		int l, r, k; cin >> l >> r >> k;
		int lo = 0, hi = val.size() - 1;
		while(lo < hi) {
			int mi = ((lo + hi) >> 1);
			if (get(ver[val[mi] + 1], 1, n, l, r) >= k) hi = mi; else lo = mi + 1;
		}
		printf("%d\n", Z[val[lo]].first);
	}
}