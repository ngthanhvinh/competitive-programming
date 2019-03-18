#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> x >> n >> m >> water_cost >> t;

	for (int i = 1; i <= n; ++i) cin >> s[i];

	for (int i = 1; i <= m; ++i) cin >> a[i].first >> a[i].second; // d, refund_cost
	sort(a + 1, a + m + 1);

	sort(s + 1, s + n + 1);
	
}