#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

int n, q;
int d[N];
int a[N];
int x;
int res[N];

struct Query {
	int t; int l; int r; int id;
	bool operator < (const Query &other) const {
		return t < other.t;
	}
} query[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> d[i];

	x = d[1];
	for (int i = 2; i <= n; ++i) {
		d[i] = max(d[i - 1], ((d[i] + d[1] - 1) / d[1]) * d[1]);
	}
	for (int i = 1; i <= n; ++i) d[i] /= x;

	for (int i = 2; i <= n; ++i) {
		d[i] = ((d[i] + d[i - 1] - 1) / d[i - 1]) * d[i - 1];
	}

	while(q--) {
		int t, l, r; cin >> t >> l >> r;
		int res = 0;
		if (t >= l && t <= r) ++res;
		t /= x;

		for (int i = 1; i <= n; ++i) {
			int k = (t / d[i]) * d[i];
			if (-i + k * x >= l && -i + k * x <= r) ++res;
		}

		printf("%d\n", res);
	}
}