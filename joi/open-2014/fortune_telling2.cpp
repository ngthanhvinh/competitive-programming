#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, k;
int a[N], b[N], t[N];
vector<int> z, vec, v;
int res[N], lst[N];
long long ans;

// BIT
int T[N];
void merge(int type, int &x, int y) {
	if (type == 0) x = max(x, y); else x += y;
}
void upd(int type, int x, int v) { for (; x > 0; x -= x & -x) merge(type, T[x], v); }
int get(int type, int x) { int res = 0; for (; x < N; x += x & -x) merge(type, res, T[x]); return res; }

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];
	for (int i = 1; i <= k; ++i) {
		cin >> t[i];
		z.push_back(t[i]);
		vec.push_back(i);
	}
	sort(z.begin(), z.end());
	z.resize(distance(z.begin(), unique(z.begin(), z.end())));
	sort(vec.begin(), vec.end(), [&](int x, int y) {
		return t[x] < t[y];
	});

	for (int i = 1; i <= n; ++i) {
		if (a[i] > b[i]) swap(a[i], b[i]), res[i] = 1;
		v.push_back(i);
	}
	sort(v.begin(), v.end(), [&](int x, int y) {
		return b[x] < b[y];
	});

	int pt = 0;
	for (int i = 0; i < v.size(); ++i) {
		while(pt < vec.size() && t[vec[pt]] < b[v[i]]) {
			upd(0, lower_bound(z.begin(), z.end(), t[vec[pt]]) - z.begin() + 1, vec[pt]);
			++pt;
		}
		int A = lower_bound(z.begin(), z.end(), a[v[i]]) - z.begin() + 1;
		lst[v[i]] = get(0, A);
	}

	memset(T, 0, sizeof T); // reset BIT

	pt = vec.size() - 1;
	for (int i = v.size()-1; i >= 0; --i) {
		while(pt >= 0 && b[v[i]] <= t[vec[pt]]) {
			upd(1, vec[pt], 1);
			--pt;
		}
		if (lst[v[i]] > 0) res[v[i]] = 1;
		int cur = get(1, lst[v[i]] + 1);
		res[v[i]] ^= (cur & 1);
	}

	for (int i = 1; i <= n; ++i) {
		ans += (res[i] == 0 ? a[i] : b[i]);
	}

	cout << ans << '\n';
}