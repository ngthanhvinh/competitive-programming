#include <bits/stdc++.h>
using namespace std;
#define double long double
const double eps = 1e-12;

struct Matrix {
	vector< vector<double> > M;
	int size() { return M.size(); }
	Matrix(int n = 0, int m = 0) { M.assign(n + 1, vector<double>(m + 1, 0)); }
	vector<double> &operator [](int x) { return M[x]; }
};

Matrix operator * (Matrix a, Matrix b) {
	int m = a.size() - 1, n = b.size() - 1, p = b[0].size() - 1;
	Matrix c = Matrix(m, p);
	for (int i = 1; i <= m; ++i) for (int j = 1; j <= p; ++j) {
		for (int k = 1; k <= n; ++k) c[i][j] += a[i][k] * b[k][j];
	}
	return c;
}

Matrix pw(Matrix a, int n) {
	int m = a.size() - 1;
	Matrix res = Matrix(m, m); for (int i = 1; i <= m; ++i) res[i][i] = 1.0;
	for (int i = 0; (1LL << i) <= n; ++i) {
		if (n & (1LL << i)) res = res * a;
		a = a * a;
	}
	return res;
}

const int N = 100010;
int n;
double W[2], L[2];
double f[N][2];

void solve() {
	cin >> n;
	for (int i = 0; i < 2; ++i) cin >> W[i];
	for (int i = 0; i < 2; ++i) cin >> L[i];
	if (n == 1) {
		cout << max(W[0],W[1]) << endl;
		return;
	}
	double f0 = L[0] * max(W[0], W[1]) + (1.0 - L[0]) * min(W[0], W[1]);
	double f1 = L[1] * max(W[0], W[1]) + (1.0 - L[1]) * min(W[0], W[1]);

	n -= 2;

	bool swapped = false;
	if (f0 > f1 + eps) swap(f0, f1), swap(L[0], L[1]), swapped = true;

	Matrix base = Matrix(2,2); 
	base[1][1] = 1.0 - L[0], base[1][2] = L[0];
	base[2][1] = 1.0 - L[1], base[2][2] = L[1];
	Matrix M = Matrix(2, 1);
	M[1][1] = f0;
	M[2][1] = f1;

	base = pw(base, n);
	M = base * M;

	if (!swapped) cout << M[1][1] << endl; else cout << M[2][1] << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cout << setprecision(9) << fixed;
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
}