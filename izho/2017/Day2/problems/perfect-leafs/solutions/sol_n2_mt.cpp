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
vector<int> g[1001000];
ll best = -inf, ans = 0;
int dp[1001000];
int is_leaf[1001000];

void calc_dp(int v, int par) {
    dp[v] = 0;
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        calc_dp(to, v);
        dp[v] = max(dp[v], dp[to] + 1);
    }
}

inline void dfs(int v, int par, int deg, int up_mx, ll &best, ll &ans) {
    if (is_leaf[v]) {
        ll val = up_mx * 1ll * deg;
        if (val > best) {
            ans = 1;
            best = val;
        } else if (val == best) {
            ans++;
        }
    }
    int mx1 = -inf, to1 = -inf;
    int mx2 = -inf, to2 = -inf;
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        int val = dp[to] + 1;
        if (val > mx1) {
            mx2 = mx1; to2 = to1;
            mx1 = val; to1 = to;
        } else if (val > mx2) {
            mx2 = val; to2 = val;
        }
    }
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        int send_up_mx_val = up_mx;
        if (to == to1) send_up_mx_val = max(send_up_mx_val, mx2);
        else send_up_mx_val = max(send_up_mx_val, mx1);
        dfs(to, v, deg + 1, send_up_mx_val, best, ans);
    }
}

void solve(int root) {
    if (!is_leaf[root]) return;
    is_leaf[root] = 0;
    calc_dp(root, -1);
    ll cur_best = -inf, cur_ans = -inf;
    dfs(root, -1, 0, 0, cur_best, cur_ans);
    if (cur_best > best) {
        best = cur_best;
        ans = cur_ans;
    } else if (cur_best == best) {
        ans += cur_ans;
    }
    is_leaf[root] = 1;
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

    for (int i = 0; i < n; i++) {
        is_leaf[i] = g[i].size() == 1;
    }

    for (int i = 0; i < n; i++) {
        if (is_leaf[i]) solve(i);
    }

    printf("%lld %lld\n", best, ans / 2);

    return 0;
}
