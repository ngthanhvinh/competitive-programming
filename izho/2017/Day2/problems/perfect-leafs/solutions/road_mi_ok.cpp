#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <queue>

#define mp make_pair
#define pb push_back


typedef long long ll;
typedef long double ld;

using namespace std;
const int MAXN = 1000100;
int was[MAXN];
pair<ll, ll> dw[MAXN];
pair<ll, ll> up[MAXN];
vector<int> eds[MAXN];
int n;

void mrg(pair<ll, ll> &a, pair<ll, ll> b) {
	if (a.first < b.first)
		a = b;
	else if (a.first == b.first)
		a.second += b.second;
}

void dfs0(int v) {
	was[v] = 1;
	dw[v] = make_pair(0, 1);
	for (int u: eds[v]) {
		if (was[u])
			continue;
		dfs0(u);
		pair<ll, ll> tmp = dw[u];
		tmp.first += 1;
		mrg(dw[v], tmp);
	}
}

void dfs1(int v, pair<ll, ll> now) {
	up[v] = now;
	pair<ll, ll> mn[2];
	mn[0] = now;
	mn[1] = make_pair(0, 0);
	was[v] = 1;
	for (int u: eds[v]) {
		if (was[u])
			continue;
		pair<ll, ll> tmp = dw[u];
		tmp.first += 1;
		if (mn[0].first == tmp.first) {
			mn[0].second += tmp.second;
		}
		else {
			mrg(mn[1], tmp);
			if (mn[1].first > mn[0].first)
				swap(mn[0], mn[1]);
		}
	}
	for (int u: eds[v]) {
		if (was[u])
			continue;
		if (dw[u].first + 1 == mn[0].first && dw[u].second == mn[0].second)
			dfs1(u, make_pair(mn[1].first + 1, mn[1].second));
		else if (dw[u].first + 1 == mn[0].first)
			dfs1(u, make_pair(mn[0].first + 1, mn[0].second - dw[u].second));
		else
			dfs1(u, make_pair(mn[0].first + 1, mn[0].second));
	}
}

pair<ll, ll> ans;

void dfs2(int v) {
	tuple<ll, ll, ll, ll> mn[3];
	mn[0] = make_tuple(up[v].first, up[v].second, 0, 0);
	mn[1] = make_tuple(0, 0, 0, 0);
	mn[2] = make_tuple(0, 0, 0, 0);
	was[v] = 1;
	for (int u: eds[v]) {
		if (was[u])
			continue;
		dfs2(u);
		int fl = 0;
		for (int i = 0; i < 3; ++i) {
			if (get<0>(mn[i]) == dw[u].first + 1) {
				get<3>(mn[i]) += get<2>(mn[i]) * dw[u].second;
				get<2>(mn[i]) += get<1>(mn[i]) * dw[u].second;
				get<1>(mn[i]) += dw[u].second;
				fl = 1;
				break;
			}
		}
		if (!fl) {
			if (get<0>(mn[2]) < dw[u].first + 1) {
				mn[2] = make_tuple(dw[u].first + 1, dw[u].second, 0, 0);
				if (mn[2] > mn[1])
					swap(mn[2], mn[1]);
				if (mn[1] > mn[0])
					swap(mn[1], mn[0]);
			}
		}
	}
	if (get<3>(mn[0])) {
		ll a = get<0>(mn[0]) * (get<0>(mn[0]) + get<0>(mn[0]));
		ll c = get<2>(mn[0]);
		if (a > ans.first && c)
			ans = make_pair(a, c);
		else if (a == ans.first)
			ans.second += c;
	}
	else if (get<2>(mn[0])) {
		ll a = get<0>(mn[0]) * (get<0>(mn[0]) + get<0>(mn[1]));
		ll c = get<1>(mn[0]) * get<1>(mn[1]);
		if (a > ans.first && c)
			ans = make_pair(a, c);
		else if (a == ans.first)
			ans.second += c;
	}
	else if (get<2>(mn[1])) {
		ll a = get<0>(mn[0]) * (get<0>(mn[1]) + get<0>(mn[1]));
		ll c = get<2>(mn[1]);
		if (a > ans.first && c)
			ans = make_pair(a, c);
		else if (a == ans.first)
			ans.second += c;
	}
	else {
		ll a = get<0>(mn[0]) * (get<0>(mn[1]) + get<0>(mn[2]));
		ll c = get<1>(mn[1]) * get<1>(mn[2]);
		if (a > ans.first && c)
			ans = make_pair(a, c);
		else if (a == ans.first)
			ans.second += c;
	}
}


int main() {
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		--a, --b;
		eds[a].push_back(b);
		eds[b].push_back(a);
	}
	int fl = 0;
	for (int i = 0; i < n; ++i)
		if (eds[i].size() > 2)
			fl = 1;
	if (!fl) {
		cout << 0 << " " << 1 << "\n";
		return 0;
	}
	int st = 0;
	for (int i = 0; i < n; ++i)
		if (eds[i].size() != 1) {
			st = i;
			break;
		}
	dfs0(st);
	memset(was, 0, sizeof(was));
	dfs1(st, make_pair(0, 0));
	memset(was, 0, sizeof(was));
	dfs2(st);
	cout << ans.first << " " << ans.second << "\n";
	return 0;
}


