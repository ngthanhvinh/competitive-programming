// TLE!
#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
typedef pair<int,int> ii;
#define fi first
#define se second

int n, m, q;
ii top_left;
long long srow[N], scol[N];

struct Node {
	int val;
	ii adj[2][2];
	// 0: horizontal
	// 1: vertical

	Node() {
		val = 0;
		for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) {
			adj[i][j] = ii();
		}
	}
} a[N][N];

struct Data {
	int type; int x; int y; int u; int v;
};
vector <Data> willcut, willadd;

void cut(int type, int x, int y, int u, int v) {
	if (x && y) {
		for (int i = 0; i < 2; ++i) {
			if (a[x][y].adj[type][i] == ii(u, v)) a[x][y].adj[type][i] = ii();
		}
	}
	if (u && v) {
		for (int i = 0; i < 2; ++i) {
			if (a[u][v].adj[type][i] == ii(x, y)) a[u][v].adj[type][i] = ii();
		}
	}
}
void add(int type, int x, int y, int u, int v) {
	if (x && y) {
		for (int i = 0; i < 2; ++i) {
			if (a[x][y].adj[type][i] == ii()) {
				a[x][y].adj[type][i] = ii(u, v);
				break;
			}
		}
	}
	if (u && v) {
		for (int i = 0; i < 2; ++i) {
			if (a[u][v].adj[type][i] == ii()) {
				a[u][v].adj[type][i] = ii(x, y);
				break;
			}
		}
	}
}

void go(int type, ii &cur, ii &last) {
	int x = cur.fi, y = cur.se;
	for (int i = 0; i < 2; ++i) {
		if (a[x][y].adj[type][i] != last) {
			last = cur;
			int nx = a[x][y].adj[type][i].fi;
			int ny = a[x][y].adj[type][i].se;
			cur = ii(nx, ny);
			return;
		}
	}
}
void find_path(int type, int r, int c1, int c2, vector <ii> &vec) {
	ii cur = top_left;
	ii last = ii();
	for (int i = 1; i < r; ++i) go(type ^ 1, cur, last);
	last = ii();
	for (int i = 1; i < c1; ++i) go(type, cur, last);
	vec.push_back(cur);
	for (int i = c1; i < c2; ++i) go(type, cur, last), vec.push_back(cur);
}

void relink_all(int type, int r, int c1, int c2) {
	// r - 1, r
	if (type == 0 && (r == 1 || r == n + 1)) return;
	if (type == 1 && (r == 1 || r == m + 1)) return;

	vector <ii> up;
	vector <ii> dn;
	find_path(type, r - 1, c1, c2, up);
	find_path(type, r, c1, c2, dn);

	int sz = up.size();
	for (int i = 0; i < sz; ++i) {
		willcut.push_back({type ^ 1, up[i].fi, up[i].se, dn[i].fi, dn[i].se});
	}
	for (int i = 0; i < sz; ++i) {
		willadd.push_back({type ^ 1, up[i].fi, up[i].se, dn[sz - 1 - i].fi, dn[sz - 1 - i].se});
	}
}

void relink_each(int type, int r1, int c1, int r2, int c2) {
	vector <ii> le, ri;
	find_path(type ^ 1, c1, r1, r2, le);
	find_path(type ^ 1, c2, r1, r2, ri);

	int lim = (type == 0 ? m : n);
	if (c1 > 1) {
		vector<ii> vec;
		find_path(type ^ 1, c1 - 1, r1, r2, vec);
		for (int i = 0; i < r2 - r1 + 1; ++i) {
			willcut.push_back({type, vec[i].fi, vec[i].se, le[i].fi, le[i].se});
			willadd.push_back({type, vec[i].fi, vec[i].se, ri[i].fi, ri[i].se});
		}
	}
	if (c2 < lim) {
		vector<ii> vec;
		find_path(type ^ 1, c2 + 1, r1, r2, vec);
		for (int i = 0; i < r2 - r1 + 1; ++i) {
			willcut.push_back({type, vec[i].fi, vec[i].se, ri[i].fi, ri[i].se});
			willadd.push_back({type, vec[i].fi, vec[i].se, le[i].fi, le[i].se});
		}
	}
}

void solve(int type, int r1, int c1, int r2, int c2) {
	if (type) swap(r1, c1), swap(r2, c2);
	willcut.clear();
	willadd.clear();
	// relink
	relink_all(type, r2 + 1, c1, c2);
	relink_all(type, r1, c1, c2);
	relink_each(type, r1, c1, r2, c2);

	// update top_left
	if (r1 == 1 && c1 == 1) {
		vector <ii> vec;
		find_path(type, r1, c1, c2, vec);
		top_left = vec.back();
	}

	// cut & add
	for (auto e : willcut) cut(e.type, e.x, e.y, e.u, e.v);
	for (auto e : willadd) add(e.type, e.x, e.y, e.u, e.v);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;
	top_left = ii(1, 1);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			a[i][j].val = (i - 1) * m + (j - 1);
			// init
			a[i][j].adj[0][0] = (j > 1 ? ii(i, j - 1) : ii());
			a[i][j].adj[0][1] = (j < m ? ii(i, j + 1) : ii());
			a[i][j].adj[1][0] = (i > 1 ? ii(i - 1, j) : ii());
			a[i][j].adj[1][1] = (i < n ? ii(i + 1, j) : ii());
		}
	}

	cin >> q;

	while(q--) {
		char type;
		int r1, c1, r2, c2;
		cin >> type >> r1 >> c1 >> r2 >> c2;
		solve(type == 'V', r1, c1, r2, c2);
	}

	// trace
	vector <ii> first_row(1, top_left);
	ii cur = top_left, last = ii();
	for (int i = 1; i < m; ++i) go(0, cur, last), first_row.push_back(cur);

	for (int i = 0; i < m; ++i) {
		ii e = first_row[i];
		vector <ii> col(1, e);
		last = ii();
		for (int j = 1; j < n; ++j) go(1, e, last), col.push_back(e);
		for (int j = 0; j < n; ++j) {
			srow[j + 1] += a[col[j].fi][col[j].se].val;
			scol[i + 1] += a[col[j].fi][col[j].se].val;
		}
	}

	for (int i = 1; i <= n; ++i) printf("%lld ", srow[i]); printf("\n");
	for (int i = 1; i <= m; ++i) printf("%lld ", scol[i]); printf("\n");
}