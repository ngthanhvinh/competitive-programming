#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

int n, s[N], e[N];
vector<int> g[N];
int color[N];
bool invalid;

bool overlap(int i, int j) {
    return !(e[i] <= s[j] || e[j] <= s[i]);
}

void dfs(int u) {
    for (int &v : g[u]) {
        if (color[v] && color[v] != (3 ^ color[u])) {
            invalid = true;
            return;
        }
        else if (!color[v]) {
            color[v] = (3 ^ color[u]);
            dfs(v);
        }
    }
}

void solve() {
    cin >> n;
    invalid = false;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i] >> e[i];
        g[i].clear();
        color[i] = 0;
    }

    for (int i = 1; i < n; ++i) {
        for (int j = i+1; j <= n; ++j) {
            if (overlap(i, j)) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    for (int i = 1; i <= n; ++i) if (!color[i]) {
        color[i] = 1;
        dfs(i);
    }

    if (invalid) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (int i = 1; i <= n; ++i) {
        cout << (color[i] == 1 ? 'J' : 'C');
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int ntest; cin >> ntest;
    for (int itest = 1; itest <= ntest; ++itest) {
        cout << "Case #" << itest << ": ";
        solve();
    }
}