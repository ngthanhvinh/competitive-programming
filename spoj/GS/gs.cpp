#include <bits/stdc++.h>
using namespace std;
const int N = 51;

int n, s, t;
int c[N][N];
double f[N];
vector < vector<double> > a;

void GaussianElimination() {
	a.assign(n + 2, vector<double>(n + 2, 0.0));
	for (int i = 1; i <= n; ++i) {
		a[i][i] = 1.0;
		if (i != t) {
			int sum = 0; 
			for (int j = 1; j <= n; ++j) if (i != j) sum += c[i][j];
			for (int j = 1; j <= n; ++j) if (i != j) a[i][j] = (double)-c[i][j] / sum;
			a[i][n + 1] = 1.0;
		}
	} 
	for (int k = 1; k <= n; ++k) {
		int imax = k;
		for (int i = k; i <= n; ++i) if (abs(a[i][k]) >= abs(a[imax][k])) imax = i;
		a[k].swap(a[imax]);
		for (int i = k + 1; i <= n; ++i) {
			double f = (double)a[i][k] / a[k][k];
			for (int j = k + 1; j <= n + 1; ++j) a[i][j] -= a[k][j] * f;
			a[i][k] = 0; 
		}
	}
	for (int k = n; k >= 1; --k) {
		double ans = a[k][n + 1];
		for (int i = n; i > k; --i) ans -= a[k][i] * f[i];
		f[k] = ans / a[k][k]; 
	}
}

void solve() {
	memset(c, 0, sizeof c);
	cin >> n >> s >> t;
	for (int i = 1; i < n; ++i) {
		int u, v, w; cin >> u >> v >> w;
		c[u][v] = c[v][u] = w;
	}
	GaussianElimination();
	cout << setprecision(5) << fixed << f[s] << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int nTest; cin >> nTest;
	while(nTest--)
		solve();
}