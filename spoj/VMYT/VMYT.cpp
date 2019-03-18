#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define ff(i, a, b) for(int i = a; i <= b; i++)
#define fo(i, a, b) for(int i = a; i < b; i++)
#define fod(i, a, b) for(int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

const int INF = 1e9, N = 100010, mod = 1e9 + 7;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

struct matrix {
	vector <vi> M;
	int size() { return M.size(); }
	vi& operator [] (int x) { return M[x]; }
	matrix(int n, int m) { M.assign(n + 1, vi(m + 1, 0)); }
};

matrix operator * (matrix a, matrix b) {
	int m = a.size() - 1, n = b.size() - 1, p = b[0].size() - 1;
	matrix c = matrix(m, p);
	ff(i, 1, m) ff(j, 1, p) {
		ff(k, 1, n) c[i][j] = (c[i][j] + 1LL * a[i][k] * b[k][j] % (mod - 1)) % (mod - 1); 
	}
	return c;
}

matrix pw(matrix a, int n) {
	int m = a.size() - 1; matrix res = matrix(m, m);
	ff(i, 1, m) res[i][i] = 1;
	for (int i = 0; (1LL << i) <= n; ++i) {
		if (n & (1LL << i)) res = res * a;
		a = a * a;
	}
	return res;
}

int n, a[N], k;

int pw(int a, int n) {
	int res = 1;
	for (int i = 0; (1LL << i) <= n; ++i) {
		if (n & (1LL << i)) res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return res;
}

int main() {
	//freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	ff(i, 1, k) cin >> a[i];
	if (n <= k) return printf("%d\n", a[n]), 0;
	matrix G = matrix(k, k); ff(i, 1, k) G[1][i] = 1;
	ff(i, 1, k - 1) G[i + 1][i] = 1;
	G = pw(G, n - k);
	int ans = 1;
	ff(i, 1, k) {
		matrix res = matrix(k, 1); res[k - i + 1][1] = 1;
		res = G * res;
		ans = (1LL * ans * pw(a[i], res[1][1])) % mod;
	}
	printf("%d\n", ans);
}