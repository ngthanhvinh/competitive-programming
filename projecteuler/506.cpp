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

const int INF = 1e9, N = 100010, mod = 123454321;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int pw(int a, long long b) {
	int res = 1;
	for (int i = 0; (1LL << i) <= b; i++) {
		if (b & (1LL << i)) res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return res;
}

struct matrix {
	vector <vi> M;
	vi& operator [] (int x) { return M[x]; }
	matrix(int n, int m) { M.assign(n + 1, vi(m + 1, 0)); }
	int size() { return M.size(); }
};

matrix operator * (matrix a, matrix b) {
	int m = a.size()-1, n = b.size()-1, p = b[0].size()-1;
	matrix c = matrix(m, p);
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

long long n, res, sum;
const int suff[] = {123432, 234321, 343212, 432123, 321234, 123432, 432123, 212343, 432123, 123432, 321234, 432123, 343212, 234321, 123432};
const int pre[] = {0, 1, 2, 3, 4, 32, 123, 43, 2123, 432, 1234, 32123, 43212, 34321, 23432};

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n;
	long long m = n / 15 - 1;
	int t = 1000000;
	fo(i, 0, 15) sum = (sum + suff[i]) % mod;
	fo(i, 0, 15) res = (res + pre[i]) % mod;
	//cout << "sum = " << sum << ' ' << "res = " << res << endl;
	long long cur = res;
	// ff(i, 1, m) {
	// 	cur = ((1LL * t * cur) % mod + sum) % mod;
	// 	res = (res + cur) % mod;
	// }
	
	matrix f = matrix(3, 1);
	f[1][1] = res; f[2][1] = cur; f[3][1] = sum;
	matrix G = matrix(3, 3);
	G[1][1] = 1; G[1][2] = t; G[1][3] = 1;
	G[2][1] = 0; G[2][2] = t; G[2][3] = 1;
	G[3][3] = 1;
	G = pw(G, m); f = G * f;
	res = f[1][1];
	
	long long nr = n - (n % 15);
	//cout << nr << endl;
	
	for (long long i = nr; i <= n; i++) {
		int tmp = (1LL * pre[i % 15] * pw(t, i / 15)) % mod;
		//cout << tmp << endl;
		matrix P = matrix(2, 2);
		P[1][1] = 1; P[1][2] = t;
		P[2][1] = 0; P[2][2] = t;
		matrix F = matrix(2, 1);
		F[1][1] = 1; F[2][1] = 1;
		P = pw(P, i / 15 - 1); F = P * F;
		tmp = (tmp + (1LL * suff[i % 15] * F[1][1]) % mod) % mod;
		//cout << i << ' ' << tmp << endl;
		res = (res + tmp) % mod;
	}
	
	cout << res << endl;
}
// 260517