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

const int INF = 1e9;
const ll INFL = 1e18, N = 1e16;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

map <vi, ll> f;
map <vi, bool> tooBig;
vi b;
ll ans; 
ll F(vi a);
int cnt, pr[100000010];
const int sz = 14; // from 0 -> 13 numbers
const int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 39, 41};
vector <vi> res;

ll backt(int pos, const vi& a, vi b) {
	if (pos == (int)a.size()) {
		bool check = 0;
		fo(i, 0, b.size()) if (a[i] != b[i]) { check = 1; break; }
		if (check) {
			if (tooBig.count(b)) { tooBig[a] = 1; return 0; }
			else return F(b); 
		}
		else return 0LL;
	}
	ll res = 0LL;
	for (int x = 0; x <= a[pos]; x++) {
		b.pb(x); res += backt(pos+1, a, b);
		b.pop_back();
	}
	if (res > N) { tooBig[a] = 1; return 0; }
	if (tooBig.count(a)) return 0;
	return res;
}

ll F(vi a) {
	sort(a.begin(), a.end(), greater <int> ());
	if (f.count(a)) return f[a];
	return f[a] = backt(0, a, vi());
}

void sieve() {
	pr[0] = pr[1] = 1;
	for (int i = 2; i <= 100000000; ++i) 
		if (!pr[i]) for (int j = i+i; j <= 100000000; j+=i) pr[j] = 1;
}

ll check(vi a) {
	//sort(a.begin(), a.end(), greater<int>());
	fo(i, 0, a.size()) cout << a[i] << ' '; cout << endl;
	ll res = F(a), n = res, cur = 2;
	if (tooBig.count(a)) return 0;
	vi ofN;
	cout << n << endl;
	while(n != 1) {
		//cout << n << endl;
		int cnt = 0;
		for (ll i = cur; i * i <= n; i++) {
			if (!pr[i] && n % i == 0) {
				while(n % i == 0) { n /= i, cnt++; }
				cur = i+1;
				break;
			}
		}
		//cout << "cnt " << cnt << endl;
		if (!cnt) { ofN.pb(1); break; }
		else ofN.pb(cnt);
	}
	while(ofN.size() < sz) ofN.pb(0);
	sort(ofN.begin(), ofN.end(), greater<int>());
	if (ofN == a) return res;
	else return 0LL;
}

void Find(int pos, vi a, ll prod) { // a has a.size() = 14
	if (pos == sz) { cnt++; res.pb(a); return; }
	int x = 0;
	while(x <= a[pos-1] && prod <= N) {
		Find(pos+1, a, prod);
		if (prod > N / prime[pos]) break;
		a[pos]++; x++; prod *= prime[pos];
	}
}

void solve() {
	int Max = 53;
	ll cur = 1LL; vi a; a.assign(14, 0);
	Find(0, a, 1);
	for (int i = 1; i <= Max; i++) {
		cur *= 2; a[0]++;
		Find(0, a, cur);
	} 
}

int main() {
	freopen("548.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	fo(i, 0, 17563) {
		vi a = vi(14, 0); fo(j, 0, 14) cin >> a[j];
		res.pb(a);
	}
	sieve();
	vi a; a.assign(14, 0); f[a] = 1LL;
	
	fo(i, 0, res.size()) {
		//fo(j, 0, 14) cout << res[i][j] << ' '; cout << endl;
		cout << i << endl; ans += check(res[i]);
	}
	
	//cout << check(res[746]) << endl;
	cout << ans << endl;
}