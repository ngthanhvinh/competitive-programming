#include <bits/stdc++.h>
using namespace std;

const int N = 50005;

struct SegmentTree {
	long long T[N << 2];
	multiset <long long> s[N];
	SegmentTree() { for (int i = 0; i < (N << 2); ++i) T[i] = inf; }

	void upd(int v, int l, int r, int x, int val) {
		if (l > r || l > x || r < x) return;
		if (l == r) { T[v] = val; return; }
		upd(v << 1, l, mid, x, val); upd(v << 1 | 1, mid + 1, r, x, val);
		T[v] = min(T[v << 1], T[v << 1 | 1]);
	}

	void add(int v, int l, int r, int x, int val) {
		if (l > r || l > r || r < x) return;
		if (l == r) { s[l].insert(val); T[v] = min(T[v], val); return; }
		add(v << 1, l, mid, x, val); upd(v << 1 | 1, mid + 1, r, x, val);
		T[v] = min(T[v << 1], T[v << 1 | 1]);
	}

	void del(int v, int l, int r, int x, int val) {
		if (l > r || l > r || r < x) return;
		if (l == r) {
			multiset<long long>::iterator iter = s[l].find(val);
			s[l].erase(iter);
			if (s[l].empty()) T[v] = inf; else T[v] = (*s[l].begin());
			return;
		}
		del(v << 1, l, mid, x, val); del(v << 1 | 1, mid + 1, r, x, val);
		T[v] = min(T[v << 1], T[v << 1 | 1]);
	}

	long long get(int v, int l, int r, int L, int R) {
		if (l > r || R < l || L > r) return inf;
		if (L <= l && r <= R) return T[v];
		return min(get(v << 1, l, mid, L, R), get(v << 1 | 1, mid + 1, r, L, R));
	}
} tr;	

int n;
int h[N];
long long ans[N];

void solve() {

}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> h[i];

	long long prv = 0;
	for (int i = 2; i <= n; ++i) prv += abs(h[i] - h[i-1]);
	for (int i = 1; i <= n; ++i) ans[i] = prv;
	// 1
	for (int i = 2; i <= n; ++i) {
		long long cur = prv;
		prv -= abs(h[1] - h[2]);
		prv -= abs(h[i] - h[i-1]);
	}

	solve();
	for (int i = 1; i <= n; ++i) h[i] = -h[i];
	solve();

	
}