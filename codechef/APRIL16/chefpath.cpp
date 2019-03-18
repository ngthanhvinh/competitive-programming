#include <bits/stdc++.h>
using namespace std;

long long n, m;
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> m >> n;
		if (m < n) swap(n, m);
		if (n % 2 == 1 && m % 2 == 1) cout << "No\n";
		else if (n == 1 && m == 2) cout << "Yes\n";
		else if (n == 1) cout << "No\n"; 
		else cout << "Yes\n";
	}
}