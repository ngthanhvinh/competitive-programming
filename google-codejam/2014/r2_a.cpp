#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

int X, n, val, ans;
multiset <int> s;

int solve() {
	cin >> n >> X; s.clear(); ans = 0;
	for (int i = 1; i <= n; ++i) cin >> val, s.insert(val);
	while(!s.empty()) {
		val = (*s.begin()); s.erase(s.begin());
		++ans;
		if (!s.empty()) {
			multiset <int>::iterator it = s.upper_bound(X - val); 
			if (it != s.begin()) {
				--it;
				s.erase(it);
			}
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int it = 1; it <= tt; ++it) {
		printf("Case #%d: %d\n", it, solve());
	}
}