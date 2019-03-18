#include "sorting.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n, m;
int s[MAXN];
int pa[MAXN], pb[MAXN], a[MAXN], b[MAXN], pos[MAXN];
int x[MAXN * 3], y[MAXN * 3];
vector < pair<int,int> > vres;

bool check(int k) {
	vres.clear();
	for (int i = 0; i < n; ++i) {
		pos[i] = i;
	}
	for (int i = 0; i < k; ++i) {
		swap(pos[x[i]], pos[y[i]]); // swap positions
	}

	for (int i = 0; i < n; ++i) {
		b[pos[i]] = i;
	}

	// the swaps must satisfy: s[i] = b[i]
	for (int i = 0; i < n; ++i) {
		pb[s[i]] = b[i];
		pa[b[i]] = s[i];
	}

	for (int i = 0; i < n; ++i) {
		if (pa[i] != i) {
			// TODO: swap i, pb[i]
			int j = pb[i];
			int p = pa[i], q = pa[j];
			vres.push_back({p, q}); // values, not positions
			swap(pa[i], pa[j]);
			pb[q] = i;
			pb[p] = j;
		}
	}

	// trace the positions
	for (int i = 0; i < n; ++i) a[i] = s[i], pos[a[i]] = i;

	for (int i = 0; i < k; ++i) {
		// swap a[x[i]], a[y[i]]
		auto do_swap = [&](int p, int q) {
			pos[a[p]] = q;
			pos[a[q]] = p;
			swap(a[p], a[q]);
		};
		do_swap(x[i], y[i]);
		// trace
		if (i < (int)vres.size()) {
			vres[i] = {pos[vres[i].first], pos[vres[i].second]};
			do_swap(vres[i].first, vres[i].second);
		}
	}

	for (int i = (int)vres.size(); i < k; ++i) {
		vres.push_back({0, 0});
	}

	return vres.size() == k;
}

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
	n = N;
	m = M;
  for (int i = 0; i < n; ++i) s[i] = S[i];
  for (int i = 0; i < m; ++i) x[i] = X[i], y[i] = Y[i];

  int low = 0, high = m;
  while(low < high) {
  	int mid = ((low + high) >> 1);
  	if (check(mid)) high = mid;
  	else low = mid + 1;
  }

  check(low);
  for (int i = 0; i < low; ++i) {
  	P[i] = vres[i].first;
  	Q[i] = vres[i].second;
  }
  return low;
}


