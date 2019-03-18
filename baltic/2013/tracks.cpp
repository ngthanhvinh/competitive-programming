#include <bits/stdc++.h>
using namespace std;

const int N = 4005;
const int dx[] = {0, 0, -1, +1};
const int dy[] = {-1, +1, 0, 0};

int r, c;
string a[N];
bool vis[N][N];
int ans;

void bfs(queue< pair<int,int> > &q1, queue< pair<int,int> > &q2) {
	if (q1.empty()) return;
	++ans;
	while(!q1.empty()) {
		int x = q1.front().first, y = q1.front().second; q1.pop();
		for (int dir = 0; dir < 4; ++dir) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (nx < 0 || nx >= r || ny < 0 || ny >= c || a[nx][ny] == '.' || vis[nx][ny]) continue;
			vis[nx][ny] = true;
			if (a[nx][ny] != a[x][y]) q2.push(make_pair(nx, ny));
			else q1.push(make_pair(nx, ny));
		}
	}
	bfs(q2, q1);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> r >> c;
	for (int i = 0; i < r; ++i) {
		cin >> a[i]; // 0-based index
	}
	queue < pair<int,int> > q1, q2;
	q1.push(make_pair(0,0));
	vis[0][0] = true;
	bfs(q1, q2);

	printf("%d\n", ans);
}