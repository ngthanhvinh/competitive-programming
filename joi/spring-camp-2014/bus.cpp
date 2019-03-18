#include <bits/stdc++.h>
using namespace std;

const int N = 300005;
const int inf = 1e9 + 7;

struct bus {
	int a; int b; int x; int y; int id;
	bus(int a=0, int b=0, int x=0, int y=0, int id=0): a(a), b(b), x(x), y(y), id(id) {}
} d[N], e[N];

bool cmpl(bus p, bus q) {
	return p.x < q.x || (p.x == q.x && p.y < q.y);
}

bool cmpr(bus p, bus q) {
	return p.y < q.y || (p.y == q.y && p.x < q.x);
}

int n, m, q;
int f[N];
int res[N];
int mx[N];
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> d[i].a >> d[i].b >> d[i].x >> d[i].y, d[i].id = i;
		e[i] = d[i];
	}
	sort(d + 1, d + m + 1, cmpl);
	sort(e + 1, e + m + 1, cmpr);
	for (int i = 0; i < N; ++i) mx[i] = -inf;
	int cur = 1;
	for (int i = 1; i <= m; ++i) {
		int xx = d[i].x, id = d[i].id;
		if (d[i].a == 1) {
			f[id] = xx;
			continue;
		}
		while(cur <= m && e[cur].y <= xx) {
			mx[e[cur].b] = max(mx[e[cur].b], f[e[cur].id]);
			++cur;
		}

		f[id] = mx[d[i].a];
	}

	vector< pair<int,int> > query;
	res[0] = -inf;
	for (int i = 1; i <= m; ++i) {
		res[i] = res[i-1];
		if (e[i].b == n) {
			query.push_back(make_pair(e[i].y, i));
			res[i] = max(res[i], f[e[i].id]);
		}
	}

	cin >> q;
	while(q--) {
		int T; cin >> T;
		int pos = upper_bound(query.begin(), query.end(), make_pair(T, inf)) - query.begin(); --pos;
		printf("%d\n", res[query[pos].second] != -inf ? res[query[pos].second] : -1);
	}
}