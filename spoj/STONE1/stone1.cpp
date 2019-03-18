#include <bits/stdc++.h>
using namespace std;

typedef vector <int> vi;
const int N = 401;
#define ff(i, a, b) for (int i = a; i <= b; i++)

int n, f[N], par[N];
vector <vi> G;

bool check(int val, vi a) {
    ff(i, 0, a.size() - 1) {
        if(val >= a[i]) val--;
        else return 0;
    }
    return 1;
}

void dfs(int u) {
    if (G[u].empty()) { f[u] = 1; return; }
    vi Child;
    ff(i, 0, (int)G[u].size()-1) {
        int v = G[u][i]; dfs(v);
        Child.push_back(f[v]);
    }
    sort(Child.begin(), Child.end(), greater<int>());
    int l = 1, r = n;
    while(l != r) {
        int mid = ((l+r)>>1);
        if (check(mid, Child)) r = mid;
        else l = mid + 1;
    }
    f[u] = l;
}

int main() {
    //freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n; G.assign(n + 1, vi());
    int u;
    while(cin >> u) {
        int m; cin >> m;
        while(m--) { int v; cin >> v; par[v] = u; G[u].push_back(v); }
    }

    dfs(1);
    printf("%d\n", f[1]);
}
