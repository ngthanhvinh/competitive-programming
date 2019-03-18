#include <bits/stdc++.h>
using namespace std;

const int N = 2010;

int n, A[N], B[N], deg[N];
vector<int> G[N];
bool del[N];
int p[N];
int mn[N];
int mx[N];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) G[i].clear(), deg[i] = 0, del[i] = false;
	for (int i = 0; i <= n; ++i) mx[i] = 0, mn[i] = n + 1;
	for (int i = 1; i <= n; ++i) cin >> A[i];
	for (int i = 1; i <= n; ++i) cin >> B[i];

	for (int i = 1; i < n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (A[j] <= A[i]) G[j].push_back(i), deg[i]++;
			if (B[i] <= B[j]) G[i].push_back(j), deg[j]++;
		}
	}

	for (int i = 1; i <= n; ++i) {
		int val = A[i];
		mx[val] = max(mx[val], i);
		if (mx[val - 1] != 0) G[mx[val - 1]].push_back(i), deg[i]++;
	}
	for (int i = n; i >= 1; --i) {
		int val = B[i];
		mn[val] = min(mn[val], i);
		if (mn[val - 1] != n + 1) G[mn[val - 1]].push_back(i), deg[i]++;
	}

	priority_queue <int, vector<int>, greater<int> > pq;
	for (int i = 1; i <= n; ++i) if (!deg[i]) pq.push(i);

	vector<int> ans;
	while(!pq.empty()) {
		int u = pq.top(); pq.pop(); del[u] = true;
		ans.push_back(u);
		for (int v : G[u]) {
			if (del[v]) continue;
			deg[v]--;
			if (!deg[v]) pq.push(v);
		}
	}

	for (int i = 0; i < (int)ans.size(); ++i) p[ans[i]] = i + 1;
	for (int i = 1; i <= n; ++i) printf("%d ", p[i]); printf("\n");
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		printf("Case #%d: ", i);
		solve();
	}
}