#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1000010;

int n, x[N], a[N], b[N], tmp[N];
int ind[N];
int par[N], mn = 1e9;
vector <int> comp[N];
long long ans;

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) { p = anc(p); q = anc(q); if (p != q) par[p] = q; }

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", x + i), mn = min(mn, x[i]);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (int i = 1; i <= n; ++i) scanf("%d", b + i);
	for (int i = 1; i <= n; ++i) ind[b[i]] = i;
	for (int i = 1; i <= n; ++i) tmp[i] = x[i]; for (int i = 1; i <= n; ++i) x[ind[i]] = tmp[i];
	for (int i = 1; i <= n; ++i) tmp[i] = a[i]; for (int i = 1; i <= n; ++i) a[i] = ind[tmp[i]];

	for (int i = 1; i <= n; ++i) par[i] = i;
	for (int i = 1; i <= n; ++i) join(i, a[i]);
	for (int i = 1; i <= n; ++i) comp[anc(i)].push_back(x[i]);

	for (int i = 1; i <= n; ++i) if (comp[i].size() > 1) {
		int sz = (int)comp[i].size();
		sort(comp[i].begin(), comp[i].end());
		long long res = 1e18;
		long long cur = 0;
		cur += 1ll * comp[i][0] * (sz - 1);
		for (int j = 1; j < sz; ++j) cur += comp[i][j];
		res = min(res, cur);

		cur = 0;
		cur += mn + comp[i][0];
		cur += 1ll * sz * mn;
		for (int j = 0; j < sz; ++j) cur += comp[i][j];
		res = min(res, cur);

		ans += res;
	}

	printf("%lld\n", ans);
}