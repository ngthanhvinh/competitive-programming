#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

int n, m, sn, sm;
int nelement;
int f[N];
int deg[N];
vector<int> g[N];

bool check(int x) {
    // -m +n
    int add = sn, sub = sm;
    int cur = x;
    while(add || sub) {
        if (sub && cur >= m) --sub, cur -= m;
        else if (add && cur + n <= x) --add, cur += n;
        else return false;
    }
    return true;
}

void solve() {
    cin >> n >> m;
    int gcd = __gcd(n, m);
    sn = m / gcd, sm = n / gcd;

    int low = 0, high = 500000;
    while(low < high) {
        int mid = ((low + high + 1) >> 1);
        if (!check(mid)) low = mid;
        else high = mid - 1;
    }
    
    // build the sequence
    nelement = low;
    for (int i = 0; i <= nelement; ++i) g[i].clear(), deg[i] = 0;

    for (int i = 0; i <= nelement; ++i) {        
        // f[i] < f[i - n]
        if (i >= n) g[i - n].push_back(i), deg[i]++;
        // f[i] > f[i - m]
        if (i >= m) g[i].push_back(i - m), deg[i - m]++;
    }

    queue<int> q;
    for (int i = 0; i <= nelement; ++i) if (!deg[i]) q.push(i);
    int cnt = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        f[u] = cnt++;
        for (int &v : g[u]) {
            if (--deg[v] == 0) q.push(v);
        }
    }

    for (int i = 0; i <= nelement; ++i) f[i] = cnt - 1 - f[i];
    for (int i = 1; i <= nelement; ++i) f[i] -= f[0]; f[0] = 0;

    printf("%d\n", nelement);
    for (int i = 1; i <= nelement; ++i) printf("%d ", f[i] - f[i - 1]);
    printf("\n");
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int tt; cin >> tt;
    while(tt--) {
        solve();
    }
}