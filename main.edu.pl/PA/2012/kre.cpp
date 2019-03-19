#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
typedef pair<long double, long double> Point;

map<Point, bool> mp;

struct Circle {
	int x; int y; // coordinates of the center
	int r; // radius
} circle[N];

struct Line {
	int id; int type; int x; int y;
	Line(int id=0, int type=0, int x=0, int y=0): id(id), type(type), x(x), y(y) {}
	bool operator < (const Line &rhs) const {
		return x < rhs.x || (x == rhs.x && type < rhs.type) || (x == rhs.x && type == rhs.type && y < rhs.y);
	}
};
vector<Line> sweep;
int n;
set< pair<int,int> > s;
set< pair<int,int> >::iterator iter; 

set< pair<int,int> >::iterator Next(set< pair<int,int> >::iterator it) { return ++it; }
set< pair<int,int> >::iterator Prev(set< pair<int,int> >::iterator it) { return --it; }

void find(int i, int j) {
	// find the intersection of circle[i] and circle[j]
	Point intersect = Point();
	long long sqdist = 1LL * (circle[i].x - circle[j].x) * (circle[i].x - circle[j].x) + 1LL * (circle[i].y - circle[j].y) * (circle[i].y - circle[j].y);
	if (sqdist > 1LL * (circle[i].r + circle[j].r) * (circle[i].r + circle[j].r)) return; // circle[i] and circle[j] do not touch each other

	int dist = circle[i].r + circle[j].r;

	intersect.first  = circle[i].x + (long double)(1LL * circle[i].r * (circle[j].x - circle[i].x)) / dist;
	intersect.second = circle[i].y + (long double)(1LL * circle[i].r * (circle[j].y - circle[i].y)) / dist;
	mp[intersect] = true;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> circle[i].x >> circle[i].y >> circle[i].r;
		sweep.push_back(Line(i, -1, circle[i].x - circle[i].r, circle[i].y)); // in
		sweep.push_back(Line(i, +1, circle[i].x + circle[i].r, circle[i].y)); // out
	}
	sort(sweep.begin(), sweep.end());

	for (auto cur : sweep) {
		int i = cur.id; // id of the current circle
		if (cur.type < 0) {
			s.insert(make_pair(cur.y, i)); // insert
			iter = s.find(make_pair(cur.y, i));
			if (iter != s.begin()) {
				find((*Prev(iter)).second, i);
			}
			if (iter != s.end() && Next(iter) != s.end()) {
				find((*Next(iter)).second, i);
			}
		} else {
			iter = s.find(make_pair(cur.y, i));
			int prv = 0, nxt = 0; // previous and next circles in the set
			if (iter != s.begin()) prv = (*Prev(iter)).second;
			if (iter != s.end() && Next(iter) != s.end()) nxt = (*Next(iter)).second;
			if (prv && nxt) find(prv, nxt);
			s.erase(iter); // pop
		}
	}
	cout << mp.size() << endl;
}