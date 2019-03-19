#include <bits/stdc++.h>
using namespace std;

const int N = 300010;
struct Point {
	int x; int y; int type; int dir;
	// type = -1: corner of the mirror trap
	Point(int x=0, int y=0, int type=0): x(x), y(y), type(type) {}
} a[N];
/* directions of the lazer
2 3
1 0
*/

int WALL[][2] = { {0,1}, {1,2}, {2,3}, {3,0} };  

int n;
pair<int,int> rmq[N][4], tmp[N][4];

// to compare points
int VAL;
bool cmp(int p, int q) { return a[p].x + VAL * a[p].y < a[q].x + VAL * a[q].y || (a[p].x + VAL * a[p].y == a[q].x + VAL * a[q].y && a[p].x < a[q].x); }

int which(int pos, int dir, vector<int> &vec) {
	int cur = pos, nxt = (dir == 0 || dir == 3) ? pos + 1 : pos - 1;
	if (nxt < 0 || nxt >= vec.size()) return -1;
	cur = vec[pos]; nxt = vec[nxt];
	if (a[cur].x + VAL * a[cur].y != a[nxt].x + VAL * a[nxt].y) return -1;
	return nxt;
}

void upd(int x, int dir, int y) {
	if (a[y].type == -1) { rmq[x][dir] = make_pair(y, dir); return; }
	int ndir = (dir + 2) % 4;
	for (int i = 0; i < 2; ++i) {
		if (WALL[a[y].type][i] == ndir) {
			rmq[x][dir] = make_pair(y, WALL[a[y].type][i^1]);
			break;
		}
	}
}

int match[N];
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i].x >> a[i].y, a[i].type = -1;
	int tot = n;

	// add new points which are located on the edges of the mirror trap
	for (int i = 0; i < n; ++i) {
		int j = (i + 1) % n;
		int type;
		if (a[i].x < a[j].x) type = 0; else if (a[i].x > a[j].x) type = 2;
		else if (a[i].y < a[j].y) type = 3; else type = 1;

		for (int X = a[i].x + 1; X <= a[j].x - 1; ++X) a[tot++] = Point(X, a[i].y, type);
		for (int X = a[j].x + 1; X <= a[i].x - 1; ++X) a[tot++] = Point(X, a[i].y, type);
		for (int Y = a[i].y + 1; Y <= a[j].y - 1; ++Y) a[tot++] = Point(a[i].x, Y, type);
		for (int Y = a[j].y + 1; Y <= a[i].y - 1; ++Y) a[tot++] = Point(a[i].x, Y, type);
	}

	// calculate the direction of each corner
	for (int i = 0; i < n; ++i) {
		Point lst = a[(i - 1 + n) % n], cur = a[i], nxt = a[(i + 1) % n];
		int add = 0;
		if (lst.x == cur.x) {
			add = 1;
			swap(lst.x, lst.y), swap(cur.x, cur.y), swap(nxt.x, nxt.y);
			lst.x = -lst.x, cur.x = -cur.x, nxt.x = -nxt.x;
		}

		int dir;
		if (lst.x < cur.x && cur.y < nxt.y) dir = 0;
		else if (lst.x < cur.x && cur.y > nxt.y) dir = 1;
		else if (lst.x > cur.x && cur.y < nxt.y) dir = 3;
		else dir = 2;
		a[i].dir = (dir + add) % 4;
	}

	// prepare for rmq
	for (int i = 0; i < tot; ++i) {
		for (int dir = 0; dir < 4; ++dir) rmq[i][dir] = make_pair(i,dir);
	}
	for (int CASE = 0; CASE < 2; ++CASE) {
		VAL = CASE == 0 ? -1 : +1;
		vector <int> vec;
		for (int i = 0; i < tot; ++i) {
			if (a[i].type != -1) vec.push_back(i); else if (a[i].dir % 2 == (CASE ^ 1)) vec.push_back(i);
		}
		sort(vec.begin(), vec.end(), cmp);

		for (int pos = 0; pos < vec.size(); ++pos) {
			if (a[vec[pos]].type == -1) {
				int nxt = which(pos, a[vec[pos]].dir, vec);
				if (nxt != -1) upd(vec[pos], a[vec[pos]].dir, nxt);
			} else {
				for (int i = 0; i < 2; ++i) if (WALL[a[vec[pos]].type][i] % 2 == (CASE ^ 1)) {
					int nxt = which(pos, WALL[a[vec[pos]].type][i], vec);
					if (nxt != -1) upd(vec[pos], WALL[a[vec[pos]].type][i], nxt);
				}
			}
		}
	}

	// use RMQ to find the destination of each lazer
	for (int j = 1; j < 20; ++j) {
		for (int i = 0; i < tot; ++i) for (int dir = 0; dir < 4; ++dir) {
			tmp[i][dir] = rmq[i][dir];
		}
		for (int i = 0; i < tot; ++i) for (int dir = 0; dir < 4; ++dir) {
			rmq[i][dir] = tmp[tmp[i][dir].first][tmp[i][dir].second];
		}
	}

	vector< pair<int,int> > ans;
	for (int i = 0; i < n; ++i) match[i] = -1;
	for (int i = 0; i < n; ++i) if (match[i] == -1) {
		int dest = rmq[i][a[i].dir].first;
		if (dest < n) match[i] = dest, match[dest] = i, ans.push_back(make_pair(i, dest));
	}

	printf("%d\n", ans.size());
	for (auto &it : ans) printf("%d %d\n", it.first + 1, it.second + 1);
}