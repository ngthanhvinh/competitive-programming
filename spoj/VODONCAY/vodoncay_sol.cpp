#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
const int maxn = (int) 4e6 + 6;
#define fi first
#define se second
#define pb push_back

int n, L[maxn], R[maxn], h[maxn], f[maxn];
ii trace[maxn];

int main() {
    freopen("vodoncay.inp", "r", stdin);
    freopen("vodoncay.ans", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++) cin >> h[i];

	vector<int> st;
	for (int i = 1; i <= n; i ++) {
		L[i] = i;
		while (!st.empty() && st.back() > i - h[i]) {
			L[i] = min(L[i], L[st.back()]);
			st.pop_back();
		}
		st.pb(i);
	}
	st.clear();
	for (int i = n; i >= 1; i --) {
		R[i] = i;
		while (!st.empty() && st.back() < i + h[i]) {
			R[i] = max(R[i], R[st.back()]);
			st.pop_back();
		}
		st.pb(i);
	}
    //for (int i = 1; i <= n; ++i) printf("%d %d %d\n", i, L[i], R[i]);

	st.clear();
	for (int i = 1; i <= n; i ++) {
		f[i] = f[L[i] - 1] + 1;
		trace[i] = ii(-i, L[i] - 1);
		while (!st.empty() && R[st.back()] < i) st.pop_back();
		if(!st.empty() && f[st.back() - 1] + 1 < f[i]) {
			f[i] = f[st.back() - 1] + 1;
			trace[i] = ii(st.back(), st.back() - 1);
		}
		if(!st.empty() && f[i - 1] >= f[st.back() - 1]) continue;
		st.pb(i);
	}
	cout << f[n] << '\n';

	vector<int> ans;
	while (n > 0) {
		ans.pb(trace[n].fi);
		n = trace[n].se;
	}
	reverse(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i ++) cout << ans[i] << ' ';
}
