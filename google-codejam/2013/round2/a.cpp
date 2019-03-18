#include <bits/stdc++.h>
using namespace std;

const int md = 1000002013;

int n, m;

int calc(int l, int r, int p) {
	int add = 1LL * (r - l) * n % md;
	add = (add - 1LL * (r - l - 1) * (r - l) / 2) % md;
	if (add < 0) add += md;
	add = 1LL * add * p % md;
	return add;
}

long long solve() {
	cin >> n >> m;
	vector < pair<int,int> > paren;

	int origin = 0;
	for (int i = 1; i <= m; ++i) {
		int l, r, p; cin >> l >> r >> p;
		paren.push_back(make_pair(l, -p));
		paren.push_back(make_pair(r, p));
		int add = calc(l, r, p);
		origin = (origin + add) % md;
	}

	sort(paren.begin(), paren.end());
	stack < pair<int,int> > st;
	
	int ans = 0;
	for (auto &cur : paren) {
		int r = cur.first, p = cur.second;
		if (p < 0) {
			st.push(cur);
		} else {
			while(p > 0) {
				pair<int,int> lst = st.top(); st.pop();
				int lst_p = -lst.second, l = lst.first;
				if (lst_p == p) {
					ans = (ans + calc(l, r, p)) % md; p = 0; lst_p = 0;
				} else if (lst_p > p) {
					ans = (ans + calc(l, r, p)) % md; lst_p -= p; p = 0;
					st.push(make_pair(l, -lst_p));
				} else {
					ans = (ans + calc(l, r, lst_p)) % md; p -= lst_p;
				}
 			}
		}
	}
	ans = (origin - ans) % md; if (ans < 0) ans += md;
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		printf("Case #%d: %d\n", i, solve());
	}
}