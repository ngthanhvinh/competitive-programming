#include <bits/stdc++.h>
using namespace std;

#define int long long 

const int N = 2010, M = 100010;

int n, m, w, h;
int par[N];
int x[N], y[N], r[N];
int ans[M][4];

int find(int p) { return p == par[p] ? p : par[p] = find(par[p]); }
void join(int p, int q) { par[find(p)] = find(q); }

typedef pair<int,int> ii;
typedef pair<int,ii> II;
vector <II> A;

int touch(int i, int j) {
	if (i >= n && j >= n) return -1;
	if (j >= n) swap(i,j);
	if (i < n) return (int)sqrt( 1LL * (x[i]-x[j]) * (x[i]-x[j]) + 1LL * (y[i]-y[j]) * (y[i]-y[j]) ) - r[i] - r[j];
	if (i == n    ) return y[j] - r[j];
	if (i == n + 1) return w - (x[j] + r[j]);
	if (i == n + 2) return h - (y[j] + r[j]);
	if (i == n + 3) return x[j] - r[j];
	return -1;
}

bool connect(int r, int i, int j) {
	return find(n + (r + i) % 4) == find(n + (r + j) % 4);
}

// Trees n, n + 1, n + 2, n + 3 are the bottom, right, top and left borders respectively
signed main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> w >> h;
	for (int i = 0; i < n; ++i) cin >> x[i] >> y[i] >> r[i];
	for (int i = 0; i < n + 4; ++i) par[i] = i;
	for (int i = 0; i < m; ++i) {
		int rr, ee; cin >> rr >> ee; --ee;
		A.push_back(II(rr * 2, ii(i + n + 4, ee)));
	}
	for (int i = 0; i < n + 4; ++i) {
		for (int j = i + 1; j < n + 4; ++j) {
			int T = touch(i,j);
			if (T != -1) A.push_back(II(T + 1, ii(i,j)));
		}
	}

	sort(A.begin(), A.end());

	for (int i = 0; i < (int)A.size(); ++i) {
		int u = A[i].second.second, v = A[i].second.first;
		if (v < n + 4) join(u,v);
		else {
			v -= (n + 4); ans[v][u] = 1;
			if (!connect(u,0,1) && !connect(u,0,2) && !connect(u,0,3)) ans[v][(u + 1) % 4] = 1;
			if (!connect(u,0,2) && !connect(u,0,3) && !connect(u,1,3) && !connect(u,1,2)) ans[v][(u + 2) % 4] = 1;
			if (!connect(u,3,0) && !connect(u,3,1) && !connect(u,3,2)) ans[v][(u + 3) % 4] = 1;
		}
	}

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < 4; ++j) if (ans[i][j]) printf("%lld", j+1);
		printf("\n");
	}
}