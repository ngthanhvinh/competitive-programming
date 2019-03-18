#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int MAX = 1500005;
const int INF = 1e9;

typedef pair<int, int> ii;

int n, a[N], id;
int at[MAX];
int best[MAX];
map <int, int> mp[N];

int dp(int v, int val) {
	if (val == INF) return v; // empty vector
	if (mp[v].find(val) != mp[v].end()) {
		return at[mp[v][val]];
	}

	mp[v][val] = ++id;
	int curid = id;
	int l = (v * 2 <= n) ? a[v * 2] : INF;
	int r = (v * 2 + 1 <= n) ? a[v * 2 + 1] : INF;

	int w[3] = {val, l, r};
	if (w[0] < min(w[1], w[2])) {
		dp(v << 1, w[1]);
		dp(v << 1 | 1, w[2]);
		return at[curid] = v;
	}
	else if (w[1] < min(w[0], w[2])) {
		dp(v << 1 | 1, w[2]);
		return at[curid] = dp(v << 1, w[0]);
	}
	else {
		// -> w[2], w[0], w[1]
		// -> w[2], w[1], w[0]

		if (w[0] < w[1]) {
			int p = dp(v << 1, w[0]);
			int q = dp(v << 1 | 1, w[0]);
			best[curid] = p < q ? 0 : 1;
			if (p < q) dp(v << 1 | 1, w[1]);
			else dp(v << 1, w[1]);

			return at[curid] = min(p, q);
		}

		int p = dp(v << 1, w[1]);
		int q = dp(v << 1 | 1, w[1]);

		if (p < q) {
			best[curid] = 1;
			return at[curid] = dp(v << 1 | 1, w[0]); 
		} else {
			best[curid] = 0;
			return at[curid] = dp(v << 1, w[0]);
		}
	}
}

void trace(int v, int val) {
	if (val == INF) return;
	int l = (v * 2 <= n) ? a[v * 2] : INF;
	int r = (v * 2 + 1 <= n) ? a[v * 2 + 1] : INF;

	int w[3] = {val, l, r};
	if (w[0] < min(w[1], w[2])) {
		a[v] = w[0];
		trace(v << 1, w[1]);
		trace(v << 1 | 1, w[2]);
	}
	else if (w[1] < min(w[0], w[2])) {
		a[v] = w[1];
		trace(v << 1, w[0]);
		trace(v << 1 | 1, w[2]);
	}
	else {
		a[v] = w[2];
		int curid = mp[v][val];
		trace(v << 1, w[best[curid]]);
		trace(v << 1 | 1, w[best[curid] ^ 1]);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}

	dp(1, a[1]);
	trace(1, a[1]);

	for (int i = 1; i <= n; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
}