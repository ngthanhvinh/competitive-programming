#include "dungeon2.h"
#include <bits/stdc++.h>
using namespace std;
 
// Move(I, V)
// NumberOfRoads()
// LastRoad()
// Color()
 
static const int N = 205;
static const int inf = 1e9;
 
static int n;
static int topar[N], par[N];
static vector< pair<int,int> > tochild[N];
static vector<int> up[N];
static int sz[N], uppar[N][N];
 
static int f[N][N];
static int cnt[N];
static int dep[N], pw = 1;
 
void dfs(int u) {
    sz[u] = NumberOfRoads();
    topar[u] = LastRoad();
 
    for (int i = 1; i <= sz[u]; ++i) if (i != topar[u]) {
        Move(i, 2); // color = 1
        int new_color = Color();
        if (new_color == 1) {
            ++n;
            par[n] = u;
            f[u][n] = f[n][u] = 1;
            dep[n] = dep[u] + 1;
            tochild[u].push_back(make_pair(i, n)); // (id_edge, vertex)
 
            dfs(n);
        } else {
            if (new_color == 2) up[u].push_back(i);
            Move(LastRoad(), new_color);
        }
    }
 
    // color = 2
    if (topar[u] != -1) Move(topar[u], 3);
}
 
void interactive(int u) {
    int color = (dep[u] / pw) % 3;
    for (int i : up[u]) {
        Move(i, color + 1);
        int new_color = Color() - 1;
        uppar[u][i] += pw * new_color;
        Move(LastRoad(), new_color + 1);
    }
    for (auto e : tochild[u]) {
        Move(e.first, color + 1); // id_edge
        interactive(e.second); // current node
    }
 
    if (topar[u] != -1) Move(topar[u], color + 1); // move to the parent of u
}
 
void solve() {
    ++n;
    dfs(1);
 
    for (int i = 0; i < 5; ++i) {
        interactive(1);
        pw *= 3;
    }
 
    // rebuild the edges
    for (int i = 1; i <= n; ++i) {
        for (int j : up[i]) {
            // jump
            int u = i;
            while(dep[u] > uppar[i][j]) u = par[u];
            f[u][i] = f[i][u] = 1;
        }
    }
}
 
void Inspect(int R) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) f[i][j] = inf;
    }
    solve();
 
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }
 
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) cnt[f[i][j]]++;
    }
 
    for (int i = 1; i <= R; ++i) {
        Answer(i, cnt[i]);
    }
}