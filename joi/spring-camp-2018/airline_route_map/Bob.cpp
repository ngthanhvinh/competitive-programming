#include "Boblib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1050;

static int nver;
static vector<int> g[MAXN];
static bool e[MAXN][MAXN];
static int label[MAXN], isbit[MAXN];
static vector<int> bits;
static bool vis[MAXN], checking[MAXN];
static vector< pair<int,int> > edges;

void find_path(int u) {
	vis[u] = true;
	isbit[u] = bits.size();
	bits.push_back(u);

	for (int &v : g[u]) if (!vis[v] && checking[v]) {
		return find_path(v);
	}
}

void Bob(int N, int M, int A[], int B[]) {
	for (int i = 0; i < M; ++i) {
		g[A[i]].push_back(B[i]);
		g[B[i]].push_back(A[i]);
		e[A[i]][B[i]] = e[B[i]][A[i]] = 1;
	}

	int nver = N - 12;
	if (nver == 1) {
		InitMap(1, 0); return;
	}

	int s, t;
	bool found = false;

	for (s = 0; s < N; ++s) {
		for (t = 0; t < N; ++t) {
			if (!(g[s].size() == 10 && g[t].size() == 11)) continue;
			// compare g[s] and g[t]
			for (int &ver1 : g[t]) {
				bool ok = true;
				vector<int> gs, gt;
				for (int &i : g[s]) if (i != ver1) gs.push_back(i);
				for (int &i : g[t]) if (i != ver1) gt.push_back(i);
				sort(gs.begin(), gs.end());
				sort(gt.begin(), gt.end());

				if (gs != gt) {
					continue; // invalid
				}

				for (int &i : gs) checking[i] = true;
				vis[s] = vis[t] = 1;
				for (int &i : gs) {
					if (e[i][ver1]) {
						find_path(i);
						found = true;
						break;
					}
				}
				if (found) break;
			}
			if (found) break;
		}
		if (found) break;
	}

	assert(bits.size() == 10);

	for (int i = 0; i < N; ++i) if (!vis[i]) {
		for (int &j : g[i]) {
			if (j == s || j == t) continue;
			if (vis[j]) label[i] |= (1 << isbit[j]);
		}
	}

	for (int i = 0; i < M; ++i) if (!vis[A[i]] && !vis[B[i]]) {
		edges.push_back(make_pair(A[i], B[i]));
	}

	InitMap(nver, edges.size());
	for (auto &e : edges) {
		MakeMap(label[e.first], label[e.second]);
	}
}

