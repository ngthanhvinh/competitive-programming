#include <bits/stdc++.h>
using namespace std;
const int N = 300010;
const long long INF = 1e18;
typedef pair<int,int> ii;

long long t[N];
int n, m, q;
void upd(int x, int val) { for (; x <= m; x += x & -x) t[x] += val; }
long long get(int x) { long long res = 0; for (; x > 0; x -= x & -x) res += t[x], res = min(res, INF); return res; }

void upd(int l, int r, int val) { upd(l, val); upd(r+1, -val); }
void query(int l, int r, int val) {
	if (l <= r) return upd(l, r, val);
	else upd(l, m, val), upd(1, r, val);
}
long long getPoint(int x) { return get(x); }
#undef mid

int u[N], v[N], k[N], a[N], lim[N];
int lo[N], hi[N];
vector <int> met[N];
vector <ii> curMid;

void reset() { 
	curMid.clear(); 
	for (int i = 1; i <= n; i++) if (!((lo[i] == hi[i] && lo[i] != q) || lo[i] > hi[i])) 
		curMid.push_back(ii((lo[i] + hi[i]) >> 1, i)); 
	sort(curMid.begin(), curMid.end());
	memset(t, 0, sizeof t);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d", &a[i]), met[a[i]].push_back(i);
	for (int i = 1; i <= n; i++) scanf("%d", &lim[i]);
	
	cin >> q;
	for (int i = 1; i <= n; i++) lo[i] = 0, hi[i] = q;
	for (int i = 1; i <= q; i++) scanf("%d%d%d", &u[i], &v[i], &k[i]);

	for (int times = 0; times < 19; times++) {
		reset();
		int ptr = 1;
		for (int i = 0; i < curMid.size(); i++) {
			int mid = curMid[i].first, p = curMid[i].second;
			while(ptr <= mid && ptr <= q) query(u[ptr], v[ptr], k[ptr]), ptr++;

			long long sum = 0;
			for (int j = 0; j < met[p].size(); j++) sum += getPoint(met[p][j]), sum = min(sum, INF); 
			if (sum >= lim[p]) hi[p] = mid;
			else lo[p] = mid + 1;
		}
	}	

	for (int i = 1; i <= n; i++) 
		if (lo[i] == q+1) printf("NIE\n");
		else printf("%d\n", lo[i]); 
}