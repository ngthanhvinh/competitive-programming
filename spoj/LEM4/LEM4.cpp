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

const int INF = 1e9, N = 10010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m, T[5 * N], L[5 * N], R[5 * N];
// white 0 & black 1
#define mid ((l + r) >> 1)
#define left id<<1
#define right (id<<1)|1

struct II { 
	int T; int L; int R; 
	//II(int L, int R, int T) { II res; res.L = L; res.R = R; res.T = T; return res; }
};

void upd(int id, int l, int r, int u, int v, int x) {
	if (v < l || u > r || l > r) return;
	if (u <= l && r <= v && l == r) { T[id] = L[id] = R[id] = (x ? 0 : 1); return; }
	upd(left, l, mid, u, v, x); upd(right, mid + 1, r, u, v, x);
	L[id] = (T[left] == mid - l + 1) ? T[left] + L[right] : L[left];
	R[id] = (T[right] == r - mid) ? T[right] + R[left] : R[right];
	T[id] = max(R[left] + L[right], max(L[left], R[right]));
}

II get(int id, int l, int r, int u, int v) {
	if (v < l || u > r || l > r) { II res; res.L = res.R = res.T = 0; return res; }
	if (u <= l && r <= v && l == r) { II res; res.L = L[id], res.R = R[id], res.T = T[id]; return res; }
	II res, Left = get(left, l, mid, u, v), Right = get(right, mid + 1, r, u, v); 
	res.L = (Left.T == mid - l + 1) ? Left.T + Right.L : Left.L;
	res.R = (Right.T == r - mid) ? Right.T + Left.R : Right.R;
	res.T = max(Left.R + Right.L, max(Left.L, Right.R));
	cout << l << ' ' << r << ' ' << res.T << ' ' << res.L << ' ' << res.R << "\n";
	return res;
}

void buildTree(int id, int l, int r) {
	if (l > r) return;
	if (l == r) { T[id] = L[id] = R[id] = 1; return; }
	buildTree(left, l, mid); buildTree(right, mid + 1, r);
	T[id] = L[id] = R[id] = T[left] + T[right];
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;  
	buildTree(1, 1, n);
	while(m--) {
		int type; cin >> type;
		if(type != 3) { int u, v; cin >> u >> v; upd(1, 1, n, u, v, type - 1); }
		else printf("%d\n", get(1, 1, n, 1, n).T);
	}
}