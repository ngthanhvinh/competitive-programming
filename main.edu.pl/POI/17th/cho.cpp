#include <bits/stdc++.h>
using namespace std;

const int N = 210;
const int MAX = 100010, BASE = 26;
const int mod = 1e9 + 123;
const long long inf = 1e18;

int n, m;
string s[N];
int *h[N];
int w[MAX];

struct Matrix {
	long long M[N][N];
	void init() {
		for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) M[i][j] = inf;
	}
};

Matrix operator * (Matrix a, Matrix b) {
	Matrix c = Matrix(); c.init();
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
		for (int k = 1; k <= n; ++k) c.M[i][j] = min(c.M[i][j], a.M[i][k] + b.M[k][j]);
	}
	return c;
}

Matrix pw(Matrix a, int p) {
	Matrix res = a; --p;
	while(p) {
		if (p & 1) res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
} 

void make_hash(int x) {
	h[x] = new int[s[x].size() + 1];
	h[x][0] = 0;
	for (int i = 0; i < s[x].size(); ++i) {
		h[x][i+1] = (1LL * h[x][i] * BASE + s[x][i] - 'a') % mod;
	}
}

int get(int x, int l, int r) {
	long long v = (h[x][r] - 1LL * h[x][l-1] * w[r-l+1] + 1LL * mod * mod) % mod;
	return v;
}

Matrix adj;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	w[0] = 1; for (int i = 1; i < MAX; ++i) w[i] = 1LL * w[i-1] * BASE % mod;
	for (int i = 1; i <= n; ++i) {
		cin >> s[i];
		make_hash(i);
	}
	if (m == 1) {
		int ret = 1e9;
		for (int i = 1; i <= n; ++i) ret = min(ret, (int)s[i].size());
		return printf("%d\n", ret), 0;
	}

	adj = Matrix(); adj.init();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			int sz = min((int)s[i].size(), (int)s[j].size());
			if (i == j) --sz;
			while(sz > 0 && get(j, 1, sz) != get(i, s[i].size() - sz + 1, s[i].size())) --sz;
			adj.M[i][j] = s[j].size() - sz;
		}
	}
	adj = pw(adj, m - 1);
	long long ans = inf;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			ans = min(ans, adj.M[i][j] + (int)s[i].size());
		}
	}
	printf("%lld\n", ans);
}