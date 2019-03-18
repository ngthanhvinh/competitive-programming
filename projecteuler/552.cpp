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

const int INF = 1e9, N = 300001;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

vector <int> p, q, M;
bool pr[N], check[N];
int n;
long long ans;

void sieve() {
	pr[0] = pr[1] = 1;
	fo(i, 2, N) {
		if (!pr[i]) { p.pb(i); for (int j = i+i; j < N; j += i) pr[j] = 1; }
	}
}

int pw(int a, int b, int mod) {
	int res = 1;
	for (int i = 0; (1LL << i) <= b; i++) {
		if (b & (1LL << i)) res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return res;
}

int modInv(int a, int mod) { return pw(a, mod-2, mod); }

int main() {
	ios_base::sync_with_stdio(false);
	p.pb(0); sieve();
	n = p.size()-1;
	//cout << "Prime Numbers\n";
	//ff(i, 1, n) cout << p[i] << ' '; cout << endl;
	//cout << endl;
	q.assign(n + 2, 1); M.assign(n + 2, 1);
	ff(i, 2, n) {
		//cout << i << ' ' << p[i] << endl;
		for (int j = i; j <= n; j++) M[j] = (1LL * p[i-1] * M[j]) % p[j];
		int k = (1LL * ((i - q[i] + p[i]) % p[i]) * modInv(M[i], p[i])) % p[i];
		for (int j = i; j <= n; j++) {
			int add = (1LL * k * M[j]) % p[j];
			q[j] = (q[j] + add) % p[j];	
		}
		//ff(j, 1, n) cout << q[j] << ' '; cout << endl;
		for (int j = i; j <= n; j++) if (!q[j]) check[j] = 1;
	}

	ff(i, 1, n) if (check[i]) ans += p[i];
	cout << ans << endl;
}