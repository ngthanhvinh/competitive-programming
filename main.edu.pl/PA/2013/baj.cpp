#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ff(i, a, b) for(int i = a; i <= b; i++)
#define fo(i, a, b) for(int i = a; i < b; i++)
#define fod(i, a, b) for(int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

const int INF = 1e9, N = 500010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, dist[N];
int d[N], M[N][20];
int lg2[N];
vector <vii> G;

void dijkstra() {
	priority_queue < ii, vector <ii>, greater <ii> > q;
	q.push(ii(0, 0)); ff(i, 1, n) d[i] = INF;
	while(!q.empty()) {
		ii T = q.top(); q.pop(); int u = T.se, du = T.fi;
		if (du != d[u]) continue;
		fo(i, 0, G[u].size()) {
			int v = G[u][i].fi, uv = G[u][i].se;
			if (d[v] > du + uv) {
				d[v] = du + uv;
				q.push(ii(d[v], v));
			}
		}
	}
}

void prep() {
	ff(i, 1, n) M[i][0] = d[i];
	ff(i, 1, 19) for (int j = 1; j + (1<<i) - 1 <= n; j++)
		M[j][i] = max(M[j][i-1], M[j + (1<<i-1)][i-1]);

	int cur = 1, lg = 0;
	ff(i, 1, n) { if (i > cur) cur *= 2, lg++; lg2[i] = lg; }
}

int get(int l, int r) {
	int k = lg2[r - l + 1];
	return max(M[l][k], M[r - (1<<k) + 1][k]);
}

bool f(int x) {
	int total = 0; ff(i, 1, n) total += dist[i]; if (total <= x) return 1;
	ff (i, 1, n) if (d[i] > x) return 0;

	int l = 1, r = 1, dl = 0, dr = 0;
	while(dl <= x) l = ((l == 1) ? n : l - 1), dl += dist[l]; dl -= dist[l]; l = ((l == n) ? 1 : l + 1);
	while(dr <= x) dr += dist[r], r = ((r == n) ? 1 : r + 1); r = ((r == 1) ? n : r - 1); dr -= dist[r];
	if (l > r + 1 && get(r+1, l-1) + d[1] > x) return 0;
    //cout << l << ' ' << r << endl;
	ff (i, 2, n) {
		dl += dist[i-1], dr -= dist[i-1];
		while(dl > x) dl -= dist[l], l = ((l == n) ? 1 : l + 1);
		while(dr <= x) dr += dist[r], r = ((r == n) ? 1 : r + 1); r = ((r == 1) ? n : r - 1); dr -= dist[r];

		int dLeft = 0, dRight = 0;
		if (i >= l) dLeft = i - l; else dLeft = i + n - l;
		if (r >= i) dRight = r - i; else dRight = r + n - i;
		if (dLeft + dRight >= n-1) continue;

		int nl = ((l == 1) ? n : l - 1), nr = ((r == n) ? 1 : r + 1), res = 0;
		//cout << nl << ' ' << nr << endl;
		// Max from nl to nr
		if (nl >= nr) res = get(nr, nl);
		else res = max(get(1, nl), get(nr, n));

		if (res + d[i] > x) return 0;
	}

	return 1;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin >> n; G.assign(n + 1, vii()); n--;
	ff (i, 1, n) {
		int j = ((i == n) ? 1 : i + 1);
		int x; cin >> x; dist[i] = x;
		G[i].pb(ii(j, x)); G[j].pb(ii(i, x));
	}
	ff (i, 1, n) { int x; cin >> x; G[0].pb(ii(i, x)); G[i].pb(ii(0, x)); }
	dijkstra();
	prep();
    /*
	int l = 0, r = INF + 10;
	while(l != r) {
		int mid = ((l + r) >> 1);
		if (f(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l << endl;
	*/
	cout << f(95) << endl;
}
