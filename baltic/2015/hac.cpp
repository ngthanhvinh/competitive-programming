#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

int n;
int a[N], f[N];
int ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	int sz = (n + 1) / 2;

	for (int i = n + 1; i <= 2 * n; ++i) a[i] = a[i - n];

	for (int i = 1; i <= n + n; ++i) a[i] = a[i - 1] + a[i];

	for (int i = sz; i <= n + n; ++i) {
		f[i] = a[i] - a[i - sz];
		//cerr << i << ' ' << f[i] << endl;
	}

	deque <int> q;

	for (int i = 1; i <= n + n; ++i) {
		while(!q.empty() && f[q.back()] > f[i]) q.pop_back();
		if (!q.empty() && q.front() <= i - sz) q.pop_front();
		q.push_back(i);
		ans = max(ans, f[q.front()]);
	}

	cout << ans << endl;
}