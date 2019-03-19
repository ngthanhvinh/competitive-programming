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

const int INF = 0x3f3f3f3f, N = 100010;
const ll INFL = 0x3f3f3f3f3f3f3f3fLL;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m, sz, k, f[N], cursum, x; string s;
bool check;
vector <ii> a;

void process() {
	ff(i, 1, sz) {
		cursum += (s[i - 1] == 'T') ? 2 : 1;
		// /cout << cursum << "\n";
		a[cursum].fi = 1; a[cursum].se = i;
	} 
	fo(i, 0, sz) if (s[i] == 'W') check = 1;
	if (!check) return;
	cursum = 0;
	ff(i, 1, sz) if (s[i - 1] == 'W') { x = i; break; }
	//cout << x << "\n";
	ff(i, x, sz) {
		if (s[i - 1] == 'T') { a[cursum + 2].fi = x; a[cursum + 2].se = i; a[cursum + 1].fi = x + 1; a[cursum + 1].se = i; }
		else a[cursum + 1].fi = x, a[cursum + 1].se = i;
		cursum += (s[i - 1] == 'T') ? 2 : 1;
	}
	cursum = 0;
	fod(i, sz, 1) if (s[i - 1] == 'W') { x = i; break; }
	//cout << x << "\n";
	fod(i, x, 1) {
		if (s[i - 1] == 'T') { a[cursum + 2].fi = i; a[cursum + 2].se = x; a[cursum + 1].fi = i; a[cursum + 1].se = x - 1; }
		else a[cursum + 1].fi = i, a[cursum + 1].se = x;
		cursum += (s[i - 1] == 'T') ? 2 : 1;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n >> m >> s; a.assign(2 * n + 1, ii(INF, INF)); sz = s.size();
	process();
	while(m--) {
		cin >> k;
		if (k > 2 * n) printf("NIE\n");
		else if (a[k].fi == INF && a[k].se == INF) printf("NIE\n");
		else printf("%d %d\n", a[k].fi, a[k].se);
	}
}