#include <bits/stdc++.h>
using namespace std;
const int N = 10010;
typedef vector <int> vi;

int n;
long long f[N][4], Min[N][4], Mn1[N], Mn2[N];
int color[N], pos1[N], pos2[N];
bool vis[N];
vector <vi> G;

void dfs(int u) {
	vis[u] = 1;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!vis[v]) {
			dfs(v);
			for (int x = 1; x <= 3; x++) {
				f[u][x] += Min[v][x];
			}
		}
	}
	for (int x = 1; x <= 3; x++) f[u][x] += x; 
	long long mn1 = 1e18, Pos1 = 0;
	
	for (int x = 1; x <= 3; x++) if (mn1 > f[u][x]) { mn1 = f[u][x]; Pos1 = x; }
	long long mn2 = 1e18, Pos2 = 0;
	for (int x = 1; x <= 3; x++) if (x != Pos1 && mn2 > f[u][x]) { mn2 = f[u][x]; Pos2 = x; }
	pos1[u] = Pos1, pos2[u] = Pos2; Mn1[u] = mn1, Mn2[u] = mn2;
	//cout << "dfs " << u << ' ' << pos1[u] << ' ' << pos2[u] << ' ' << Mn1[u] << ' ' << Mn2[u] << "\n";
	for (int x = 1; x <= 3; x++) 
		if (x == Pos1) Min[u][x] = mn2;
		else Min[u][x] = mn1;
}

void trace(int u, int x) {
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i]; if (color[v]) continue;
		if (Min[v][x] == Mn1[v]) color[v] = pos1[v];
		else color[v] = pos2[v];
		trace(v, color[v]);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; G.assign(n + 1, vi());
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		G[u].push_back(v); G[v].push_back(u);
	}
	dfs(1); long long mn = 1e18;
	for (int i = 1; i <= 3; i++) if (mn > f[1][i]) { mn = f[1][i]; color[1] = i; }
	trace(1, color[1]);
	printf("%lld\n", mn);
	for (int i = 1; i <= n; i++) printf("%d\n", color[i]);
}