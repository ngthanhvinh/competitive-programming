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

const int INF = 1e9, N = 1010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m, X, Y, res[4 * N], ans = INF; 
bool vis[N][N][2], a[N][N];
// |\| 0
// |/| 1
bool in(int x, int y) { return (x >= 1 && x <= n && y >= 1 && y <= m); }

void dfs(int x, int y, int part, int cnt) {
	// cout << x << ' ' << y << ' ' << ' ' << part << ' ' << cnt << ' ';
	// (a[x][y]) ? cout << "| / |" : cout << "| \\ |"; cout << "\n";
	vis[x][y][part] = 1;
	if (x == n && ((!part && !a[x][y]) || (part && a[x][y]))) { res[cnt]++; return; }
	if (part == 0 && !a[x][y]) {
		X = x, Y = y - 1; if (in(X, Y) && !vis[X][Y][1]) dfs(X, Y, 1, cnt + 1);
		X = x + 1, Y = y; 
		if (in(X, Y)) { 
			if (!a[X][Y] && !vis[X][Y][1]) dfs(X, Y, 1, cnt + 1); 
			else if (a[X][Y] && !vis[X][Y][0]) dfs(X, Y, 0, cnt + 1); 
		}
	}
	
	if (part == 1 && !a[x][y]) {
		X = x, Y = y + 1; 
		if (in(X, Y) && !vis[X][Y][0]) dfs(X, Y, 0, cnt + 1);
		X = x - 1, Y = y; 
		if (in(X, Y)) { 
			if (!a[X][Y] && !vis[X][Y][0]) dfs(X, Y, 0, cnt + 1); 
			else if (a[X][Y] && !vis[X][Y][1]) dfs(X, Y, 1, cnt + 1); 
		}
		
	}

	if (part == 0 && a[x][y]) {
		X = x, Y = y - 1; if (in(X, Y) && !vis[X][Y][1]) dfs(X, Y, 1, cnt + 1);
		X = x - 1, Y = y; 
		if (in(X, Y)) { 
			if (a[X][Y] && !vis[X][Y][1]) dfs(X, Y, 1, cnt + 1); 
			else if (!a[X][Y] && !vis[X][Y][0]) dfs(X, Y, 0, cnt + 1); 
		}
	}
	if (part == 1 && a[x][y]) {
		X = x, Y = y + 1; if (in(X, Y) && !vis[X][Y][0]) dfs(X, Y, 0, cnt + 1);
		X = x + 1, Y = y; 
		if (in(X, Y)) { 
			if (a[X][Y] && !vis[X][Y][0]) dfs(X, Y, 0, cnt + 1); 
			else if (!a[X][Y] && !vis[X][Y][1]) dfs(X, Y, 1, cnt + 1); 
		}
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	ff(i, 1, n) ff(j, 1, m) cin >> a[i][j];
	
	ff(i, 1, m) {
		if (a[1][i] == 0) dfs(1, i, 1, 1);
		else dfs(1, i, 0, 1);
	}
	
	fo(i, 0, 4 * N) if (res[i]) ans = min(ans, i);
	if (ans != INF) printf("%d %d\n", ans, res[ans]);
	else printf("0 0\n");
}