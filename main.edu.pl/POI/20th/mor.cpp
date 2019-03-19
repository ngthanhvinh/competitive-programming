#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int N = 5010, INF = 1e9 + 123;

int n, m, k;
vector<int> G[N];
int d[N][2];

typedef pair<int,int> ii;
void bfs(int s) {
	queue<ii> q; q.push(ii(s,0)); for (int i = 1; i <= n; ++i) d[i][0] = d[i][1] = INF; d[s][0] = 0;
	while(!q.empty()) {
		ii t = q.front(); q.pop(); int u = t.first, mod = t.second;
		for (int i = 0; i < G[u].size(); ++i) {
			int v = G[u][i]; if (d[v][mod^1] == INF) d[v][mod^1] = d[u][mod] + 1, q.push(ii(v,mod^1));
		}
	}
}

struct Query {
	int t; int dis; int id;
	Query(int t=0, int dis=0, int id=0): t (t), dis (dis), id (id) {}
};

vector<Query> q[N];
bool ans[1000010];

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; ++i) {
		int u, v; scanf("%d%d", &u, &v); 
		G[u].push_back(v); G[v].push_back(u);
	} 
	for (int i = 1; i <= k; ++i) { int s, t, dis; scanf("%d%d%d", &s, &t, &dis); q[s].push_back(Query(t,dis,i)); }
	for (int i = 1; i <= n; ++i) {
		bfs(i);
		for (int j = 0; j < q[i].size(); ++j) {
			ans[q[i][j].id] = (q[i][j].dis >= d[q[i][j].t][q[i][j].dis%2] && G[i].size());
		} 
	}
	for (int i = 1; i <= k; ++i) (ans[i]) ? printf("TAK\n") : printf("NIE\n");
}