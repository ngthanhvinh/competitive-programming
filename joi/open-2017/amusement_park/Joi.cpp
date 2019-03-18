#include "Joi.h"
#include <bits/stdc++.h>
using namespace std;

const int MAX = 10005;

namespace JOI {
	int n, m;
	int pos[MAX];
	int par[MAX];
	int id[MAX];
	bool vis[MAX];
	int ncomp;
	vector<int> comp[MAX];
	vector<int> G[MAX];
	long long X;
	
	void build() {
		vector< pair<int,int> > edges;
		for (int i = 0; i < n; ++i) pos[i] = 0;
		queue <int> q; q.push(0); pos[0] = 1;
	
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for (int v : G[u]) {
				if (!pos[v]) q.push(v), pos[v] = 1, edges.push_back(make_pair(u,v));
			}
		}
		for (int i = 0; i < n; ++i) G[i].clear(), pos[i] = 0;
		for (auto e : edges) G[e.first].push_back(e.second), G[e.second].push_back(e.first);
	}

	void dfs(int u) {
		if (comp[ncomp].size() == 60) return;
		pos[u] = ncomp;
		comp[ncomp].push_back(u);
		for (int v : G[u]) if (!pos[v]) {
			par[v] = u;
			dfs(v);
		}
	}

	void add(int u, int c) {
		if (comp[c].size() == 60) return;
		comp[c].push_back(u);
		vis[u] = 1;
		for (int v : G[u]) {
			if (pos[v] == pos[u] && !vis[v]) add(v, c);
		}
	}

	void prepare() {
		build();
		for (int i = 0; i < n; ++i) if (!pos[i]) ++ncomp, dfs(i);

		for (int i = 1; i <= ncomp; ++i) if (comp[i].size() == 60) {
			for (int j = 0; j < comp[i].size(); ++j) id[comp[i][j]] = j;
		}
		if (comp[ncomp].empty()) --ncomp;
		
		for (int i = 1; i <= ncomp; ++i) {
			if (comp[i].size() < 60) {
				int sz = comp[i].size();
				int root = -1;
				for (int u : comp[i]) {
					if (root != -1) break;
					for (int v : G[u]) if (pos[u] != pos[v] && comp[pos[v]].size() == 60) {
						root = v;
						break;
					}
				}
				add(root, i);

				long long mask = 0;
				vector<int> rem;
				for (int j = sz; j < 60; ++j) mask |= (1LL << id[comp[i][j]]);
				for (int j = 0; j < 60; ++j) if (!(mask >> j & 1)) rem.push_back(j);
				for (int j = 0; j < sz; ++j) id[comp[i][j]] = rem.back(), rem.pop_back();
				for (int u : comp[i]) vis[u] = false;
			}
		}
	}

	void assign() {
		JOI::prepare();
		for (int i = 0; i < n; ++i) MessageBoard(i, (X >> id[i] & 1));
	}
};

void Joi(int N, int M, int A[], int B[], long long X, int T) {
  JOI::n = N; 
  JOI::m = M;
  JOI::X = X;
  for (int i = 0; i < M; ++i) JOI::G[A[i]].push_back(B[i]), JOI::G[B[i]].push_back(A[i]);
  JOI::assign();
}
