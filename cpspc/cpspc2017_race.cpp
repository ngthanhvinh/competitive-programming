#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int Q = 1000005;

int n, m, q;
char a[N][N];
int sx[Q], sy[Q], ex[Q], ey[Q];
vector<int> queries[N * 4];
bitset<N> dn[N][N], up[N][N];
bool ans[Q];

void push(int v, int l, int r, int i) {
	if (l > r || l > sx[i] || r < ex[i]) return;
	
	int mid = ((l + r) >> 1);
	if (sx[i] <= mid && mid <= ex[i]) {
		queries[v].push_back(i); return;
	}

	push(v << 1, l, mid - 1, i); push(v << 1 | 1, mid + 1, r, i);
}

void solve(int v, int l, int r) {
	if (l > r) return;
	int mid = ((l + r) >> 1);
	
	// solve
	for (int i = mid; i >= l; --i) {
		for (int j = m; j >= 1; --j) {
			dn[i][j] = 0;
			if (a[i][j] == '.') {
				if (i == mid) {
					dn[i][j][j] = 1;
				} else {
					dn[i][j] |= dn[i + 1][j]; // i < mid
				}
				if (j < m) dn[i][j] |= dn[i][j + 1];
			}
		}
	}

	for (int i = mid; i <= r; ++i) {
		for (int j = 1; j <= m; ++j) {
			up[i][j] = 0;
			if (a[i][j] == '.') {
				if (i == mid) {
					up[i][j][j] = 1;
				} else {
					up[i][j] |= up[i - 1][j]; // i > mid
				}
				if (j > 1) up[i][j] |= up[i][j - 1];
			}
		}
	}

	for (int i : queries[v]) {
		ans[i] = (dn[sx[i]][sy[i]] & up[ex[i]][ey[i]]).any();
	}

	// push
	solve(v << 1, l, mid - 1); solve(v << 1 | 1, mid + 1, r);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> q;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j];
		}
	}

	for (int i = 1; i <= q; ++i) {
		cin >> sx[i] >> sy[i] >> ex[i] >> ey[i];
		if (sx[i] <= ex[i] && sy[i] <= ey[i]) push(1, 1, n, i);
	}

	solve(1, 1, n);

	for (int i = 1; i <= q; ++i) printf(ans[i] ? "YES\n" : "NO\n");
}