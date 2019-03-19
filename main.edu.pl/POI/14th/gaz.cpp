#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

struct Point {
	int x; int y; int id;
	bool operator < (const Point &rhs) const {
		return x < rhs.x || (x == rhs.x && y > rhs.y);
	}
} a[N];

int dist(Point p, Point q) {
	return abs(p.x - q.x) + abs(p.y - q.y);
}

int n;
int match[N];
long long ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y, a[i].id = i;
	for (int i = 1; i <= n; ++i) cin >> a[i+n].x >> a[i+n].y, a[i+n].id = -i;
	
	sort(a + 1, a + n * 2 + 1);

	set < pair<int,int> > s;
	for (int i = 1; i <= n * 2; ++i) {
		if (a[i].id > 0) {
			s.insert(make_pair(a[i].y, i));
		} else {
			a[i].id = -a[i].id;
			set < pair<int,int> >::iterator iter = s.lower_bound(make_pair(a[i].y, 0));
			
			int cur = (*iter).second;
			s.erase(iter);

			match[a[i].id] = a[cur].id;
			ans += dist(a[i], a[cur]);
		}
	}

	printf("%lld\n", ans);
	for (int i = 1; i <= n; ++i) printf("%d %d\n", i, match[i]);
}