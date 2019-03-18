#include <bits/stdc++.h>
using namespace std;

#define int long long
typedef pair<int,int> point;
#define x first
#define y second

int N, M, L;
point a[200005];
vector <point> p;
int l[200005], r[200005];

void rot(point &p) {
	p = point(p.x - p.y, p.x + p.y);
}

bool check(int h) {
	int ptr = 0;
	int cur = 0;
	int rem = L;

	while(cur < N && rem) {
		while(ptr < p.size() && p[ptr].x <= cur) ++ptr; --ptr;

		int wh = cur + h;
		if (p[ptr].x == cur) {
			wh = min(wh, r[ptr]);
			if (wh < l[ptr]) return false;
			--rem;
			cur = wh;
		} else { // cur > p[ptr].x
			if (ptr == p.size() - 1) return false;
			else {
				if (wh < p[ptr].y) cur = p[ptr].x;
				else {
					wh = p[ptr].y;
					cur = wh;
					--rem;
				}
			}
		}
	}

	if (cur >= N) return true;
	return false;
}

void solve() {
	cin >> N >> M >> L;
	p.clear();
	// -> rotate: (0, 0) -> (N, N)
	for (int i = 1; i <= M + 1; ++i) {
		cin >> a[i].x >> a[i].y;
		rot(a[i]);
	}

	for (int i = 1; i <= M; ++i) {
		if (a[i].y == a[i + 1].y) {
			p.push_back(a[i]);
			int sz = p.size() - 1;
			l[sz] = a[i].y, r[sz] = a[i].y;
			if (i > 1 && a[i - 1].x == a[i].x) {
				l[sz] = a[i - 1].y;
			}
		}
	}
	p.push_back(a[M + 1]);
	int sz = p.size() - 1;
	l[sz] = a[M + 1].y, r[sz] = a[M + 1].y;
	if (a[M].x == a[M + 1].x) {
		l[sz] = a[M].y;
	}

	int low = 1, high = 2e9;
	while(low < high) {
		int mid = ((low + high) >> 1);
		if (check(mid)) {
			high = mid;
		} else {
			low = mid + 1;
		}
	}

	if (!check(low)) {
		cout << -1 << endl;
	}
	else if (low % 2 == 0) {
		cout << low / 2 << ' ' << 1 << endl;
	} else {
		cout << low << ' ' << 2 << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int ntest; cin >> ntest;
	for (int itest = 1; itest <= ntest; ++itest) {
		cout << "Case #" << itest << endl;
		solve();
	}
}