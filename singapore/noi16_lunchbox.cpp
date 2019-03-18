#include <bits/stdc++.h>
using namespace std;

int n, MAX;
int a[60010];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> MAX >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	sort(a + 1, a + n + 1);
	
	int cur = 0;
	for (int i = 1; i <= n; ++i) {
		if (cur + a[i] > MAX) {
			cout << i - 1 << endl; return 0;
		}
		cur += a[i];
	}
	cout << n << endl;
}