#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 10001
#define INF 0x3f3f3f3f
using namespace std;
int n;

class Graph{
private:
    int cnt;
    struct Edge{
        int w;
        int to;
        int next;
    };
public:
    Edge e[MAXN << 1];
    int head[MAXN << 1];
    void init(){
        cnt = 0;
        memset(head, -1, sizeof(head));
    }
    void add(int u, int v, int w){
        e[cnt].w = w;
        e[cnt].to = v;
        e[cnt].next = head[u];
        head[u] = cnt++;
    }
}g;

class Segment_Tree{
#define lchild rt << 1, l, m
#define rchild rt << 1 | 1, m + 1, r
private:
    int node[MAXN << 2];
    void push_up(int rt){
        node[rt] = max(node[rt << 1], node[rt << 1 | 1]);
    }
public:
    void update(int P, int val, int rt = 1, int l = 1, int r = n){
        if (l == r){ node[rt] = val; return; }
        int m = (l + r) >> 1;
        if (P <= m) update(P, val, lchild);
        else update(P, val, rchild);
        push_up(rt);
    }
    int query(int L, int R, int rt = 1, int l = 1, int r = n){
        if (L <= l && r <= R) return node[rt];
        int m = (l + r) >> 1, ret = -INF;
        if (L <= m) ret = max(ret, query(L, R, lchild));
        if (R > m) ret = max(ret, query(L, R, rchild));
        return ret;
    }
};

class HLD : public Segment_Tree{
public:
    int dep[MAXN], son[MAXN], fa[MAXN], sz[MAXN];
    int top[MAXN], dfn[MAXN], dfs_clock;

    void init(){
        memset(dep, 0, sizeof(dep));
        memset(son, 0, sizeof(son));
        dep[1] = 1;
        dfs_clock = 0;
    }

    void dfs1(int u){
        sz[u] = 1;
        for (int i = g.head[u]; ~i; i = g.e[i].next){
            int v = g.e[i].to;
            if (!dep[v]){
                fa[v] = u;
                dep[v] = dep[u] + 1;
                dfs1(v);
                sz[u] += sz[v];
                if (sz[son[u]] < sz[v])
                    son[u] = v;
            }
        }
    }

    void dfs2(int u, int tp){
        top[u] = tp;
        dfn[u] = dfs_clock++;
        if (son[u]) dfs2(son[u], tp);
        for (int i = g.head[u]; ~i; i = g.e[i].next){
            int v = g.e[i].to;
            if (v != son[u] && v != fa[u])
                dfs2(v, v);
        }
    }

    int getmax(int u, int v){
        int ans = -INF;
        while (top[u] != top[v]){
            if (dep[top[u]] > dep[top[v]]) swap(u, v);
            ans = max(ans, query(dfn[top[v]], dfn[v]));
            v = fa[top[v]];
        }
        if (u == v) return ans;
        if (dep[u] > dep[v]) swap(u, v);
        ans = max(ans, query(dfn[son[u]], dfn[v]));
        return ans;
    }
}hld;

int main(){
#ifdef _DEBUG
    freopen("d:\\QTREE.txt", "r", stdin);
#endif
    char opt[8];
    int t, u, v, w, a, b, x;
    scanf("%d", &t);
    while (t--){
        scanf("%d", &n);
        g.init();
        for (int i = 1; i < n; i++){
            scanf("%d %d %d", &u, &v, &w);
            g.add(u, v, w);
            g.add(v, u, w);
        }
        hld.init();
        hld.dfs1(1);
        hld.dfs2(1, 1);
        for (int i = 0; i < ((n - 1) << 1); i += 2){
            u = g.e[i].to;
            v = g.e[i | 1].to;
            w = g.e[i].w;
            if (hld.dep[u] > hld.dep[v]) swap(u, v);
            hld.update(hld.dfn[v], w);
        }
        while (scanf("%s", opt), opt[0] != 'D'){
            scanf("%d %d", &a, &b);
            switch (opt[0])
            {
            case 'Q':
                printf("%d\n", hld.getmax(a, b));
                break;
            case 'C':
                a--;
                x = hld.dep[g.e[a << 1].to] > hld.dep[g.e[(a << 1) | 1].to] ? g.e[a << 1].to : g.e[(a << 1) | 1].to;
                hld.update(hld.dfn[x], b);
                break;
            }
        }
    }
    return 0;
}