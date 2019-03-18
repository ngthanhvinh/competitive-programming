#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

const int N = 11;

int n;
string s;
deque<vi> cand;
vi cur, v;
map <vi, bool> mp;
long long fact[N];
long long ans;

void bt() {
	int sum = 0;
	for (int i = 0; i < n; ++i) sum += v[i] * (i + 1);
	if (sum > n) {
		long long res = fact[n];
		int t = n; for (int i = 0; i < n; ++i) t -= v[i], res /= fact[v[i]];
		if (t < 0) res = 0; else res /= fact[t];
		ans += res;
		return;
	}
	cur.clear();
	for (int i = 0; i < n; ++i) while(v[i]-- > 0) cur.push_back(i + 1);
	while(cur.size() < n) cur.push_back(0);
	sort(cur.begin(), cur.end());
	
	do {
		if (!mp.count(cur)) cand.push_back(cur);
	} while(next_permutation(cur.begin(), cur.end()));
}

void solve() {
	cin >> s;
	cand.clear();
	mp.clear();
	n = s.size();
	ans = 0;

	cur.clear();
	for (int i = 0; i < s.size(); ++i) cur.push_back(s[i]-'0');
	cand.push_back(cur);
	mp[cur] = true;

	while(!cand.empty()) {
		v = cand.front(); cand.pop_front();
		bt();
		++ans;
	}
	printf("%lld\n", ans);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	fact[0] = 1; for (int i = 1; i < N; ++i) fact[i] = 1LL * fact[i-1] * i;
	int tt; cin >> tt;
	for (int i = 1; i <= tt; ++i) {
		printf("Case #%d: ", i);
		solve();
	}
}