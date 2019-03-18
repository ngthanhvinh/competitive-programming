#include <bits/stdc++.h>
using namespace std;

const int N = 405;
const int INF = 1e9 + 123;

int n;
bool dp[N][N];

struct segment {
	int l; int r; int id;
	bool operator < (const segment &other) const {
		return l < other.l || (l == other.l && r < other.r);
	}
} a[N];

bool intersect(int i, int j) {
	if (!i || !j) return false;
	if (a[i].l > a[j].r || a[j].l > a[i].r) return false;
	return true;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n;
	int low = INF;
	int high = -INF;
	for (int i = 1; i <= n; ++i) {
		int l, r;
		cin >> l >> r;
		a[i * 2 - 1] = {l, (l + r) >> 1, i};
		a[i * 2] = {(l + r) >> 1, r, i};
		low = min(low, l);
		high = max(high, r);
	}
	n *= 2;
	sort(a + 1, a + n + 1);

	// solve
	for (int i = 1; i <= n; ++i) {
		if (a[i].l == low) {
			dp[i][0] = true; // only segment a[i]
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < i; ++j) if (a[i].id != a[j].id && a[i].r > a[j].r) {
			for (int k = 0; k < j; ++k) {
				if (dp[j][k] && intersect(i, j) && !intersect(i, k)) {
					dp[i][j] = true;
				}
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		if (a[i].r != high) continue;
		for (int j = 0; j < i; ++j) {
			if (dp[i][j]) {
				return printf("YES\n"), 0;
			}
		}
	}

	printf("NO\n");
}