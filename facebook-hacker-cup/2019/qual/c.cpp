#include <bits/stdc++.h>
using namespace std;

const char cand_vals[] = {'0', '1', 'x', 'X'};
const char cand_ops[] = {'^', '&', '|'};

int calc(int a, int b, char c) {
	if (c == '|') return (a | b);
	if (c == '^') return (a ^ b);
	if (c == '&') return (a & b);
	return -1;
}

bool check(string &s) {
	int ans[2] = { -1, -1};
	for (int x = 0; x < 2; ++x) {
		stack <char> ops;
		stack <int> vals;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == '(') continue;
			else if (s[i] == ')') {
				assert(vals.size() >= 2);
				assert(ops.size() >= 1);
				int a = vals.top(); vals.pop();
				int b = vals.top(); vals.pop();
				char c = ops.top(); ops.pop();
				vals.push(calc(a, b, c));
			}
			else if (s[i] == 'x') vals.push(x);
			else if (s[i] == 'X') vals.push(!x);
			else if (s[i] == '0' || s[i] == '1') {
				vals.push(s[i] - '0');
			}
			else {
				ops.push(s[i]);
			}
		}
		assert(vals.size() >= 1);
		ans[x] = vals.top();
	}

	// cerr << s << ' ' << ans[0] << ' ' << ans[1] << endl;
	return ans[0] == ans[1];
}

void solve() {
	string s; cin >> s;
	int res = 1e9;
	for (int i = 0; i < s.size(); ++i) {
		char cur = s[i];
		if (cur == '(' || cur == ')') {
			continue;
		}
		if (cur == 'x' || cur == 'X' || cur == '0' || cur == '1') {
			for (int j = 0; j < 4; ++j) {
				s[i] = cand_vals[j];
				if (check(s)) {
					res = min(res, (int)(cur != cand_vals[j]));
				}
			}
		}
		if (cur == '^' || cur == '|' || cur == '&') {
			for (int j = 0; j < 3; ++j) {
				s[i] = cand_ops[j];
				if (check(s)) {
					res = min(res, (int)(cur != cand_ops[j]));
				}
			}
		}
		s[i] = cur;
	}

	printf("%d\n", res);
}

int main() {
	int t; cin >> t;
	for (int it = 1; it <= t; ++it) {
		printf("Case #%d: ", it);
		solve();
	}
}