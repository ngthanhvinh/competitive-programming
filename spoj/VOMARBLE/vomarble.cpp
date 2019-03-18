#include <bits/stdc++.h>
using namespace std;

const int md = 1e9 + 7;

struct Matrix {
	int M[62][62];
	Matrix() { memset(M, 0, sizeof M); }
};

Matrix operator * (Matrix a, Matrix b) {
	Matrix c = Matrix();
	for (int i = 0; i < 62; ++i) for (int j = 0; j < 62; ++j) {
		for (int k = 0; k < 62; ++k) c.M[i][j] = (c.M[i][j] + 1LL * a.M[i][k] * b.M[k][j]) % md;
	}
	return c;
}

vector<int> operator * (vector<int> a, Matrix b) {
	vector<int> c(62, 0);
	for (int i = 0; i < 62; ++i) {
		for (int j = 0; j < 62; ++j) c[i] = (c[i] + 1LL * a[j] * b.M[j][i]) % md;
	}
	return c;
}

Matrix adj, pw_adj[65];

const int N = 2005;
struct Query {
	int type; long long x; char y;
	bool operator < (const Query &rhs) const {
		return x < rhs.x;
	}
} q[N];

int id(char c) {
	if ('a' <= c && c <= 'z') return c - 'a';
	else if ('A' <= c && c <= 'Z') return 26 + c - 'A';
	else return 52 + c - '0';
}

long long n;
int m, k;

void pw(vector<int> &res, long long p) {
	for (int i = 0; (1LL << i) <= p; ++i) {
		if (p & (1LL << i)) res = res * pw_adj[i];
	}
}

int main() {
	//freopen("marble.inp", "r", stdin);
	//freopen("marble.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 0; i < 62; ++i) {
		for (int j = 0; j < 62; ++j) adj.M[i][j] = 1;
	}
	while(m--) {
		char a, b; cin >> a >> b;
		int ca = id(a), cb = id(b);
		adj.M[ca][cb] = adj.M[cb][ca] = 0;
	}
	pw_adj[0] = adj;
	for (int i = 1; i < 65; ++i) pw_adj[i] = pw_adj[i-1] * pw_adj[i-1];

	for (int i = 0; i < k; ++i) {
		cin >> q[i].type >> q[i].x >> q[i].y;
	}
	sort(q, q + k);


	vector<int> res(62, 1);
	long long lst = 1;
	for (int i = 0; i < k; ) {
		long long TIME = q[i].x;
		pw(res, TIME - lst);
		char fixed = '?';
		vector<char> diff;

		while(i < k && q[i].x == TIME) {
			if (q[i].type == 1) {
				if (fixed == '?') {
					fixed = q[i].y;
					int ID = id(fixed);
					for (int ch = 0; ch < 62; ++ch) if (ch != ID) {
						res[ch] = 0;
					}
				} else if (q[i].y != fixed) return printf("0\n"), 0;
			} else {
				diff.push_back(q[i].y);
				res[id(q[i].y)] = 0;
			}	

			++i;
		}

		for (char ch : diff) if (ch == fixed) return printf("0\n"), 0;
		lst = TIME;
	}	

	pw(res, n - lst);
	int ans = 0;
	for (int i = 0; i < 62; ++i) ans = (ans + res[i]) % md;
	printf("%d\n", ans);
}