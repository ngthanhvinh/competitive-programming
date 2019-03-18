#include <bits/stdc++.h>
using namespace std;

int a, b, c, k;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> a >> b >> c >> k;
		cout << (long long)min(a, k-1) + (long long)min(b, k-1) + (long long)min(c, k-1) + 1LL << endl;
	}
}