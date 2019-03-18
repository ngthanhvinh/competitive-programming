#include "Borislib.h"
#include <bits/stdc++.h>
using namespace std;

namespace B {
	const int N = 505;
	
	int n;
	int par[N], topar[N];
	int dep[N];
	int w[N]; // for edges
	int mod;
	int where[N];
	vector< pair<int,int> > G[N];
	vector<int> cand;

	void dfs(int u) {
		for (auto e : G[u]) {
			int v = e.second; if (v == par[u]) continue;
			par[v] = u;
			topar[v] = e.first;
			dep[v] = dep[u] + 1;
			dfs(v);
		}
	}

	void init() {
		dfs(0);
		vector<int> buf[10];
		for (int i = 0; i < n; ++i) {
			buf[dep[i] % 10].push_back(i);
		}
		mod = 0;
		for (int i = 1; i < 10; ++i) {
			if (buf[i].size() < buf[mod].size()) mod = i;
		}

		cand = buf[mod];

		// where
		int cur = n - 1;
		for (int u : cand) {
			where[u] = cur; cur += 9;
		}
	}

	int solve(int u) {
		int ret = 0;
		while(u && dep[u] % 10 != mod) {
			ret += Ask(topar[u]); u = par[u];
		}
		if (dep[u] % 10 == mod) {
			int start = where[u];
			int cur = 0;
			for (int i = start; i < start + 9; ++i) {
				cur += (1 << (i - start)) * Ask(i);
			}
			ret += cur;
		}
		return ret;
	}
}

void InitBoris(int N , int A[] , int B[]) {
  B::n = N;
	for (int i = 0; i < N - 1; ++i) {
		B::G[A[i]].push_back(make_pair(i, B[i]));
		B::G[B[i]].push_back(make_pair(i, A[i]));
	}
	B::init();
}

int Boris(int city) {
  return B::solve(city);
}
