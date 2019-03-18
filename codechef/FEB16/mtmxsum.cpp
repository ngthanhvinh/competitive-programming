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

int n, A[N], B[N], l[N], r[N], T[N], S[N];
int resA[N], resB[N]; 
stack <int> s;

void find(int a[]) {
	s = stack<int>();
	ff(i, 1, n) {
		while(!s.empty() && a[s.top()] < a[i]) s.pop();
		if (!s.empty()) l[i] = s.top() + 1; else l[i] = 1;
		s.push(i); 
	}

	s = stack<int>();
	fod(i, n, 1) {
		while(!s.empty() && a[s.top()] <= a[i]) s.pop();
		if (!s.empty()) r[i] = s.top() - 1; else r[i] = n;
		s.push(i); 
	}
}

void upd(int x, int v) { for(; x <= n + 1; x += x & -x) T[x] = (T[x] + v) % mod; }
int get(int x) { int res = 0; for(; x > 0; x -= x & -x) res = (res + T[x]) % mod; return res; }
void upd(int l, int r, int v) { upd(l, v % mod); upd(r + 1, -v % mod); }

void solve(int a[]) {
	find(a); memset(T, 0, sizeof T); memset(S, 0, sizeof S);
	ff(i, 1, n) {
		int d = min(i - l[i] + 1, r[i] - i + 1);
		upd(1, d, a[i] % mod); upd(r[i] - l[i] + 3 - d, r[i] - l[i] + 2, -a[i] % mod);
	}
	ff(i, 1, n) {
		S[i] = get(i); 
		if (S[i] < 0) S[i] += mod;
	}
}

int main() {
	//freopen("mtmxsum.in", "r", stdin);
	//freopen("mtmxsum.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin >> n;
	ff(i, 1, n) cin >> A[i], A[i] += i; ff(i, 1, n) cin >> B[i], B[i] += i;
	solve(A); ff(i, 1, n) resA[i] = (resA[i - 1] + S[i]) % mod;
	//ff(i, 1, n) cout << i << ' ' << resA[i] << "\n";
	solve(B); ff(i, 1, n) resB[i] = (resB[i - 1] + S[i]) % mod;
	//ff(i, 1, n) cout << i << ' ' << resB[i] << "\n";
	ff(i, 1, n) cout << ((1LL * resA[i] * resB[i]) % mod + mod) % mod << " "; cout << "\n";
}