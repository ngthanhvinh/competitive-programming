// http://wcipeg.com/problem/noi14p5
// Day 2, Problem 2 - Random Number Generator

#include <bits/stdc++.h>
using namespace std;

const int N = 5005;

int n, m, q;
int x, a, b, c, d;
int T[N * N], pos[N * N];
int l[N], r[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> x >> a >> b >> c >> d;
	cin >> n >> m >> q;

	for (int i = 0; i < n * m; ++i) {
		T[i] = i;
		x = (1LL * a * x * x + 1LL * b * x + c) % d;
		swap(T[i], T[x % (i + 1)]);
	}

	for (int i = 0; i < q; ++i) {
		int u, v; cin >> u >> v; --u; --v;
		swap(T[u], T[v]);
	}

	for (int i = 0; i < n * m; ++i) pos[T[i]] = i;
	for (int i = 0; i < n; ++i) r[i] = m - 1;

	for (int val = 0; val < n * m; ++val) {
		int x = pos[val] / m, y = pos[val] % m;
		if (y < l[x] || y > r[x]) continue;

		cout << val + 1 << ' ';
		for(int i = x - 1; i >= 0; --i) r[i] = min(r[i], y);
		for(int i = x + 1; i < n; ++i) l[i] = max(l[i], y);
	}
}