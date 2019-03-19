#include <bits/stdc++.h>
using namespace std;

const int N = 610;
const int M = 10010;
const int inf = 1e9 + 7;

struct Point {
	int x; int y; int v;
	Point operator -= (Point other) { x -= other.x; y -= other.y; }
} a[N], b[M];
int n, m;
int f[N][N];

long long cross(Point O, Point A, Point B) {
	A -= O; B -= O;
	return 1LL * A.x * B.y - 1LL * A.y * B.x;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i].x >> a[i].y;
	reverse(a, a + n);
	cin >> m;
	for (int i = 0; i < m; ++i) cin >> b[i].x >> b[i].y >> b[i].v;

	for (int i = 0; i < n; ++i) {
		vector<Point> vec;
		for (int j = 0; j < m; ++j) if (!(b[j].x == a[i].x && b[j].y == a[i].y)) {
			vec.push_back(b[j]);
		}
		sort(vec.begin(), vec.end(), [&](Point p, Point q) {
			return cross(a[i], p, q) > 0;
		});

		int ptr = 0;
		int sum = 0;
		for (int j = 1; j < n; ++j) {
			while(ptr < vec.size() && cross(a[i], vec[ptr], a[(i+j)%n]) > 0) {
				sum += vec[ptr].v;
				++ptr;
			}
			f[i][(i+j)%n] = sum;
		}
	}

	int ans = inf;
	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			for (int k = j+1; k < n; ++k) {
				ans = min(ans, f[i][j] + f[j][k] + f[k][i]);
			}
		}
	}
	ans = -ans;
	for (int i = 0; i < m; ++i) ans += b[i].v;
	cout << ans << '\n';
}