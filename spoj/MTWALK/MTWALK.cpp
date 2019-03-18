#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define ff(i, a, b) for(int i = a; i <= b; i++)
#define fo(i, a, b) for(int i = a; i < b; i++)
#define fod(i, a, b) for(int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

const int INF = 1e9, N = 111;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef pair <ii, ii> II;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, a[N][N];
const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
bool check, vis[N][N];

void bfs(int Min, int Max) {
	queue <ii> q; memset(vis, 0, sizeof vis);
	if (a[1][1] >= Min && a[1][1] <= Max) q.push(ii(1, 1));
	else return;
	vis[1][1] = 1;
	while(!q.empty()) {
		int x = q.front().fi, y = q.front().se;
		q.pop();
		fo(i, 0, 4) {
			int X = x + dx[i], Y = y + dy[i];
			if (X < 1 || X > n || Y < 1 || Y > n || vis[X][Y]) continue;
			if (a[X][Y] >= Min && a[X][Y] <= Max) { q.push(ii(X, Y)); vis[X][Y] = 1; }
		}
	} 
	if (vis[n][n]) check = 1;
}

bool f(int x) {
	check = 0;
	for (int Min = 0; Min + x <= 110; Min++) {
		int Max = Min + x;
		bfs(Min, Max);
		if (check) return 1; 
	}
	return 0;
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; ff(i, 1, n) ff(j, 1, n) cin >> a[i][j];
	int l = 0, r = 110;
	while(l != r) {
		int mid = ((l + r) >> 1);
		//cout << "mid = " << mid << "\n";
		bool ok = f(mid);
		//cout << "ok = " << ok << "\n";
		if (ok) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
}