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
pii d[1000100];
int n;
ll dis, cnt;
void dfs(int v, int p = -1){
	d[v] = mp(0, 1);
	for(int i = 0; i < g[v].size(); i++){
		int to = g[v][i];
		if(to == p ) {
			continue;
		}
		dfs(to, v);
		pii x = mp(d[to].f + 1, d[to].s);
		if(x.f > d[v].f) d[v]=x;
		else if(x.f == d[v].f) d[v].s += x.s;
	}
}

void get(int v, int p = -1, int mx = 0, int ccnt = 0){
	vector<pii> dd;
	dd.pb(mp(mx, ccnt));
	for(int i = 0; i < g[v].size(); i++){
		int to = g[v][i];
		if(to == p) continue;
		dd.pb(mp(d[to].f + 1, d[to].s));
	}
	sort(all(dd));
	reverse(all(dd));
	if(dd.size() > 2 && dd[2].f != 0){
		ll cur = dd[0].f * 1ll * (dd[1].f + dd[2].f);
		ll cc = 0;
		if(dd[2].f == dd[0].f){
			ll sum = 0;
			for(int i = 0; i < dd.size(); i++){
				if(dd[i].f == dd[0].f) {
					cc += sum * dd[i].s;
					sum += dd[i].s;
				}
			}
		}else if(dd[1].f == dd[0].f){
			ll sum = 0;
			for(int i = 0; i < dd.size(); i++){
				if(dd[i].f == dd[2].f) {
					sum += dd[i].s;
				}
			}
			cc = sum * (d[0].s + d[1].s);
		}else if(dd[1].f == dd[2].f){
			ll sum = 0;
			for(int i = 0; i < dd.size(); i++){
				if(dd[i].f == dd[1].f) {
					cc += sum * dd[i].s;
					sum += dd[i].s;
				}
			}
		}else{
			ll sum = 0;
			for(int i = 0; i < dd.size(); i++){
				if(dd[i].f == dd[2].f) {
					sum += dd[i].s;
				}
			}
			cc = sum * dd[1].s;
		}
		if(dis < cur) {
			dis = cur;
			cnt = 0;
		}
		if(dis == cur){
			cnt += cc;
		}
	}
	pii M = dd[0];
	pii M2 = dd[1];
	for(int i = 1; i < dd.size(); i++){
		if(dd[i].f == M.f){
			M.s += dd[i].s;
		}
	}
	for(int i = 2; i < dd.size(); i++){
		if(dd[i].f == M2.f){
			M2.s += dd[i].s;
		}
	}
	for(int i = 0; i < g[v].size(); i++){
		int to = g[v][i];
		if(to == p) continue;
		int G = M.s;
		int MX = M.f;
		if(M.f == d[to].f + 1){
			G -= d[to].s;
		}
		if(G == 0){
			MX = M2.f;
			G = M2.s;
		}
		get(to, v, MX + 1, G);
	}
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
	int ind = 1;
	for(int i = 1; i <= n; i++){
		if(g[i].size() > 1) ind = i;
	}
	dfs(ind);
	get(ind);
	cout << dis << " "<< cnt << endl;
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

