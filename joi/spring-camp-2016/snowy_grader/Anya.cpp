#include "Anyalib.h"
#include <bits/stdc++.h>
using namespace std;

namespace A {
	const int N = 505;
	
	int n;
	int dep[N];
	int snowy[N];
	int w[N]; // for edges
	int mod;
	int where[N];
	vector< pair<int,int> > G[N];
	vector<int> cand;

	void dfs(int u, int p) {
		for (auto e : G[u]) {
			int v = e.second; if (v == p) continue;
			dep[v] = dep[u] + 1;
			dfs(v, u);
		}
	}

	void redfs(int u, int p) {
		for (auto e : G[u]) {
			int id = e.first, v = e.second; if (v == p) continue;
			snowy[v] = snowy[u] + w[id];
			redfs(v, u);
		}
	}

	void init() {
		dfs(0, 0);
		vector<int> buf[10];
		for (int i = 0; i < n; ++i) {
			buf[dep[i] % 10].push_back(i);
		}
		mod = 0;
		for (int i = 1; i < 10; ++i) {
			if (buf[i].size() < buf[mod].size()) mod = i;
		}

		cand = buf[mod];
	}

	void solve() {
		for (int i = 0; i < n; ++i) snowy[i] = 0;
		redfs(0, 0);

		// save the edges into bits from 0 to N - 2
		for (int i = 0; i < n - 1; ++i) {
			Save(i, w[i]);
		}

		// save the "snowy" values of the vertices that are candidates
		// each has 9 bits
		int cur = n - 1;
		for (int u : cand) {
			where[u] = cur;
			for (int i = 0; i < 9; ++i) {
				Save(cur, snowy[u] >> i & 1); ++cur;
			}
		}

		assert(cur < 1000);
	}
}

void InitAnya(int N , int A[] , int B[]) {
	A::n = N;
	for (int i = 0; i < N - 1; ++i) {
		A::G[A[i]].push_back(make_pair(i, B[i]));
		A::G[B[i]].push_back(make_pair(i, A[i]));
	}
	A::init();
}

void Anya(int C[]) {
 	for (int i = 0; i < A::n - 1; ++i) {
  	A::w[i] = C[i];
  }
  A::solve();
}
