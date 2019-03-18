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

const int INF = 1e9, N = 100010, mod = 1e8;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

struct matrix {
	vector <vi> M;
	int size() { return M.size(); }
	matrix(int n, int m) { M.assign(n + 1, vi(m + 1, 0)); }
	vi& operator [] (int x) { return M[x]; }
};

matrix operator * (matrix a, matrix b) {
	int m = a.size()-1, n = b.size()-1, p = b[0].size()-1;
	matrix c = matrix(m, m);
	ff(i, 1, m) ff(j, 1, p) {
		ff(k, 1, n) c[i][j] = (c[i][j] + (1LL * a[i][k] * b[k][j]) % mod) % mod;
	}
	return c;
}

matrix pw(matrix a, long long n) {
	int m = a.size()-1; matrix res = matrix(m, m);
	ff(i, 1, m) res[i][i] = 1;
	for (int i = 0; (1LL << i) <= n; i++) {
		if (n & (1LL << i)) res = res * a;
		a = a * a;
	}
	return res;
}
long long n;

void debug(matrix a) {
	fo(i, 1, a.size()) {
		fo(j, 1, a[0].size()) cout << a[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n;
	matrix G = matrix(4, 4);
	G[1][1] = G[1][2] = 2; G[1][4] = 1; G[1][3] = mod - 2;
	G[2][1] = G[3][2] = G[4][3] = 1;
	//debug(G);
	matrix f = matrix(4, 1);
	f[4][1] = 1; f[3][1] = 1; f[2][1] = 4; f[1][1] = 8;
	//debug(f);
	n -= 4;
	G = pw(G, n);
	//debug(G);
	f = G * f;
	cout << f[1][1] << endl;
}