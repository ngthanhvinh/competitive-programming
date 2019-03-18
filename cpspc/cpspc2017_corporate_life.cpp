#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

int n, st1[N], en1[N], st2[N], en2[N], TIME;
int ans[N];
vector<int> g1[N], g2[N];

// BIT
int T[N];
void upd(int x, int v) { for (; x <= n; x += x & -x) T[x] += v; }
int get(int x) { int ret = 0; for (; x > 0; x -= x & -x) ret += T[x]; return ret; }

void dfs1(int u) {
    st1[u] = ++TIME;
    for (int v : g1[u]) dfs1(v);
    en1[u] = TIME;
}

void dfs2(int u) {
    st2[u] = ++TIME;
    for (int v : g2[u]) dfs2(v);
    en2[u] = TIME;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        int p; cin >> p; g1[p].push_back(i);
    }
    for (int i = 2; i <= n; ++i) {
        int p; cin >> p; g2[p].push_back(i);
    }

    TIME = 0; dfs1(1);
    TIME = 0; dfs2(1);

    vector<int> buf, nbuf;

    // st2[x] > st2[y] && st1[x] <= st1[y] <= en1[x]
    for (int i = 1; i <= n; ++i) buf.push_back(i);
    sort(buf.begin(), buf.end(), [&](int x, int y) {
        return st2[x] < st2[y];
    });
    for (int u : buf) {
        ans[u] += get(en1[u]) - get(st1[u] - 1);
        upd(st1[u], +1);
    }

    // st2[y] > en2[x] && st1[x] <= st1[y] <= en1[x]
    memset(T, 0, sizeof T);
    for (int i = 1; i <= n; ++i) nbuf.push_back(i);
    sort(nbuf.begin(), nbuf.end(), [&](int x, int y) {
         return en2[x] < en2[y];
    });
    int ptr = buf.size() - 1;
    for (int i = nbuf.size() - 1; i >= 0; --i) {
        int u = nbuf[i];
        while(ptr >= 0 && en2[u] < st2[buf[ptr]]) {
            upd(st1[buf[ptr]], +1);
            --ptr;
        }
        ans[u] += get(en1[u]) - get(st1[u] - 1);
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d ", en1[i] - st1[i] - ans[i]);
    }
    printf("\n");
}
