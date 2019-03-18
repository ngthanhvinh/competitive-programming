#include "aliens.h"
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

struct ConvexHullTrick {
	// slopes are different from each other
	struct Line {
		long long a; long long b; int id; // b <= 1e12, a >= -2e6
		// id is the ID of the corresponding segment, which is useful for tracing
		Line(long long a=0, long long b=0, int id=0): a(a), b(b), id(id) {}
	};
	deque<Line> L;

	ConvexHullTrick() { L.clear(); }

	bool bad(Line l1, Line l2, Line l3) {
		return 1LL * (l1.b - l3.b) * (l2.a - l1.a) < 1LL * (l1.b - l2.b) * (l3.a - l1.a); // ~ [-2e18, 2e18]
	}
	void add(long long a, long long b, int id) {
		Line d = Line(a, b, id);
		while(L.size() >= 2 && bad(L[L.size()-2], L[L.size()-1], d)) L.pop_back();
		L.push_back(d);
	}
	long long func(Line &d, long long &x) {
		return 1LL * d.a * x + d.b;
	}
	pair<long long,int> get(long long x) {
		while(L.size() >= 2 && func(L[0], x) > func(L[1], x)) L.pop_front(); // L[0] is not good anymore
		return make_pair(func(L[0], x), L[0].id); // get the minimum ID
	}
} cht;

namespace Solver {
	const int N = 100005;
	pair<int, int> inp[N]; // input segments
	int l[N], r[N]; // leftmost and rightmost points of the segments
	int n, m, k;
	long long dp[N];
	int trace[N];

	void process() { // build new segments
		// no segment is contained by another segment
		sort(inp, inp + n, [&](pair<int,int> x, pair<int,int> y) {
			return x.fi < y.fi || (x.fi == y.fi && x.se > y.se);
		});
		int rmax = -1;
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			if (rmax < inp[i].se) {
				rmax = inp[i].se;
				++cnt;
				l[cnt] = inp[i].fi;
				r[cnt] = inp[i].se;
			}
		}
		n = cnt; // 1-based index now
	}

	int check(long long cost) {
		// reset
		cht = ConvexHullTrick();
		memset(dp, 0, sizeof dp);
		memset(trace, 0, sizeof trace);

		// dp[i] = (dp[j-1] - (max(0, r[j-1] - l[j]) ^ 2) + l[j] ^ 2) + (-2 * l[j]) * r[i] + r[i] ^ 2 (j <= i)

		// solve
		cht.add(-2 * l[1], 1LL * l[1] * l[1], 0);
		for (int i = 1; i <= n; ++i) {
			pair<long long, int> g = cht.get(r[i]);
			dp[i] = g.fi + 1LL * r[i] * r[i] + cost;
			trace[i] = g.se;
			long long cur = dp[i] - (1LL * max(0, r[i] - l[i+1]) * max(0, r[i] - l[i+1])) + 1LL * l[i+1] * l[i+1]; // b
			cht.add(-2 * l[i+1], cur, i);
		}

		// trace
		int pos = n, cnt = 0;
		while(pos) ++cnt, pos = trace[pos];
		return cnt;
	}

	long long solve() {
		process();

		long long l = 0, r = 1e13; // cost is positive
		while(l < r) {
			long long mid = ((l + r) >> 1);
			if (check(mid) <= k) r = mid; else l = mid + 1;
		}
		check(l);
		return dp[n] - l * k;
	}
};

long long take_photos(int n, int m, int k, vector<int> r, vector<int> c) {
	// init
	Solver::n = n;
	Solver::m = m; // square: [0...m-1][0...m-1]
	Solver::k = k;
	for (int i = 0; i < n; ++i) {
		if (r[i] > c[i]) swap(r[i], c[i]); // [r,c] is the corresponding segment in the diagonal
		Solver::inp[i].fi = r[i];
		Solver::inp[i].se = ++c[i];
	}

	// solve
	return Solver::solve();
}
