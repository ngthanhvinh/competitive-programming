#include <bits/stdc++.h>
using namespace std;

const int N = 400010;
typedef pair<int,int> ii;
#define fi first
#define se second

int n;
ii a[N], b[N];
int ans;
vector<int> z;
int t[N << 2], s[N << 2];

#define mid ((l + r) >> 1)
void upd(int v, int l, int r, int pos, int x) {
	if (l > r || l > pos || r < pos) return;
	if (l == r) { t[v] += x; s[v] += x; return; }
	upd(v << 1, l, mid, pos, x); upd(v << 1 | 1, mid + 1, r, pos, x);
	t[v] = min(t[v << 1], s[v << 1] + t[v << 1 | 1]);
	s[v] = s[v << 1] + s[v << 1 | 1];
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i].se >> a[i].fi, z.push_back(a[i].fi);
	for (int i = 1; i <= n; ++i) cin >> b[i].se >> b[i].fi, z.push_back(b[i].fi);

	reverse(a + 1, a + n + 1);
	reverse(b + 1, b + n + 1);
	sort(z.begin(), z.end()); z.resize(distance(z.begin(), unique(z.begin(), z.end())));

	int cur = 1;
	for (int i = 1; i <= n; ++i) 
		a[i].fi = lower_bound(z.begin(), z.end(), a[i].fi) - z.begin() + 1,
		b[i].fi = lower_bound(z.begin(), z.end(), b[i].fi) - z.begin() + 1; 
	
	//cerr << endl;
	//for (int i = 1; i <= n; ++i) cerr << a[i].fi << ' ' << a[i].se << endl;
	//for (int i = 1; i <= n; ++i) cerr << b[i].fi << ' ' << b[i].se << endl;
	for (int i = 1; i <= n; ++i) upd(1, 1, N-1, a[i].fi, +1);
	for (int i = 1; i <= n; ++i) upd(1, 1, N-1, b[i].fi, -1);

	multiset<ii> S;
	for (int i = 1; i <= n; ++i) {
		while(cur <= n && a[cur].fi <= b[i].fi) S.insert(ii(a[cur].se, a[cur].fi)), ++cur;
		multiset<ii> ::iterator it = S.lower_bound(ii(b[i].se, 1e9));
		if (it == S.begin()) continue;
		--it;
		int country = (*it).fi;
		if (country != b[i].se) continue;
		int score = (*it).se;
		upd(1, 1, N-1, score, -1);
		upd(1, 1, N-1, b[i].fi, +1);

		if (t[1] < 0) upd(1, 1, N-1, score, +1), upd(1, 1, N-1, b[i].fi, -1);
		else ++ans, S.erase(it);
	}

	cout << n - ans << endl;
}