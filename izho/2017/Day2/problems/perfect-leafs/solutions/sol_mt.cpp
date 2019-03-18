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
pii up[1001000], dp[1001000];
ll best = -inf, ans = -inf;

void update(pii &a, int x, int y) {
    if (x < 0) return;
    if (x > a.f) a = mp(x, y);
    else if (x == a.f) a.s += y;
}

void calc_dp(int v, int par) {
    dp[v] = mp(0, 1);
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        calc_dp(to, v);
        update(dp[v], dp[to].f + 1, dp[to].s);
    }
}

void calc_up(int v, int par) {
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        up[to] = mp(0, 1);
        update(up[to], up[v].f + 1, up[v].s);
    }
    pii cur = mp(-inf, -inf);
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        update(up[to], cur.f + 2, cur.s);
        update(cur, dp[to].f, dp[to].s);
    }
    reverse(all(g[v]));
    cur = mp(-inf, -inf);
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        update(up[to], cur.f + 2, cur.s);
        update(cur, dp[to].f, dp[to].s);
    }
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        calc_up(to, v);
    }
}

int get_cnt(int v, int par, ll val) {
    int res = 0;
    if (up[v].f == val) res += up[v].s;
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        if (dp[to].f + 1 == val) res += dp[to].s;
    }
    return res;
}

ll calc_sum_of_pairwise_sum(int v, int par, ll val) {
    ll res2 = 0, res1 = 0;
    if (up[v].f == val) {
        res2 += up[v].s * 1ll * up[v].s;
        res1 += up[v].s;
    }
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        if (dp[to].f + 1 == val) {
            res2 += dp[to].s * 1ll * dp[to].s;
            res1 += dp[to].s;
        }
    }
    return (res1 * res1 - res2) / 2;
}

void update(pii &a, pii &b, pii &c, int x, int y) {
    if (x > a.f) {
        c = b;
        b = a;
        a = mp(x, y);
    } else if (x > b.f) {
        c = b;
        b = mp(x, y);
    } else if (x > c.f) {
        c = mp(x, y);
    }
}

void calc_ans(int v, int par) {
    pii data1 = mp(-inf, -inf);
    pii data2 = mp(-inf, -inf);
    pii data3 = mp(-inf, -inf);
    if (par != -1) update(data1, data2, data3, up[v].f, up[v].s);
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        update(data1, data2, data3, dp[to].f + 1, dp[to].s);
    }
    if (data3.f != -inf) {
        int mx3 = data3.f, cnt3 = data3.s;
        int mx2 = data2.f, cnt2 = data2.s;
        int mx1 = data1.f, cnt1 = data1.s;
        ll val = (mx2 + mx3) * 1ll * mx1;
        if (val >= best) {
            ll res = 0;
            if (mx1 != mx2 && mx2 != mx3) {
                cnt3 = get_cnt(v, par, mx3);
                res = cnt2 * cnt3;
            } else if (mx1 != mx2 && mx2 == mx3) {
                res = calc_sum_of_pairwise_sum(v, par, mx3);
            } else if (mx1 == mx2 && mx2 != mx3) {
                cnt3 = get_cnt(v, par, mx3);
                res = (cnt1 + cnt2) * cnt3;
            } else if (mx1 == mx2 && mx2 == mx3) {
                res = calc_sum_of_pairwise_sum(v, par, mx3);
            } else {
                assert(false);
            }
            if (val > best) {
                best = val;
                ans = res;
            } else if (val == best) {
                ans += res;
            }
        }
    }
    forit (it, g[v]) {
        int to = *it;
        if (to == par) continue;
        calc_ans(to, v);
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
    up[0] = mp(0, 1);
    calc_up(0, -1);

    calc_ans(0, -1);

    printf("%lld %lld\n", best, ans);

    return 0;
}

