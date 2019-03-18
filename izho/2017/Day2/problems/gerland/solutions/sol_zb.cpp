#include <bits/stdc++.h>

#define all(x) (x).begin(),(x).end()
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define sz(x) ((int)(x).size())

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

const int inf = 1e9 + 5;
const int mod = 1e9 + 7;
const ll INF = 4e18 + 5;

pair < int, pair <int,int> > query[100100];
int n, m;
int a[100000+100];

int b[200000+100], k;

int t[4*200000+100];

inline void upd(int v, int l, int r, int L, int R, int x) {
	if(r < L || R < l) {
		return;
	}
	if(L <= l && r <= R) {
		t[v] += x;
		return;
	}
	int mid = (l + r) >> 1;
	upd(v + v, l, mid, L, R, x);
	upd(v + v + 1, mid + 1, r, L, R, x);
}

inline int get(int v, int l, int r, int pos) {
	if(l == r) {
		return t[v];
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) {
		return t[v] + get(v + v, l, mid, pos);
	}
	else {
		return t[v] + get(v + v + 1, mid + 1, r, pos);
	}
}

int main() {

	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
		b[k++] = a[i];
	}

	for(int i = 0; i < m; ++i) {
		int q;
		scanf("%d", &q);
		if(q == 1) {
			int pos, val;
			scanf("%d%d", &pos, &val);
			pos--;
			b[k++] = val;
			query[i] = (mp(q, mp(pos, val)));
		}
		else {
			int x;
			scanf("%d", &x);
			b[k++] = x;
			query[i] = (mp(q, mp(x, 0)));
		}
	}

	sort(b, b + k);
	k = unique(b, b + k) - b;

	for(int i = 0; i < n; ++i) {
		a[i] = lower_bound(b, b + k, a[i]) - b + 1;
	}

	for(int i = 0; i < n - 1; ++i) {
		upd(1, 1, k, min(a[i], a[i+1]), max(a[i], a[i+1]), 1);
	}

	for(int i = 0; i < m; ++i) {
		if(query[i].f == 1) {
			int pos = query[i].s.f, 
				val = lower_bound(b, b + k, query[i].s.s) - b + 1;
			if(a[pos] == val) {
				continue;
			}
			if(pos) {	
				upd(1, 1, k, min(a[pos-1], a[pos]), max(a[pos-1], a[pos]), -1);
				upd(1, 1, k, min(a[pos-1], val), max(a[pos-1], val), 1);
			}
			if(pos + 1 < n) {
				upd(1, 1, k, min(a[pos], a[pos+1]), max(a[pos], a[pos+1]), -1);
				upd(1, 1, k, min(val, a[pos+1]), max(val, a[pos+1]), 1);
			}
			a[pos] = val;
		}
		else {
			int x = lower_bound(b, b + k, query[i].s.f) - b + 1;
			printf("%d\n", get(1, 1, k, x));
		}
	}

	return 0;
}