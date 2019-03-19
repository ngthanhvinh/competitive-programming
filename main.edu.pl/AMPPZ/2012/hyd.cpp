#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

int n, deg[N];
vector<int> G[N], R[N]; // reverse edges
int U[N], Z[N];
set < pair<int,int> > s;
long long f[N];
bool del[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> U[i] >> Z[i];
		int r; cin >> r; deg[i] = r;
		while(r--) {
			int u; cin >> u; R[u].push_back(i); G[i].push_back(u);
		}
	}

	for (int i = 1; i <= n; ++i) s.insert(make_pair(Z[i], i));

	while(!s.empty()) {
		set < pair<int,int> >::iterator it = s.begin();
		int u = it->second; s.erase(it);
		queue <int> q; q.push(u); f[u] = Z[u];

		while(!q.empty()) {
			u = q.front(); q.pop(); del[u] = 1;
			for (int v: R[u]) if (!del[v]) {
				deg[v]--;
				if (!deg[v]) {
					q.push(v); f[v] = Z[v]; s.erase(make_pair(Z[v], v));
					long long res = 0;
					for (int w: G[v]) res += f[w]; f[v] = min(f[v], res + U[v]);
				}
			}
		}
	}

	printf("%lld\n", f[1]);
}