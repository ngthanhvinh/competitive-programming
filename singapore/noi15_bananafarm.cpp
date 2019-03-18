#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m;
int a[N];
vector<int> z;
vector<int> vec[N * 4];

#define mid ((l + r) >> 1)
void build(int v, int l, int r) {
	for (int i = l; i <= r; ++i) vec[v].push_back(a[i]);
	sort(vec[v].begin(), vec[v].end());
	if (l == r) return;
	build(v << 1, l, mid); build(v << 1 | 1, mid + 1, r);
}

int get(int v, int l, int r, int L, int R, int val) {
	if (l > r || R < l || L > r) return 0;
	if (L <= l && r <= R) {
		// count the number of elements that are >= val
		int pos = lower_bound(vec[v].begin(), vec[v].end(), val) - vec[v].begin();
		// pos ... vec[v].size() - 1
		return vec[v].size() - pos;
	}
	return get(v << 1, l, mid, L, R, val) + get(v << 1 | 1, mid + 1, r, L, R, val);
}
#undef mid

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i), z.push_back(a[i]);
	build(1, 1, n);
	sort(z.begin(), z.end());
	z.erase(unique(z.begin(), z.end()), z.end());

	while(m--) {
		int l, r, num; scanf("%d %d %d", &l, &r, &num);
		int low = 0, high = z.size() - 1;
		while(low < high) {
			int mid = ((low + high + 1) >> 1);
			if (get(1, 1, n, l, r, z[mid]) >= num) low = mid;
			else high = mid - 1;
		}
		printf("%d\n", z[low]);
	}
}