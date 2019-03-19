#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 4;

int m, n;
vector< pair<int,int> > v;
int b[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> m >> n;
	for (int i = 1; i <= n; ++i) cin >> b[i];
	sort(b + 1, b + n + 1, greater<int>());

	if (b[1] == m) return printf("0\n"), 0;

	int lst = m+1;
	int cnt = 0;
	int cur = 0;
	for (int i = 1; i <= n; ++i) {
		if (b[i] == lst - 1) ++cnt, lst = b[i];
		else {
			if (cur > 0) v.push_back(make_pair(cur, cnt));
			cur += lst - b[i] - 1, lst = b[i], cnt = 1;
		}
	}
	if (cnt > 0) v.push_back(make_pair(cur, cnt));

	if (v[0].first == 1) {
		return printf("%d\n", v[0].second), 0;
	}

	int nim = 0;
	for (auto &cur : v) if (cur.first % 2 == 1) nim ^= cur.second;
	if (!nim) {
		return printf("0\n"), 0;
	}

	int ans = 0;
	for (int i = 0; i < v.size(); ++i) {
		if (v[i].first == 2) continue;
		if (v[i].first & 1) {
			for (int j = 1; j <= v[i].second; ++j) {
				int curnim = nim ^ v[i].second ^ (v[i].second - j);
				if (curnim == 0) ++ans;
			}
		} else {
			int prv = (i && v[i].first == v[i-1].first + 1) ? v[i-1].second : 0;
			for (int j = 1; j <= v[i].second; ++j) {
				int curnim = nim ^ prv ^ (prv + j);
				if (curnim == 0) ++ans;
			}
		}
	}
	printf("%d\n", ans);
}