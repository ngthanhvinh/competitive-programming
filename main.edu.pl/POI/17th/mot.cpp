#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
const int MAX = 1000005;
const int inf = 1e9;
typedef pair<int,int> ii;

int n, k;
int a[N];
int b[N];
int dp[N], trace[N];

pair<int,int> t0[MAX], t1[MAX], t2[MAX];

void upd0(int x, ii v) { for (; x < MAX; x += x & -x) t0[x] = max(t0[x], v); }
ii get0(int x) { ii res = ii(-inf,-inf); for (; x > 0; x -= x & -x) res = max(res, t0[x]); return res; }

void upd2(int x, ii v) { for (; x > 0; x -= x & -x) t2[x] = max(t2[x], v); }
ii get2(int x) { ii res = ii(-inf,-inf); for (; x < MAX; x += x & -x) res = max(res, t2[x]); return res; }

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= k; ++i) {
		char c; cin >> c;
		if (c == '<') b[i] = 0;
		else if (c == '=') b[i] = 1;
		else b[i] = 2;
	}	
	for (int i = k+1; i <= n; ++i) b[i] = b[i-k];

	for (int i = 0; i < MAX; ++i) {
		t0[i] = t1[i] = t2[i] = ii(-inf,-inf);
	}
	for (int i = 1; i <= n; ++i) {
		dp[i] = 1;
		ii t[3];
		t[0] = get0(a[i] - 1);
		t[1] = t1[a[i]];
		t[2] = get2(a[i] + 1);

		ii cur = max({t[0],t[1],t[2]});
		dp[i] = max(dp[i], cur.first + 1);
		if (dp[i] == cur.first + 1) {
			trace[i] = cur.second;
		} else trace[i] = 0;

		if (b[dp[i]] == 0) upd0(a[i], ii(dp[i], i));
		else if (b[dp[i]] == 1) t1[a[i]] = max(t1[a[i]], ii(dp[i], i));
		else upd2(a[i], ii(dp[i], i));
	}

	int k = max_element(dp + 1, dp + n + 1) - dp;
	printf("%d\n", dp[k]);

	vector<int> ans;
	while(k > 0) {
		ans.push_back(a[k]);
		k = trace[k];
	}
	for (int i = (int)ans.size() - 1; i >= 0; --i) {
		printf("%d ", ans[i]);
	}
	printf("\n");
}