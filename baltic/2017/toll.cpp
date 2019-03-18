#include <bits/stdc++.h>
using namespace std;

const int N = 50005, Q = 10005;
const int inf = 1e9;

int n, m, K, q;

struct Matrix {
	int M[5][5];
	Matrix(int val = inf) { for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j) M[i][j] = val; }
};

Matrix operator * (Matrix a, Matrix b) {
	Matrix c = Matrix();
	for (int i = 0; i < K; ++i) for (int j = 0; j < K; ++j) {
		for (int k = 0; k < K; ++k) c.M[i][j] = min(c.M[i][j], a.M[i][k] + b.M[k][j]);
	}
	return c;
}

Matrix base[N][16];

Matrix jump(int x, int y) {
	Matrix res = Matrix();
	bool found = false;
	for (int j = 15; j >= 0; --j) if (x + (1 << j) <= y) {
		if (found) res = res * base[x][j];
		else res = base[x][j];
		found = true;
		x += (1 << j);
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> K >> n >> m >> q;
	while(m--) {
		int u, v, t; cin >> u >> v >> t;
		base[u / K][0].M[u % K][v % K] = t;
	}
	for (int j = 1; j < 16; ++j) {
		for (int i = 0; i <= (n - 1) / K; ++i) {
			if (i + (1 << j) > (n - 1) / K) break;
			base[i][j] = base[i][j - 1] * base[i + (1 << (j - 1))][j - 1];
		}
	}

	while(q--) {
		int u, v; cin >> u >> v;
		if (u / K == v / K) { printf("-1\n"); continue; }
		Matrix res = jump(u / K, v / K);
		printf("%d\n", res.M[u % K][v % K] == inf ? -1 : res.M[u % K][v % K]);
	}
}