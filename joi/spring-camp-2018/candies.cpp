#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

struct segment {
	int l; int r;
	long long real; long long hidden;
	segment(int l=0, int r=0, long long real=0, long long hidden=0): 
		l(l), r(r), real(real), hidden(hidden) {}
	bool operator < (const segment &other) const {
		return l < other.l || (l == other.l && r < other.r);
	}
};

set <segment> s;
set < pair<long long, pair<int,int> > > pq;
int n, a[N];
long long res;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n;
	s.insert(segment(0, 0, 0, 0));
	s.insert(segment(n + 1, n + 1, 0, 0));
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		s.insert(segment(i, i, 0, a[i]));
		pq.insert(make_pair(a[i], make_pair(i, i)));
	}

	for (int have = 1; have <= (n + 1) / 2; ++have) {
		auto top = (*pq.rbegin()); pq.erase(--pq.end());
		res += top.first;
		
		// update the current segment
		set <segment>::iterator it = s.lower_bound(segment(top.second.first, top.second.second));
		auto cur = (*it);
		swap(cur.real, cur.hidden);

		set <segment>::iterator prv, nxt;

		if (it != s.begin()) {
			prv = prev(it);
			cur.real += (prv -> real); cur.hidden += (prv -> hidden); cur.l = (prv -> l);
			pq.erase(make_pair(prv -> hidden - prv -> real, make_pair(prv -> l, prv -> r)));
		}
		if (it != --s.end()) {
			nxt = next(it);
			cur.real += (nxt ->real); cur.hidden += (nxt -> hidden); cur.r = (nxt -> r);
			pq.erase(make_pair(nxt -> hidden - nxt -> real, make_pair(nxt -> l, nxt -> r)));
		}

		if (it != s.begin()) s.erase(prv);
		if (it != --s.end()) s.erase(nxt);
		s.erase(it);

		s.insert(cur);
		if (cur.l != 0 && cur.r != n + 1) {
			// we cannot increase the number of chosen cells with this type of segment
			pq.insert(make_pair(cur.hidden - cur.real, make_pair(cur.l, cur.r)));
		}

		printf("%lld\n", res);
	}
}