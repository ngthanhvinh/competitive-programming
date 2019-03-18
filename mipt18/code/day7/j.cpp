#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int MAGIC = 335;
const int MAX = 1 << 20;
const int INF = 1e9;

int n, k, q;
int a[N], t[6], f[N];
int offset[N / MAGIC + 20];
bitset <MAX> bs[N / MAGIC + 20];
// for Dijkstra
vector <int> z;
int zpos[MAX];
int dis[50];

void prepare() {
	for (int i = 0; i < n; ++i) {
		f[i] = ((i > 0 ? f[i - 1] : 0) ^ a[i]);
		bs[i / MAGIC].set(f[i]);
	}
}

void upd(int pos, int x) {
	int block = pos / MAGIC;
	bs[block].reset();
	for (int i = block * MAGIC; i < n && i < (block + 1) * MAGIC; ++i) {
		f[i] ^= offset[block];
		if (i >= pos) f[i] ^= (a[pos] ^ x);
		bs[block].set(f[i]);
	}
	offset[block] = 0;

	for (int bl = block + 1; bl <= (n - 1) / MAGIC; ++bl) {
		offset[bl] ^= (a[pos] ^ x);
	}
	a[pos] = x;
}

int find_in(int l, int block, int pre) { 
	// l: starting position of finding progress
	int r = min(n - 1, (block + 1) * MAGIC - 1);
	if (!bs[block][pre ^ offset[block]]) return INF;
	for (int i = l; i <= r; ++i) {
		if ((f[i] ^ offset[block]) == pre) return i;
	}
	return INF;
}

int find(int start, int pre) {
	int st_block = start / MAGIC;
	int ret = find_in(start, st_block, pre);
	if (ret != INF) return ret;

	for (int bl = st_block + 1; bl <= (n - 1) / MAGIC; ++bl) {
		ret = find_in(bl * MAGIC, bl, pre); 
		if (ret != INF) return ret;
	}

	return INF;
}

typedef pair<int,int> ii;
void dijkstra() {
	priority_queue < ii, vector <ii>, greater<ii> > pq;
	for (int i = 0; i < z.size(); ++i) dis[i] = INF;

	for (int i = 0; i < k; ++i) {
		dis[zpos[t[i]]] = find(0, t[i]);
		pq.push(ii(dis[zpos[t[i]]], zpos[t[i]]));
	}

	while(!pq.empty()) {
		ii top = pq.top(); pq.pop();
		int u = top.second, du = top.first;
		if (du != dis[u]) continue;
		if (du == INF) continue;

		u = z[u];
		//cerr << "sumxor " << u << ' ' << du << endl;
		for (int i = 0; i < k; ++i) {
			int nxt = (u ^ t[i]);
			int v = zpos[nxt];
			if (dis[v] == INF) {
				dis[v] = find(du + 1, nxt);
				if (dis[v] != INF) {
					pq.push(ii(dis[v], v));
				}
			}
		}
	}
}

void reset(bool flag) {
	for (int i = 0; i < z.size(); ++i) zpos[z[i]] = (flag ? -1 : i);
}

void query() {
	z.clear();
	for (int mask = 0; mask < (1 << k); ++mask) {
		int val = 0;
		for (int i = 0; i < k; ++i) if (mask >> i & 1) val ^= t[i];
		z.push_back(val);
	}
	sort(z.begin(), z.end());
	z.erase(unique(z.begin(), z.end()), z.end());

	reset(0);

	int curxor = (f[n - 1] ^ offset[(n - 1) / MAGIC]);
	if (zpos[curxor] == -1) {
		puts("NIE"); reset(1); return; 
	}

	dijkstra();
	if (dis[zpos[curxor]] == INF) puts("NIE");
	else puts("TAK");

	reset(1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> q;
	for (int i = 0; i < n; ++i) cin >> a[i];

	prepare();
	memset(zpos, -1, sizeof zpos);

	while(q--) {
		int type; cin >> type;
		if (type == 1) {
			int pos, x; cin >> pos >> x; --pos;
			upd(pos, x);
		} else {
			cin >> k;
			for (int i = 0; i < k; ++i) cin >> t[i];
			query();
		}
	}
}