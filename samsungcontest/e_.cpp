#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 2e9 + 10000;
typedef pair<int,int> point;
#define x first
#define y second

int N, M, L;
point a[200005];
vector <point> p;

void rot(point &p) {
	p = point(p.x - p.y, p.x + p.y);
}

bool check(int h) {
	vector <point> vec;
	for (int i = 0; i < p.size(); ++i) {
		if (p[i].y - p[i].x <= h) {
			vec.push_back(p[i]);
		}
		if (i + 1 < p.size()) {
			if (p[i].x == p[i + 1].x && p[i].y < p[i].x + h && p[i].x + h < p[i + 1].y) {
				vec.push_back(point(p[i].x, p[i].x + h));
			}
			else if (p[i].y == p[i + 1].y && p[i].x < p[i].y - h && p[i].y - h < p[i + 1].x) {
				vec.push_back(point(p[i].y - h, p[i].y));
			}
		}
	}

	int need = 0;
	int cur = 0;
	int maxr = -INF;
	for (auto &pt : vec) {
		if (cur >= N || need == L) break;
		if (pt.x > cur + 1) {
			if (maxr == -INF) return false;
			cur = maxr;
			maxr = -INF;
			++need;
		}
		if (pt.x <= cur && pt.y >= cur) {
			maxr = max(maxr, pt.y);
		}
	}
	if (cur < N && maxr != -INF) {
		cur = maxr;
		++need;
	}

	return cur >= N && need <= L;
}

void solve() {
	p.clear();
	cin >> N >> M >> L;
	for (int i = 1; i <= M + 1; ++i) {
		cin >> a[i].x >> a[i].y;
		rot(a[i]);
	}

	for (int i = 1; i <= M + 1; ++i) {
		p.push_back(a[i]);
    while (i + 2 <= M + 1 && ( (a[i].x == a[i + 1].x) == (a[i + 1].x == a[i + 2].x) || (a[i].y == a[i + 1].y) == (a[i + 1].y == a[i + 2].y))) i++;
	}

	int low = 0, high = INF;
	while(low < high) {
		int mid = ((low + high) >> 1);
		if (check(mid)) high = mid;
		else low = mid + 1;
	}

	if (!check(low)) {
		cout << -1 << endl;
	} else if (low % 2 == 0) {
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