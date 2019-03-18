#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int N = 1010;

int n;
int x[N], y[N];

long long dist(int i, int j) { return 1ll * (x[i]-x[j]) * (x[i]-x[j]) + 1ll * (y[i]-y[j]) * (y[i]-y[j]); }

int par[N];
int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) { par[anc(p)] = anc(q); }

bool check(long long l) {
    for (int i = 1; i <= n; ++i) par[i] = i;
    for (int i = 1; i < n; ++i) {
        for (int j = i+1; j <= n; ++j) if (dist(i,j) <= l) join(i,j);
    }
    int a = anc(1);
    for (int i = 1; i <= n; ++i) if (anc(i) != a) return 0;
    return 1;
}

int main() {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n; for (int i = 1; i <= n; ++i) cin >> x[i] >> y[i];
    long long l = 0, r = 1e12;
    while(l != r) {
        long long mid = ((l + r) >> 1);
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << endl;
}
