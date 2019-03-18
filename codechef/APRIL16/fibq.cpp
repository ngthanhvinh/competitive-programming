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

const int INF = 1e9, N = 100010, mod = 1e9 + 7;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int pw(int a, int n) {
	int res = 1;
	for (int i = 0; (1LL << i) <= n; i++) {
		if (n & (1LL << i)) res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return res;
}

int frac(int a, int b) { return (1LL * a * pw(b, mod-2)) % mod; }

ii operator * (ii a, ii b) {
	ii res; 
	res.fi = ((1LL * a.fi * b.fi) % mod + (5LL * a.se * b.se) % mod) % mod;
	res.se = ((1LL * a.fi * b.se) % mod + (1LL * a.se * b.fi) % mod) % mod;
	return res;
}

ii pw(ii a, int n) {
	ii res = ii(1, 0);
	for (int i = 0; (1LL << i) <= n; ++i) {
		if (n & (1LL << i)) res = res * a;
		a = a * a;
	}
	return res;
}

ii calc(int n) { ii a = ii(frac(1, 2), frac(1, 2)); return pw(a, n); }

int n, m, A[N<<2], B[N<<2], a[N];
#define mid ((l + r)>>1)
#define left id<<1
#define right (id<<1)|1

void upd(int id, int l, int r, int x, int val) {
	if (x < l || x > r || l > r) return;
	if (l == r) {
		ii x = calc(val); 
		A[id] = x.fi + 1, B[id] = x.se;
		return; 
	}
	upd(left, l, mid, x, val); upd(right, mid+1, r, x, val);
	A[id] = ((1LL * A[left] * A[right]) % mod + (5LL * B[left] * B[right]) % mod) % mod;
	B[id] = ((1LL * A[left] * B[right]) % mod + (1LL * A[right] * B[left])) % mod;
}

ii get(int id, int l, int r, int L, int R) {
	if (R < l || L > r || l > r) return ii(1, 0);
	if (L <= l && r <= R) return ii(A[id], B[id]);
	ii Left = get(left, l, mid, L, R), Right = get(right, mid+1, r, L, R);
	int x = ((1LL * Left.fi * Right.fi) % mod + (5LL * Left.se * Right.se) % mod) % mod;
	int y = ((1LL * Left.fi * Right.se) % mod + (1LL * Right.fi * Left.se) % mod) % mod;
	//cout << "get " << id << ' ' << l << ' ' << r << ' ' << L << ' ' << R << ' ' << x << ' ' << y << endl;
	return ii(x, y);
}

void buildTree(int id, int l, int r) {
	if (l > r) return;
	if (l == r) { ii x = calc(a[l]); A[id] = x.fi + 1, B[id] = x.se; return; }
	buildTree(left, l, mid); buildTree(right, mid+1, r);
	A[id] = ((1LL * A[left] * A[right]) % mod + (5LL * B[left] * B[right]) % mod) % mod;
	B[id] = ((1LL * A[left] * B[right]) % mod + (1LL * A[right] * B[left])) % mod;
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin >> n >> m; ff(i, 1, n) { cin >> a[i]; ii x = calc(a[i]); }
	buildTree(1, 1, n);

	while(m--) {
		char type; cin >> type;
		if (type == 'C') { int x, val; cin >> x >> val; upd(1, 1, n, x, val); }
		else { int l, r; cin >> l >> r; ii res = get(1, 1, n, l, r); printf("%d\n", ((int)(2LL * res.se) % mod) ); }
	}
	
}