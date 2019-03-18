#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int n, m, k, a[11], res[11];
int MAX;

struct query {
    int u; int v; char c;
    query(int u=0, int v=0, char c='a'): u(u), v(v), c(c) {}
};

query q[110][11];
int mask;

int pos[1<<10];

int do_query(int i, int state) {
    int nxt = 0;
    for (int j = 0; j < n; ++j) {
        int b0 = (state>>q[i][j].u&1), b1 = (state>>q[i][j].v&1), cur;
        if (q[i][j].c == 'a') cur = (b0 & b1); else if (q[i][j].c == 'o') cur = (b0 | b1); else cur = (b0 ^ b1);
        nxt |= (cur << j);
    }
    return nxt;
}

int process(int state) {
    for (int i = 0; i < m; ++i) state = do_query(i, state);
    return state;
}

int solve() {
    memset(pos, 0, sizeof pos);
    int state = mask;
    //cerr << mask << endl;
    pos[mask] = 1;
    int st, cycle = 0;
    for (int j = 1; j <= min(k / m, MAX + 1); ++j) {
        int nxt = process(mask);
        if (!pos[nxt]) mask = nxt, pos[nxt] = j + 1;
        else {
            st = pos[nxt];
            cycle = j + 1 - pos[nxt];
            break;
        }
    }
    if (!cycle) {
        int rem = k % m;
        for (int i = 0; i < k % m; ++i) mask = do_query(i, mask);
        return mask;
    }
    else {
        for (int i = 1; i <= st; ++i) state = process(state);
        int rem = k; rem -= st * m; rem %= (m * cycle);
        for (int i = 0; i < rem; ++i) state = do_query(i % m, state);
        return state;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> k;
    MAX = (1<<n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int u, v; string op; cin >> u >> op >> v;
            q[i][j] = query(u-1, v-1, op[0]);
        }
    }
    for (int i = 0; i < 31; ++i) {
        mask = 0;
        for (int j = 0; j < n; ++j) mask |= (((a[j]>>i)&1) << j);
        mask = solve();
        for (int j = 0; j < n; ++j) if (mask & (1<<j)) res[j] |= (1<<i);
    }
    for (int i = 0; i < n; ++i) cout << res[i] << ' '; cout << endl;
}
/*
2 3 10
1 2
1 and 2
1 or 2

1 or 2
1 xor 2

1 xor 2
1 and 2
*/
