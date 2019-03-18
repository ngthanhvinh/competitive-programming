#include <bits/stdc++.h>
using namespace std;
 
const int N = 1e6 + 5; // TODO: fix
 
struct Node {
	int L; int R; int cnt;
	Node() { L = R = cnt = 0; }
} T[N * 20];
 
int pos[N * 2][2], segl[N * 2], segr[N * 2];
bool color[N * 20]; int cnt; // for bipartite checking
bool vis[N * 20]; // for BFS
int n, peak, version;
pair<int,int> a[N];
vector<int> z;

struct edge {
	int u; int v; int id;
	edge(int u=0, int v=0, int id=0): u(u), v(v), id(id) {}
};
vector<edge> e;
int back[N * 20]; // nodes
int le[N * 60], ri[N * 60]; // edges

#define mid ((l + r) >> 1)
inline int build(int l, int r) {
	if (l == r) {
		pos[l][1] = ++peak; // on
		T[peak].L = T[peak].R = peak; T[peak].cnt = 1;
		pos[l][0] = ++peak; // off
		T[peak].L = T[peak].R = peak;
		return peak; // currently off
	}
	int L = build(l, mid), R = build(mid + 1, r);
	++peak; T[peak].L = L; T[peak].R = R;
	return peak;
}
 
inline int upd(int v, int l, int r, int p, int val) {
	if (l > r || l > p || r < p) return v;
	if (l == r) return pos[p][val];
	int L = upd(T[v].L, l, mid, p, val);
	int R = upd(T[v].R, mid + 1, r, p, val);
	++peak; T[peak].L = L; T[peak].R = R;
	T[peak].cnt = T[T[peak].L].cnt + T[T[peak].R].cnt;
	return peak;
}
 
void add_edges(int u, int v, int id) {
	ri[back[u]] = e.size(); le[e.size()] = back[u]; back[u] = e.size();
	e.push_back(edge(u, v, id)); 
	ri[back[v]] = e.size(); le[e.size()] = back[v]; back[v] = e.size();
	e.push_back(edge(v, u, id)); 
}

inline void add(int cur, int v, int l, int r, int L, int R) {
	if (l > r || R < l || L > r) return;
	if (L <= l && r <= R) {
		// cur and v belong to different sides in the bipartite graph
		if (!T[v].cnt) return; // off
		add_edges(cur, v, 1);
		vis[v] = true;
		return;
	}
	add(cur, T[v].L, l, mid, L, R); add(cur, T[v].R, mid + 1, r, L, R);
}
#undef mid
 
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i].first >> a[i].second;
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i) {
		segl[a[i].first] = i;
		segr[a[i].second] = i;
		z.push_back(a[i].second);
	}
	memset(back, -1, sizeof back);
	sort(z.begin(), z.end());
	z.erase(unique(z.begin(), z.end()), z.end());
	version = build(1, n);
 
	for (int lef = 1; lef <= 2 * n; ++lef) {
		int del = segr[lef - 1];
		int plef = lower_bound(z.begin(), z.end(), lef) - z.begin() + 1;
		if (del) {
			// delete
			version = upd(version, 1, n, plef - 1, 0);
		}
		int cur = segl[lef];
		if (!cur) continue;
		int rig = a[cur].second;
		int prig = lower_bound(z.begin(), z.end(), rig) - z.begin() + 1;
 
		// add
		add(pos[prig][1], version, 1, n, plef, prig);
		// update
		version = upd(version, 1, n, prig, 1);
	}
 
	// BFS
	queue <int> qu;
	for (int i = 1; i <= peak; ++i) if (vis[i]) qu.push(i);
	while(!qu.empty()) {
		int u = qu.front(); qu.pop();
		if (T[T[u].L].cnt) {
			add_edges(u, T[u].L, 0);
			if (!vis[T[u].L]) {
				qu.push(T[u].L);
				vis[T[u].L] = true;
			}
		}
		if (T[T[u].R].cnt) {
			add_edges(u, T[u].R, 0);
			if (!vis[T[u].R]) {
				qu.push(T[u].R);
				vis[T[u].R] = true;
			}
		}
	}
 
	// check for bipartite graph
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= z.size(); ++i) if (!vis[pos[i][1]]) {
		++cnt; color[pos[i][1]] = 0; 
		qu.push(pos[i][1]); vis[pos[i][1]] = 1;
		while(!qu.empty()) {
			int u = qu.front(); qu.pop();
			while(back[u] != -1) {
				int v = e[back[u]].v, id = e[back[u]].id;
				if (!vis[v]) {
					color[v] = (color[u] ^ id); vis[v] = 1; qu.push(v);
				} else if (vis[v] && color[v] != (color[u] ^ id)) {
					printf("0\n"); exit(0); // invalid
				}
				back[u] = le[back[u]];
			}
		}
	}
	int ans = 1;
	while(cnt-- > 0) ans = 2LL * ans % (int)(1e9 + 7);
	printf("%d\n", ans);
}