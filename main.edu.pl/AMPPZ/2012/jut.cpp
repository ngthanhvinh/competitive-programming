#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int n;
pair<int,int> a[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i].second >> a[i].first;
	sort(a + 1, a + n + 1);
	
	int c = 0;
	int mx = 1e9;
	for (int i = 1; i <= n; ++i) {
		c += a[i].second;
		mx = min(mx, a[i].first - c);
	}
	cout << mx << endl;
}