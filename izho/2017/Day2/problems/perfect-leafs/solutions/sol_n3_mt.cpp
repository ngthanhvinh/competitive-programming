#pragma comment(linker, "/STACK:64000000")
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

#define f first
#define s second
#define pb push_back
#define mp make_pair
#define ll long long
#define pii pair < int, int >
#define pll pair < long long, long long>
#define ull unsigned long long
#define y1 stupid_cmath
#define left stupid_left
#define right stupid_right
#define vi vector <int>
#define sz(a) (int)a.size()
#define forit(it, s) for(__typeof(s.begin()) it = s.begin(); it != s.end(); it++)
#define all(a) a.begin(), a.end()
#define sqr(x) ((x) * (x))

const int inf = (int)1e9;
const int mod = inf + 7;
const double eps = 1e-9;
const double pi = acos(-1.0);

int n;
vector<int> g[100100];
int deg[100100], par[100100];
int tin[100100], tout[100100], timer = 0;

void dfs(int v, int p, int lvl) {
    deg[v] = lvl;
    par[v] = p;
    tin[v] = timer++;
    forit (it, g[v]) {
        int to = *it;
        if (to != p) {
            dfs(to, v, lvl + 1);
        }
    }
    tout[v] = timer++;
}

bool is_parent(int a, int b) {
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

int dist(int a, int b) {
    int ans = 0;
    while (!is_parent(a, b)) {
        a = par[a];
        ans++;
    }
    while (a != b) {
        b = par[b];
        ans++;
    }
    return ans;
}

int get(int a, int b) {
    queue<int> q;
    vector<int> d(n, -1);
    while (!is_parent(a, b)) {
        d[a] = 0;
        q.push(a);
        a = par[a];
    }
    while (b != a) {
        d[b] = 0;
        q.push(b);
        b = par[b];
    }
    if (d[a] == -1) {
        d[a] = 0;
        q.push(a);
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        forit (it, g[v]) {
            int to = *it;
            if (d[to] == -1) {
                q.push(to);
                d[to] = d[v] + 1;
            }
        }
    }
    return *max_element(d.begin(), d.end());
}

int main(){

    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        g[x].pb(y);
        g[y].pb(x);
    }

    dfs(0, -1, 0);

    vector<int> leafs;
    for (int i = 0; i < n; i++) {
        if (sz(g[i]) == 1) leafs.pb(i);
    }

    ll best = 0, cnt = 0;

    for (int ii = 0; ii < leafs.size(); ii++) {
        for (int jj = ii + 1; jj < leafs.size(); jj++) {
            int i = leafs[ii], j = leafs[jj];
            int d = dist(i, j);
            int h = get(i, j);
            if (d * 1ll * h > best) {
                best = d * 1ll * h;
                cnt = 1;
            } else if (d * 1ll * h == best) {
                cnt++;
            }
        }
    }

    printf("%lld %lld\n", best, cnt);

    return 0;
}
