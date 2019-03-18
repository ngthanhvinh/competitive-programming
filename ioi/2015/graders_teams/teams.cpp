#include "teams.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

int n;
int cntRig[N];
vector <int> lef[N];
int ver[N];

#define mid ((l + r) >> 1)
struct PersistentIT {
	int T[N * 30], L[N * 30], R[N * 30], peak;

	int build(int l, int r) {
		if (l == r) {
			++peak; L[peak] = R[peak] = peak; return peak;
		}
		int u = ++peak;
		L[u] = build(l, mid);
		R[u] = build(mid + 1, r);
		return u;
	}	
	
	int upd(int v, int l, int r, int x, int val) { // a[x] += val
		if (r < x || l > x) return v;
		if (l == r) {
			++peak; T[peak] = T[v] + val; L[peak] = R[peak] = peak; return peak;
		}
		int u = ++peak;
		L[u] = upd(L[v], l, mid, x, val);
		R[u] = upd(R[v], mid + 1, r, x, val);
		T[u] = T[L[u]] + T[R[u]];
		//printf("u = %d l = %d r = %d -> leftchild = %d rightchild = %d => T = %d\n", u, l, r, L[u], R[u], T[u]);
		return u;
	}
} pit;

struct IT {
	int T[N << 2];
	int lz[N << 2];

	IT() {
		memset(T, 0, sizeof T);
		memset(lz, -1, sizeof lz);
	}

	void push(int v, int l, int r) {
		if (lz[v] == -1) return;
		if (l < r) lz[v << 1] = lz[v], lz[v << 1 | 1] = lz[v];
		T[v] = lz[v] * (r - l + 1);
		lz[v] = -1;
	}

	void upd(int v, int l, int r, int L, int R, int val) { // [L...R] -> val
		push(v, l, r);
		if (R < l || L > r) return;
		if (L <= l && r <= R) {
			lz[v] = val; push(v, l, r); return;
		}
		upd(v << 1, l, mid, L, R, val);
		upd(v << 1 | 1, mid + 1, r, L, R, val);
		T[v] = T[v << 1] + T[v << 1 | 1];
	}
} it;

// --------------------------------

void init(int _n, int A[], int B[]) {
	n = _n;
	for (int i = 0; i < n; ++i) {
		cntRig[B[i]]++;
		lef[A[i]].push_back(B[i]);
	}
	pit.build(1, n);
	ver[0] = 1;
	for (int i = 1; i <= n; ++i) {
		ver[i] = ver[i - 1];
		if (cntRig[i - 1]) {
			ver[i] = pit.upd(ver[i], 1, n, i - 1, -cntRig[i - 1]); // delete
		}
		for (auto &j : lef[i]) {
			ver[i] = pit.upd(ver[i], 1, n, j, +1); // add
		}
	}
}

int find(int u, int v, int w, int l, int r, int leftmost, int rightmost, int &gap) { 
	// u, v: two different versions in PIT (u: ver[s[i]], v: ver[s[i - 1]])
	// w: current node in IT
	it.push(w, l, r);
	if (r < leftmost || l > rightmost) return 0;
	if (l >= leftmost) {
		if (l == r) {
			if (pit.T[u] - pit.T[v] + it.T[w] >= gap) {
				gap -= (pit.T[u] - pit.T[v] + it.T[w]);
				return l;
			}
		}
		if (pit.T[u] - pit.T[v] + it.T[w] < gap) {
			gap -= (pit.T[u] - pit.T[v] + it.T[w]);
			return 0;
		}
	}

	int ret = find(pit.L[u], pit.L[v], w << 1, l, mid, leftmost, rightmost, gap);
	if (!ret) {
		return find(pit.R[u], pit.R[v], w << 1 | 1, mid + 1, r, leftmost, rightmost, gap);
	}
	else return ret;
}

pair<int,int> t[200005];
int can(int m, int sz[]) {
	sort(sz, sz + m);
	int k = 0;
	for (int i = 0; i < m; ++i) {
		if (i > 0 && sz[i] == sz[i - 1]) {
			t[k].second += sz[i];
		} else {
			t[++k] = {sz[i], sz[i]};
		}
	}
	m = k;

	int last = 0;
	for (int i = 1; i <= m; ++i) {
		int pos = find(ver[t[i].first], ver[t[i - 1].first], 1, 1, n, t[i].first, last, t[i].second);
		if (!pos) {
			pos = find(ver[t[i].first], 0, 1, 1, n, last + 1, n, t[i].second);
		}
		if (!pos) {
			it.upd(1, 1, n, 1, n, 0);
			return false;
		}

		it.upd(1, 1, n, 1, pos, 0); // all 0s
		it.upd(1, 1, n, pos, pos, -t[i].second); // -t[i].second = rem
		last = pos;
	}

	it.upd(1, 1, n, 1, n, 0);
	return true;
}
