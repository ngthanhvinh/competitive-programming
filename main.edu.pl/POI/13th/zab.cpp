#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
const int inf = 2e4;

int n, m;
int l[N][N], r[N][N];
int up[N][N], dn[N][N];
int sx, sy, ex, ey;

int in_row(int i, int j) {
	int dist = inf;
	dist = min(dist, l[i][j] ? j - l[i][j] : inf);
	dist = min(dist, r[i][j] ? r[i][j] - j : inf);
	return dist;
}

struct ConvexHullTrick {
	struct line { int a; int b; };
	vector<line> L;
	int ptr;
	ConvexHullTrick() { L.clear(); ptr = 0; }

	bool bad(line l1, line l2, line l3) { 
		return 1LL * (l1.b - l2.b) * (l2.a - l3.a) < 1LL * (l3.b - l2.b) * (l2.a - l1.a); 
	}
	void add(int a, int b) {
		line d = {a,b};
		while(L.size() >= 2 && bad(L[L.size()-2], L[L.size()-1], d)) L.pop_back();
		L.push_back(d);
	}
	int get(int x) {
		if (L.empty()) return inf * inf;
		if (ptr > L.size()-1) ptr = L.size()-1;
		while(ptr < L.size()-1 && L[ptr].a * x + L[ptr].b > L[ptr+1].a * x + L[ptr+1].b) ++ptr;
		return L[ptr].a * x + L[ptr].b;
	}
} cht;

int cell(int i, int j) { return (i-1) * m + (j-1); }

typedef pair<int,int> ii;
vector< pair<int, ii> > vec;
int par[N * N];
const int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1};

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) { p = anc(p); q = anc(q); par[p] = q; }

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	cin >> sx >> sy >> ex >> ey;
	int num; cin >> num;
	while(num-- > 0) {
		int x, y; cin >> x >> y;
		l[x][y] = y; r[x][y] = y;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) if (l[i][j] == 0) l[i][j] = l[i][j-1];
		for (int j = m; j >= 1; --j) if (r[i][j] == 0) r[i][j] = r[i][j+1];
	}

	for (int j = 1; j <= m; ++j) {
		cht = ConvexHullTrick();
		for (int i = 1; i <= n; ++i) {
			int d = in_row(i,j);
			up[i][j] = min(d * d, i * i + cht.get(i));
			if (d != inf) cht.add(-2 * i, d * d + i * i);
		}

		cht = ConvexHullTrick();
		for (int i = n; i >= 1; --i) {
			int d = in_row(i,j);
			dn[i][j] = min(d * d, i * i + cht.get(-i));
			if (d != inf) cht.add(2 * i, d * d + i * i);
		}

		for (int i = 1; i <= n; ++i) {
			int TIME = min(up[i][j], dn[i][j]);
			vec.push_back(make_pair(TIME, ii(i, j)));
		}
	}
	for (int i = 0; i < n * m; ++i) par[i] = -1;

	int s = cell(sx, sy);
	int e = cell(ex, ey);
	sort(vec.begin(), vec.end(), greater< pair<int,ii> >());
	for (int i = 0; i < vec.size(); ++i) {
		int x = vec[i].second.first, y = vec[i].second.second;
		par[cell(x,y)] = cell(x,y);

		for (int dir = 0; dir < 4; ++dir) {
			int nx = x + dx[dir], ny = y + dy[dir];
			if (nx <= 0 || nx > n || ny <= 0 || ny > m || par[cell(nx,ny)] == -1) continue;
			join(cell(x,y), cell(nx,ny));
		}
		
		if (par[s] != -1 && par[e] != -1 && anc(s) == anc(e)) {
			printf("%d\n", vec[i].first);
			return 0;
		}
	}

	printf("0\n");
}