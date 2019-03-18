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

const int INF = 1e9, N = 110, mod = (int)1e9 + 7;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m, cnt, ans;
int Div[N], ft[100010];
vector <int> pr, v;
vector < vector <vi> > f;
vector <int> T, G;

int pw(int a, int b) {
	int res = 1;
	for (int i = 0; (1LL << i) <= b; i++) {
		if (b & (1LL << i)) res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return res;
}

int C(int n, int k) {
	if (n < k || n < 0 || k < 0) return 0;
	int res = ft[n]; res = (1LL * res * pw(ft[k], mod - 2)) % mod; res = (1LL * res * pw(ft[n-k], mod - 2)) % mod;
	return res;
}

void sieve() {
	Div[0] = Div[1] = 1;
	ff(i, 2, m) {
		if (!Div[i]) { pr.pb(i); for (int j = i; j <= m; j += i) Div[j] = i; }
	}
}

void solve() {
	cin >> n >> m; pr.clear(); v.clear(); cnt = 0; memset(Div, 0, sizeof Div);
	sieve(); for (int i = 0; i < pr.size(); i++) if (pr[i] <= m/2) ++cnt;
	f.assign(cnt + 1, vector<vi>(m+1, vi(1 << cnt, 0))); 
	ff(num, 2, m) {
		if (Div[num] == num && num > m/2) continue;
		v.pb(num);
	}
	//fo(i, 0, v.size()) cout << v[i] << ' '; cout << endl;
	ff(pos, 1, v.size()) {
		fo(mask, 0, 1<<cnt) f[1][pos][mask] = f[1][pos-1][mask];
		int num = v[pos-1], state = 0; ff(i, 0, cnt-1) if (num % pr[i] == 0) state |= (1 << i);
		f[1][pos][state] = (f[1][pos][state] + 1) % mod;
	}

	ff(i, 2, cnt) ff(pos, 1, v.size()) {
		int num = v[pos-1], state = 0;
		fo(j, 0, cnt) if (num % pr[j] == 0) state |= (1 << j);
		fo(mask, 1, (1<<cnt)) {
			f[i][pos][mask] = f[i][pos-1][mask];
			if ((mask & state) != state) continue;
			f[i][pos][mask] = (f[i][pos][mask] + f[i-1][pos-1][mask ^ state]) % mod;
		}
	}

	T.assign(cnt + 1, 0); G.assign(m + 1, 0);
	ff(i, 0, cnt) { fo(mask, 1, (1<<cnt)) T[i] = (T[i] + f[i][v.size()][mask]) % mod; }
	T[0] = G[0] = 1; 
	ff(i, 1, m) {
		ff(j, 0, min(i, cnt)) G[i] = (G[i] + (1LL * T[j] * C(pr.size()-cnt, i-j))) % mod;
		//cout << pr.size()-cnt << endl;
		//cout << i << ' ' << G[i] << endl;
	}
	ans = 0;
	ff(i, 0, min(m,n)) {
		int res = (1LL * ft[n] * G[i]) % mod;
		res = (1LL * res * pw(ft[n-i], mod - 2)) % mod;
		ans = (ans + res) % mod;  
	}	
	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	ft[0] = 1; ff(i, 1, 100000) ft[i] = (1LL * ft[i-1] * i) % mod;
	int t; cin >> t;
	while(t--) solve();
}