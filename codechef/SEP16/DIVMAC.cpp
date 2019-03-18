#include <bits/stdc++.h>
using namespace std;
const int N = 100010, MAX = 1000010;
typedef pair<int,int> ii;

int n, m;
int d[MAX];
deque <int> q[N];
set <ii> s;
set <ii>::iterator it; 

void sieve() {
	d[0] = d[1] = 1;
	for (int i = 2; i < MAX; i++) if (!d[i]) 
		for (int j = i; j < MAX; j+=i) d[j] = i;
}

// Segment Tree
int t[N<<2];
#define le (v<<1)
#define ri ((v<<1)|1)
#define mid ((l + r) >> 1)

void upd(int v, int l, int r, int x, int val) {
	if (l > r || l > x || r < x) return;
	if (l == r) { t[v] = val; return; }
	upd(le,l,mid,x,val); upd(ri,mid+1,r,x,val);
	t[v] = max(t[le], t[ri]);
}

int get(int v, int l, int r, int L, int R) {
	if (l > r || R < l || L > r) return 1;
	if (L <= l && r <= R) return t[v];
	return max(get(le,l,mid,L,R), get(ri,mid+1,r,L,R));
}

void solve() {
	scanf("%d%d", &n, &m); s.clear();
	for (int i = 1; i <= 4 * n + 10; i++) t[i] = 1;
	for (int i = 1; i <= n; i++) {
		int x; scanf("%d", &x); q[i].clear();
		while(x != 1) q[i].push_front(d[x]), x /= d[x];
		if (!q[i].empty()) upd(1, 1, n, i, q[i].front()), q[i].pop_front();
		s.insert(ii(i, q[i].size()));
	}

	while(m--) {
		int type, l, r; scanf("%d%d%d", &type, &l, &r);
		if (type == 0) {
			vector <ii> trash;
			it = s.lower_bound(ii(l, 0));
			for (set<ii>::iterator IT = it; IT != s.end() && (IT->first) <= r; ++IT) trash.push_back(*IT);
			for (int i = 0; i < trash.size(); i++) {
				ii cur = trash[i]; 
				s.erase(cur);
				if (cur.second) 
					upd(1, 1, n, cur.first, q[cur.first].front()), q[cur.first].pop_front(), s.insert(ii(cur.first, cur.second-1));
				else upd(1, 1, n, cur.first, 1);
			}
		}
		else printf("%d ", get(1, 1, n, l, r));
	}
	printf("\n");
}

int main() {
	sieve();
	int t; scanf("%d", &t);
	while(t--)
		solve();
}