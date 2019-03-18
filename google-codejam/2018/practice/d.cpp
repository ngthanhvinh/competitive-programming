#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll n, k;
map <ll, ll> mp;

void solve() {
	cin >> n >> k;
	mp.clear();
	mp[n] = 1;
	priority_queue < pair<ll, ll> > pq;
	pq.push(make_pair(n, 1));

	while(!pq.empty()) {
		auto top = pq.top(); pq.pop();
		ll len = top.first;
		ll cnt = top.second;
		if (cnt != mp[len]) continue;
		mp[len] = 0;

		ll lef = (len + 1) / 2 - 1;
		ll rig = len - 1 - lef;

		k -= cnt;
		if (k <= 0) {
			printf("%lld %lld\n", rig, lef);
			return;
		}
		if (lef > 0) mp[lef] += cnt, pq.push(make_pair(lef, mp[lef]));
		if (rig > 0) mp[rig] += cnt, pq.push(make_pair(rig, mp[rig]));
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int tt; cin >> tt;
	for (int itest = 1; itest <= tt; ++itest) {
		printf("Case #%d: ", itest);
		solve();
	}
}