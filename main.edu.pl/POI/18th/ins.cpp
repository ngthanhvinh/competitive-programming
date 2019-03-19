#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;

int n, sz[N];
vector<int> G[N];
int f[N];
int in1[N], in2[N], out[N];
long long s_in[N], s_out[N];
vector <int> ch[N];
int best[N];

typedef pair<int,int> ii;

void dfs(int u, int p) {
	sz[u] = 1; f[u] = 0; in1[u] = -1e9; in2[u] = -1e9;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i]; if (v == p) continue;
		dfs(v, u);
		sz[u] += sz[v];
		s_in[u] += s_in[v] + sz[v];

		int A = in1[u], B = in2[u], C = in1[v] + 1;
		if (A < B) swap(A,B); if (A < C) swap(A,C); if (B < C) swap(B,C);
		in1[u] = A;
		in2[u] = B;

		if (n % 2 == 0 && sz[v] == n / 2) best[u] = v;
		if (sz[v] > n / 2) f[u] = -1;
	}
	if (n % 2 == 0 && n - sz[u] == n / 2) best[u] = -1;
	if (n - sz[u] > n / 2) f[u] = -1;
	if (in1[u] == -1e9) in1[u] = 0;
}

void redfs(int u, int p) {
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i]; if (v == p) continue;
		out[v] = out[u] + 1;
		s_out[v] += s_out[u] + s_in[u] - s_in[v] + n - 2 * sz[v];
		out[v] = max(out[v], (in1[v] == in1[u] - 1 ? in2[u] + 1 : in1[u] + 1));
		
		//cerr << v << ' ' << out[v] << ' ' << ndout[v] << endl;
		redfs(v, u);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		G[u].push_back(v); G[v].push_back(u);
	}
	dfs(1,1);
	redfs(1,1);
	//for (int i = 1; i <= n; ++i) cerr << i << ' ' << best[i] << endl;
	for (int i = 1; i <= n; ++i) {
		if (f[i] == -1) printf("-1\n");
		else {
			long long ans = 2LL * s_in[i] + 2LL * s_out[i];

			if (!best[i]) ans -= max(out[i], in1[i]);
			else {
				if (best[i] == -1) ans -= out[i];
				else ans -= (in1[best[i]] + 1);
			}
			printf("%lld\n", ans);
		}
	}
}
