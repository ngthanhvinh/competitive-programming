#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m, k;

struct Bus {
	int x; int y; int p;
	bool operator < (const Bus &rhs) const {
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}
} a[N];
vector<int> z;
int ans;

int T[N];
void upd(int x, int v) { for (; x < N; x += x & -x) T[x] = max(T[x], v); }
int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res = max(res, T[x]); return res; }

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= k; ++i) {
		cin >> a[i].x >> a[i].y >> a[i].p;
		z.push_back(a[i].y);
	}
	sort(z.begin(), z.end());
	z.resize(distance(z.begin(), unique(z.begin(), z.end())));
	for (int i = 1; i <= k; ++i) {
		a[i].y = lower_bound(z.begin(), z.end(), a[i].y) - z.begin() + 1;
	}
	sort(a + 1, a + k + 1);

	for (int i = 1; i <= k; ++i) {
		int res = get(a[i].y) + a[i].p;
		upd(a[i].y, res);
		ans = max(ans, res);
	}

	cout << ans << endl;
}