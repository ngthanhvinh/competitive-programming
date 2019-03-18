#include "game.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1505;

int n, par[MAXN], nver[MAXN], nedge[MAXN][MAXN];

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
bool join(int p, int q) {
	p = anc(p), q = anc(q);
	if (p == q) return false;

	if (nedge[p][q] + 1 == nver[p] * nver[q]) {
		for (int i = 0; i < n; ++i) {
			nedge[q][i] += nedge[p][i];
			nedge[i][q] += nedge[p][i];
		}
		par[p] = q;
		nver[q] += nver[p];
		return true;
	} else {
		++nedge[p][q];
		++nedge[q][p];
		return false;
	}
}

void initialize(int N) {
	n = N;
	for (int i = 0; i < n; ++i) {
		par[i] = i;
		nver[i] = 1;
	}
}

int hasEdge(int u, int v) {
	return join(u, v);
}
