#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <ctime>

#define pb push_back
#define ll long long
#define mp make_pair
#define f first
#define s second
#define pii pair < int, int >
#define ull unsigned long long
#define pll pair < ll, ll >
#define forit(it, s) for(__typeof(s.begin()) it = s.begin(); it != s.end(); it ++)
#define all(s) s.begin(), s.end()
#define sz(a) (int)a.size()

const int inf = (1ll << 30) - 1;
const int maxn = (int) 1e5 + 10;

using namespace std;
vector<int> g[1000100];
int d[1000100];
int d2[1000100];
int n;
int dis, cnt;
int X;
void dfs(int v, int p = -1){
	d[v] = 0;
	d2[v] = 0;
	for(int i = 0; i < g[v].size(); i++){
		int to = g[v][i];
		if(to == p ) continue;
		dfs(to, v);
		if(d[v] < d[to] + 1){
			d2[v] = d[v];
			d[v] = d[to] + 1;
		}
		else if(d2[v] < d[to] + 1){
			d2[v] = d[to] + 1;
		}
	}
}

void get(int v, int p = -1, int mx = 0, int lev = 0){
	int ccnt = 0;
	for(int i = 0; i < g[v].size(); i++){
		int to = g[v][i];
		if(to == p) continue;
		ccnt++;
		int mx2 = mx;
		if(d[v] == d[to] + 1) mx2 = max(mx2, d2[v]);
		else mx2 = max(d[v], mx2);
		get(to, v, mx2, lev + 1);
	}
	if(ccnt > 0) return;
	if(X >= v) return;
	int cur = lev * mx; 
	if(dis < cur){
		dis = cur;
		cnt = 0;
	}
	if(cur == dis)
		cnt++;

}

void calc(int x){
	X = x;
	dfs(X);
	get(X);
}

void solve(){
	scanf("%d", &n);
	for(int i = 1, x, y; i < n; i++){
		scanf("%d%d", &x, &y);
		g[x].pb(y);
		g[y].pb(x);
	}
	if(n == 2){
		printf("0 1\n");
		return;
	}
	pii ans = mp(0, 0);
	for(int i = 1; i <= n; i++){
		if(g[i].size()==1){
			calc(i);
		}
	}
	printf("%d %d\n", dis, cnt);
}

int main () {
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
    int t=1;
    //scanf("%d", &t);
    for(int i=1; i <= t; i++){
      //printf("Case #%d\n", i);
      solve();
    }

    return 0;
}

