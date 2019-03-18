#include <bits/stdc++.h>
using namespace std;
typedef pair <int, int> ii;
typedef vector <int> vi;

#define ll long long
#define ff(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define fod(i, a, b) for (int i = (int)(a); i >= (int)(b); i--)
#define pb push_back
#define fi first
#define se second
const int N = 1000010, mod = (int)1e9 + 7, INF = 1e9;

int n, G[N], a[N], low[N], num[N], ans, Time;
stack <int> s;

void dfs(int u) {
	low[u] = num[u] = ++Time; s.push(u);
	int ch = G[u];
	if (num[ch]) low[u] = min(low[u], num[ch]);
	else dfs(ch), low[u] = min(low[u], low[ch]);
	if (low[u] == num[u]) {
		int v = 0, cnt = 0; 
		do {
			v = s.top(); s.pop(); ++cnt;
			low[v] = num[v] = INF;
		} while(v != u);
		if (cnt > 1) ans += cnt;
		else if (cnt == 1 && G[u] == u) ans++;
	}
}

void solve() {
	cin >> n; 
	ff(i, 0, n-1) cin >> a[i], G[i] = (i + a[i] + 1) % n;
	ans = 0; Time = 0; s = stack <int> ();
	ff(u, 0, n-1) low[u] = num[u] = 0;
	ff(i, 0, n-1) if (!num[i]) dfs(i);
	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--) 
		solve();
}