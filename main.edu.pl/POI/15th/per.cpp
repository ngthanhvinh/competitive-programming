#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int n, md, a[N];
int d[N], t[N];
vector<int> prime;
int id[N];
int ans;

pair<int,int> dvs[N];
int prv[N];

void sieve() {
	d[0] = d[1] = 1;
	prime.push_back(0);
	id[0] = 1;
	for (int i = 2; i < N; ++i) if (!d[i]) {
		for (int j = i; j < N; j += i) d[j] = i;
		prime.push_back(i);
		id[i] = prime.size();
	}

	for (int i = 2; i < N; ++i) {
		int tmp = i;
		int x = d[tmp], cnt = 0;
		while(tmp % x == 0) tmp /= x, ++cnt;
		dvs[i] = make_pair(id[x], cnt);
		prv[i] = tmp;
		//cerr << i << "->" << dvs[i].first << ' ' << dvs[i].second << ' ' << prv[i] << endl;
	}
}

int pw(int x, int y) {
	if (y < 0) return 0;
	if (y == 0) return 1;
	int res = 1;
	for (int i = 0; (1LL << i) <= y; ++i) {
		if (y & (1LL << i)) res = 1LL * res * x % md;
		x = 1LL * x * x % md;
	}
	return res;
}

struct SegmentTree {
	int T[N << 2];
	int c[N << 2];
	SegmentTree() { for (int i = 0; i < (N << 2); ++i) T[i] = 1, c[i] = 0; }

	#define mid ((l + r) >> 1)
	void upd(int v, int l, int r, int pos, int val) {
		if (l > r || l > pos || r < pos) return;
		if (l == r) { c[v] += val; T[v] = pw(prime[l-1], c[v]); return; } 
		upd(v << 1, l, mid, pos, val); upd(v << 1 | 1, mid + 1, r, pos, val);
		T[v] = 1LL * T[v << 1] * T[v << 1 | 1] % md;
	}
} seg;

struct FenwickTree {
	int T[N];
	FenwickTree() { memset(T, 0, sizeof T); }
	void upd(int x, int v) { for(; x < N; x += x & -x) T[x] += v; }
	int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res += T[x]; return res; }
} bit;	

void upd(int val, int v) {
	if (val == 0) {
		seg.upd(1, 1, prime.size(), 1, v);
		return;
	}
	while(val > 1) {
		seg.upd(1, 1, prime.size(), dvs[val].first, v * dvs[val].second);
		val = prv[val];
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	sieve();
	cin >> n >> md;
	for (int i = 1; i <= n; ++i) cin >> a[i], t[a[i]]++;
	
	for (int i = 1; i < N; ++i) bit.upd(i, t[i]);
	int s = n;
	
	for (int i = 1; i <= s; ++i) upd(i, +1);
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j <= t[i]; ++j) upd(j, -1);
	}
	
	for (int i = 1; i <= n; ++i) {
		bit.upd(a[i], -1);
		upd(s, -1); --s;

		int nw = bit.get(a[i] - 1);
		upd(nw, +1);

		ans = (ans + seg.T[1]) % md;
		upd(nw, -1);
		upd(t[a[i]], +1); --t[a[i]];
	}

	cout << (ans + 1) % md << endl;
}