#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int BASE = 27;
const int md = 1e9 + 123;

map <int,int> mp; int step; // for compressing
vector< pair<int,int> > vec[500005]; int cnt[500005]; // for hashes
int n, l, m;
int pw[N];
string s[N];
int h[N];
int mx[N];
int lst[N];

void add(int x, pair<int,int> cur) {
	if (vec[x].size() && vec[x].back().first == cur.first) return;
	while(!vec[x].empty() && vec[x].back().second <= cur.second) vec[x].pop_back();
	vec[x].push_back(cur);
}

int get(int x, int TIME) {
	int pos = lower_bound(vec[x].begin(), vec[x].end(), make_pair(TIME,(int)-1e9)) - vec[x].begin();
	return vec[x][pos].second;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> l >> m;
	pw[0] = 1; for (int i = 1; i < N; ++i) pw[i] = 1LL * pw[i-1] * BASE % md;
	for (int i = 1; i <= n; ++i) {
		cin >> s[i];
		for (int j = 0; j < l; ++j) h[i] = (1LL * BASE * h[i] + s[i][j] - 'a') % md;
		if (!mp.count(h[i])) mp[h[i]] = ++step;
		cnt[mp[h[i]]]++;
	}

	for (int id = 1; id <= step; ++id) vec[id].push_back(make_pair(0, cnt[id]));

	for (int TIME = 1; TIME <= m; ++TIME) {
		int p1, w1, p2, w2;
		cin >> p1 >> w1 >> p2 >> w2;
		int old1 = mp[h[p1]], old2 = mp[h[p2]];
		// compute new hashes in positions p1 and p2
		h[p1] -= 1LL * (s[p1][w1-1] - 'a') * pw[l-w1] % md; h[p1] %= md;
		h[p2] -= 1LL * (s[p2][w2-1] - 'a') * pw[l-w2] % md; h[p2] %= md;
		swap(s[p1][w1-1], s[p2][w2-1]);
		h[p1] += 1LL * (s[p1][w1-1] - 'a') * pw[l-w1] % md; h[p1] %= md;
		h[p2] += 1LL * (s[p2][w2-1] - 'a') * pw[l-w2] % md; h[p2] %= md;
		if (h[p1] < 0) h[p1] += md; if (h[p2] < 0) h[p2] += md;

		int new1 = h[p1], new2 = h[p2];
		if (!mp.count(new1)) mp[new1] = ++step; new1 = mp[new1];
		if (!mp.count(new2)) mp[new2] = ++step; new2 = mp[new2];
		// update cnt
		if (p1 != p2) {
			cnt[old1]--; cnt[old2]--;
			cnt[new1]++; cnt[new2]++;
		}
		else cnt[old1]--, cnt[new1]++;

		// update mx and lst
		mx[p1] = max(mx[p1], get(old1, lst[p1]));
		mx[p2] = max(mx[p2], get(old2, lst[p2]));
		lst[p1] = TIME;
		lst[p2] = TIME;

		// update vec
		add(old1, make_pair(TIME, cnt[old1]));
		add(old2, make_pair(TIME, cnt[old2]));
		add(new1, make_pair(TIME, cnt[new1]));
		add(new2, make_pair(TIME, cnt[new2]));
	}
	
	for (int i = 1; i <= n; ++i) {
		mx[i] = max(mx[i], get(mp[h[i]], lst[i]));
	}

	for (int i = 1; i <= n; ++i) printf("%d\n", mx[i]);
}