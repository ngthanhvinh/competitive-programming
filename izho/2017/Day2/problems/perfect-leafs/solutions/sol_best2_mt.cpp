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

inline void read(int &x)
{
    char c = '0'; c--;
    x = 0;
    while((c < '0' || c > '9')) c = getchar();
    while((c >= '0' && c <= '9')) x = x * 10 + c - '0', c = getchar();
}

int n;
vector<int> g[1001000];
int up[1001000], dp[1001000];
ll best = -inf, ans = -inf;
vector<int> goods;

void calc_dp(int v, int par) {
    dp[v] = 0;
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        calc_dp(to, v);
        dp[v] = max(dp[v], dp[to] + 1);
    }
}

void calc_up(int v, int par) {
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        up[to] = max(up[to], up[v] + 1);
    }
    int cur = -inf;
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        up[to] = max(up[to], cur + 2);
        cur = max(cur, dp[to]);
    }
    cur = -inf;
    for (int i = sz(g[v]) - 1; i >= 0; i--) {
        int to = g[v][i];
        if (to == par) continue;
        up[to] = max(up[to], cur + 2);
        cur = max(cur, dp[to]);
    }
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        calc_up(to, v);
    }
}

void calc_ans(int v, int par) {
    int data1 = -inf, data2 = -inf, data3 = -inf;
    if (par != -1) {
        if (up[v] > data1) {
            data3 = data2;
            data2 = data1;
            data1 = up[v];
        } else if (up[v] > data2) {
            data3 = data2;
            data2 = up[v];
        } else if (up[v] > data3) {
            data3 = up[v];
        }
    }
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        if (dp[to] + 1 > data1) {
            data3 = data2;
            data2 = data1;
            data1 = dp[to] + 1;
        } else if (dp[to] + 1 > data2) {
            data3 = data2;
            data2 = dp[to] + 1;
        } else if (dp[to] + 1 > data3) {
            data3 = dp[to] + 1;
        }
    }
    if (data3 != -inf) {
        int mx3 = data3;
        int mx2 = data2;
        int mx1 = data1;
        ll val = (mx2 + mx3) * 1ll * mx1;
        if (val > best) {
            best = val;
            goods.clear();
            goods.pb(v);
        } else if (val == best) {
            goods.pb(v);
        }
    }
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        calc_ans(to, v);
    }
}

void dfs(int v, int par, int deg, int &mx, int &cnt) {
    if (deg > mx) {
        mx = deg;
        cnt = 1;
    } else if (deg == mx) cnt++;
    forit (it, g[v]) {
        int to = *it;
        if (to != par) dfs(to, v, deg + 1, mx, cnt);
    }
}

void process(int root) {
    vector<pii> v;
    for (int i = 0; i < g[root].size(); i++) {
        int child = g[root][i];
        int mx = -1, cnt = -1;
        dfs(child, root, 1, mx, cnt);
        v.pb(mp(mx, cnt));
    }
    assert(v.size() >= 3);
    int mx1 = -inf, mx2 = -inf, mx3 = -inf;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].f > mx1) {
            mx3 = mx2;
            mx2 = mx1;
            mx1 = v[i].f;
        } else if (v[i].f > mx2) {
            mx3 = mx2;
            mx2 = v[i].f;
        } else if (v[i].f > mx3) {
            mx3 = v[i].f;
        }
    }
    ll s2 = 0, s = 0, q = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].f == mx3) {
            s2 += v[i].s * 1ll * v[i].s;
            s += v[i].s;
        }
        if (v[i].f == mx2) {
            q += v[i].s;
        }
    }
    if (mx2 == mx3) {
        ans += (s * s - s2) / 2;
    } else {
        ans += s * q;
    }
}

int main(){
    
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);
    
    read(n);
    for (int i = 0, x, y; i < n - 1; i++) {
        read(x);
        read(y);
        x--; y--;
        g[x].pb(y);
        g[y].pb(x);
    }
    
    int leaf_number = 0;
    for (int i = 0; i < n; i++) {
        if (g[i].size() == 1) leaf_number++;
    }
    
    if (leaf_number == 2) {
        printf("0 1\n");
        return 0;
    }
    
    calc_dp(0, -1);

    calc_up(0, -1);

    calc_ans(0, -1);

    ans = 0;
    for (int i = 0; i < goods.size(); i++) {
        process(goods[i]);
    }

    printf("%lld %lld\n", best, ans);
    
    return 0;
}

