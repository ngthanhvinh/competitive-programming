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

const int INF = 1e9, N = 100010, M = 1000001;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, a[N], d[M], check[M];
vector <int> Div[M];
int mn[M], p[M], ans[N], pos[N];

void sieve() {
	d[0] = d[1] = 1;
	fo(i, 2, M) if (!d[i]) for (int j = i; j < M; j += i) d[j] = i;
}

void calc(int x) {
	for (int i = 1; 1ll * i * i <= x; i++) if (x % i == 0) {
		if (i != x/i) Div[x].pb(i), Div[x].pb(x/i);
		else Div[x].pb(i);
	}
	//fo(i, 0, Div[x].size()) cout << Div[x][i] << ' '; cout << endl;
}

int process(int x) {
	int cnt = 0;
	while(x != 1) {
		int cur = d[x];
		while(x % cur == 0) x /= cur, cnt++;
	}
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(false);
	sieve();
	cin >> n;
	ff(i, 1, n) {
		cin >> a[i]; 
		if (!check[a[i]]) calc(a[i]), check[a[i]] = 1;
		ans[i] = pos[i] = INF;
	}
	ff(i, 1, M-1) mn[i] = p[i] = INF;
	ff(i, 1, n) {
		int x = a[i];
		fo(j, 0, Div[x].size()) {
			int y = Div[x][j];
			int r = process(x / y);
			if (ans[i] > r + mn[y]) ans[i] = r + mn[y], pos[i] = p[y]; 
			else if (ans[i] == r + mn[y]) pos[i] = min(pos[i], p[y]);
			if (mn[y] > r) mn[y] = r, p[y] = i;
		}
	}
	//ff(i, 1, n) cout << pos[i] << ' '; cout << endl;

	ff(i, 1, M-1) mn[i] = p[i] = INF;
	fod(i, n, 1) {
		int x = a[i];
		fo(j, 0, Div[x].size()) {
			int y = Div[x][j];
			int r = process(x / y);
			if (ans[i] > r + mn[y]) ans[i] = r + mn[y], pos[i] = p[y];
			else if (ans[i] == r + mn[y]) pos[i] = min(pos[i], p[y]);
			if (mn[y] >= r) mn[y] = r, p[y] = i;
		}
	}
	
	ff(i, 1, n) cout << pos[i] << endl;
}