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

const int INF = 1e9, MAX = 10010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, v, k, N;
string s;
vector <int> x, y;
bool A[MAX], B[MAX];
vector <ii> t;

int Int(string s) { int r = 0; fo(i, 0, s.size()) r = 10 * r + s[i] - '0'; return r; }

void solve() {
	x.clear(); y.clear(); t.clear();
	cin >> n >> s;
	while(cin >> s && s != ">>") v = Int(s), x.pb(v);
	cin >> s;
	while(cin >> s && s != ">>") v = Int(s), y.pb(v);

	memset(A, 0, sizeof A); memset(B, 0, sizeof B);
	fo(i, 0, x.size()) B[x[i]] = 1, A[y[i]] = 1, t.pb(ii(y[i], x[i])); k = t.size();
	N = n - k;
	sort(t.begin(), t.end());
	double ans = 1.0 / 4.0 * N * (N-1);
	int sum = 0;
	fo(i, 0, t.size()-1) {
		sum += t[i].se;
		fo(j, i+1, t.size()) if (t[j].se < t[i].se) ans += 1.0;
	}
	fo(i, 0, t.size()) {
		int g = 0, m = 0;
		ff(j, 1, t[i].se-1) if (!B[j]) g++;
		ff(j, t[i].fi+1, n) if (!A[j]) m++;
		ans += g * (double)m / N;
		g = m = 0;
		ff(j, t[i].se+1, n) if (!B[j]) g++;
		ff(j, 1, t[i].fi-1) if (!A[j]) m++;
		ans += g * (double)m / N;
	}
	cout << setprecision(6) << fixed << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	while(cin >> s && s != "[END]") 
		solve();
}