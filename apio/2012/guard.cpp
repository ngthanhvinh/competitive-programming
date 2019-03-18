#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
typedef pair<int,int> ii;
typedef pair<ii, int> II;

int n, m, k;
int l[N], r[N], type[N];
int zero[N];
vector<int> avail;
vector< pair<int,int> > seg;
vector<II> byL;

int f[N];
int mnR[N], val[N];
bool cantDel[N];
vector<int> ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> l[i] >> r[i] >> type[i];
		if (type[i] == 0) zero[r[i] + 1]--, zero[l[i]]++;
	}
	for (int i = 1; i <= n; ++i) {
		zero[i] += zero[i-1];
		if (!zero[i]) avail.push_back(i);
	}
	if (avail.size() == k) {
		for (int p : avail) printf("%d\n", p);
		return 0;
	}
	for (int i = 1; i <= m; ++i) {
		if (type[i]) {
			int L = lower_bound(avail.begin(), avail.end(), l[i]) - avail.begin();
			int R = upper_bound(avail.begin(), avail.end(), r[i]) - avail.begin() - 1;
			if (L >= 0 && L < avail.size() && R >= 0 && R < avail.size() && L <= R) {
				seg.push_back(make_pair(L,R));
			}
		}
	}
	sort(seg.begin(), seg.end(), [&](pair<int,int> p, pair<int,int> q) { // (L,R); being sorted according to R
		return p.second < q.second || (p.second == q.second && p.first < q.first);
	});
	for (int i = 0; i < seg.size(); ++i) byL.push_back(II(seg[i], i));
	sort(byL.begin(), byL.end());
	
	// find f[i]: the number of necessarily chosen points if we only use segments with id >= i
	int ptr = byL.size() - 1;
	int curF = 0, curR = n + 1;
	for (int i = byL.size() - 1; i >= 0; --i) { // ( [L,R], id )
		while(ptr >= 0 && byL[ptr].first.first > byL[i].first.second) {
			if (curR >= byL[ptr].first.second) curR = byL[ptr].first.second, curF = f[byL[ptr].second];
			--ptr;
		}
		f[byL[i].second] = curF + 1;
	}

	// for each L, find val[L] = f[minR]
	for (int i = 1; i <= n; ++i) mnR[i] = n + 1, val[i] = -1e9;
	for (int i = 0; i < seg.size(); ++i) {
		auto it = seg[i];
		if (mnR[it.first] > it.second) mnR[it.first] = it.second, val[it.first] = f[i];
	}

	// for each position i, check whether or not it can be deleted
	for (auto it : seg) if (it.first == it.second) cantDel[it.first] = true; // obviously :)
 
	curR = -1; // reset curR
	int cnt = 0; // current number of necessarily chosen points
	for (int i = 0; i < seg.size(); ++i) {
		if (seg[i].first > curR) curR = seg[i].second, ++cnt;
		int mn = val[curR] + cnt; // total number of necessarily chosen points
		if (mn > k) cantDel[curR] = true;
	}
	for (int i = 0; i < avail.size(); ++i) if (cantDel[i]) ans.push_back(i);

	if (ans.size() == 0) return printf("-1\n"), 0;
	for (int i = 0; i < ans.size(); ++i) printf("%d\n", avail[ans[i]]);
}