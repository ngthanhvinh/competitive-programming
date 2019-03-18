#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
const int inf = 1e9;

int n, a[N];
long long nday;
vector<int> G[N];
pair<int,int> fin[N], fout[N], L[N], R[N];
int to[N];
int pos[N];
int cyc[N], cnt;

inline void dfs(int u, int p) {
    for (int v : G[u]) if (v != p) {
        dfs(v, u);
        fin[u] = max(fin[u], make_pair(fin[v].first - 1, fin[v].second));
        fin[u] = max(fin[u], make_pair(a[v] - 1, -v));
    }
}

vector<int> ch;
vector< pair<int,int> > val;
inline void up(int u, int p) {
    ch.clear();
    val.clear();
    for (int v : G[u]) if (v != p) {
        ch.push_back(v);
        pair<int,int> cur = max(fin[v], make_pair(a[v], -v));
        cur.first--;
        val.push_back(cur);
    }

    int sz = ch.size();
    L[0] = make_pair(-inf, -inf); for (int i = 1; i <= sz; ++i) L[i] = max(L[i - 1], val[i - 1]);
    R[sz + 1] = make_pair(-inf, -inf); for (int i = sz; i >= 1; --i) R[i] = max(R[i + 1], val[i - 1]);

    for (int i = 1; i <= sz; ++i) {
        int v = ch[i - 1];
        fout[v] = max(L[i - 1], R[i + 1]);
        fout[v] = max(fout[v], fout[u]);
        fout[v] = max(fout[v], make_pair(a[u], -u));
        fout[v].first--;
    }

    for (int v : G[u]) if (v != p) up(v, u);
}

void out() {
    int start = 0;
    int cycle = 0;
    int cur = 1;
    cyc[0] = 1; pos[1] = 0;
    while(cycle == 0) { // have not found cycle yet
        cur = to[cur]; ++cnt;
        if (pos[cur] == -1) cyc[cnt] = cur, pos[cur] = cnt;
        else {
            start = pos[cur];
            cycle = cnt - start;
        }
    }
    if (nday < start) {
        printf("%d\n", cyc[nday]);
    } else {
        nday -= start;
        printf("%d\n", cyc[start + nday % cycle]);
    }
}

int main() {
    scanf("%d %lld", &n, &nday);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i < n; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        G[u].push_back(v); G[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) pos[i] = -1;
    for (int i = 1; i <= n; ++i) fin[i] = fout[i] = make_pair(-inf, -inf);

    dfs(1, -1);
    up(1, -1);
    for (int i = 1; i <= n; ++i) {
        pair<int,int> cur = max(fin[i], fout[i]);
        to[i] = -cur.second;
    }
    out();
}
