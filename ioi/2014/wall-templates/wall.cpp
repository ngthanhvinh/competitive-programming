#include "wall.h"
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

const int N = 2000005;

// SEGMENT TREE
int mn[N << 2];
int mx[N << 2];
int lz[N << 2];
int segpos[N];
#define mid ((l + r) >> 1)

void build(int v, int l, int r) {
	mn[v] = 0;
	mx[v] = 0;
	lz[v] = -1;
	if (l == r) {
		segpos[l] = v;
		return;
	}
	build(v << 1, l, mid);
	build(v << 1 | 1, mid + 1, r);
}

void push(int v, int l, int r) {
	if (lz[v] == -1) return;
	if (l < r) lz[v << 1] = lz[v], lz[v << 1 | 1] = lz[v];
	mn[v] = mx[v] = lz[v];
	lz[v] = -1;
}

void upd(int v, int l, int r, int L, int R, int val) {
	push(v, l, r);
	if (R < l || L > r) return;
	if (L <= l && r <= R) {
		lz[v] = val; push(v, l, r); return;
	}
	upd(v << 1, l, mid, L, R, val);
	upd(v << 1 | 1, mid + 1, r, L, R, val);
	mx[v] = max(mx[v << 1], mx[v << 1 | 1]);
	mn[v] = min(mn[v << 1], mn[v << 1 | 1]);
}

int find_smaller(int v, int l, int r, int leftmost, int h) {
	// find the smallest i >= leftmost s.t. a[i] < h
	push(v, l, r);
	if (r < leftmost) return N;
	if (l >= leftmost) {
		if (l == r) {
			if (mn[v] < h) return l;
			else return N;
		}
		if (mn[v] >= h) return N;
	}

	int gl = find_smaller(v << 1, l, mid, leftmost, h);
	if (gl != N) return gl;
	else return find_smaller(v << 1 | 1, mid + 1, r, leftmost, h);
}

int find_greater(int v, int l, int r, int leftmost, int h) {
	// find the smallest i >= leftmost s.t. a[i] > h
	push(v, l, r);
	if (r < leftmost) return N;
	if (l >= leftmost) {
		if (l == r) {
			if (mx[v] > h) return l;
			else return N;
		}
		if (mx[v] <= h) return N;
	}

	int gl = find_greater(v << 1, l, mid, leftmost, h);
	if (gl != N) return gl;
	else return find_greater(v << 1 | 1, mid + 1, r, leftmost, h);
}

void final(int v, int l, int r) {
	push(v, l, r);
	if (l == r) return;
	final(v << 1, l, mid);
	final(v << 1 | 1, mid + 1, r);
}

#undef mid

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	build(1, 0, n - 1);

	for (int i = 0; i < k; ++i) {
		if (op[i] == 1) { // add
			int pos = left[i];
			while(pos <= right[i]) {
				int posl = find_smaller(1, 0, n - 1, pos, height[i]);
				if (posl == N) break;
				int posr = find_greater(1, 0, n - 1, posl, height[i]);
				posr = min(posr - 1, right[i]);

				upd(1, 0, n - 1, posl, posr, height[i]);
				pos = posr + 1;
			}
		} else { // remove
			int pos = left[i];
			while(pos <= right[i]) {
				int posl = find_greater(1, 0, n - 1, pos, height[i]);
				if (posl == N) break;
				int posr = find_smaller(1, 0, n - 1, posl, height[i]);
				posr = min(posr - 1, right[i]);

				upd(1, 0, n - 1, posl, posr, height[i]);
				pos = posr + 1;
			}
		}
	}

	final(1, 0, n - 1);
	for (int i = 0; i < n; ++i) {
		finalHeight[i] = mn[segpos[i]];
	}
}

