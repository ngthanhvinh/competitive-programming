#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
typedef pair<int,int> ii;
#define fi first
#define se second

int n, q;
ii a[N];
int res[N];
vector<int> z;

struct Query {
	int a; int b; int id;
	bool operator < (const Query &rhs) const {
		return a > rhs.a;
	}
} query[N];

// BIT
int T[N * 2];
void upd(int x, int v) { for (; x < 2 * N; x += x & -x) T[x] = max(T[x], v); }
int get(int x) { int ret = 0; for (; x > 0; x -= x & -x) ret = max(ret, T[x]); return ret; }

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].fi, &a[i].se);
		z.push_back(a[i].se);
	}
	sort(a + 1, a + n + 1, [&](ii p, ii q) {
		return p.fi < q.fi || (p.fi == q.fi && p.se > q.se);
	});

	for (int i = 0; i < q; ++i) {
		scanf("%d%d", &query[i].a, &query[i].b);
		query[i].id = i;
		z.push_back(query[i].b);
	}
	sort(query, query + q);

	sort(z.begin(), z.end());
	z.erase(unique(z.begin(), z.end()), z.end()); // z.size() <= 4e5

	// solve
	int ptr = n;
	for (int i = 0; i < q; ++i) { // >= A
		while(ptr >= 1 && a[ptr].fi >= query[i].a) {
			int p = lower_bound(z.begin(), z.end(), a[ptr].se) - z.begin() + 1;
			int f = get(p) + 1; // <= p
			upd(p, f);
			--ptr;
		}

		int pb = lower_bound(z.begin(), z.end(), query[i].b) - z.begin() + 1;
		res[query[i].id] = get(pb);
	}

	for (int i = 0; i < q; ++i) printf("%d\n", res[i]);
}