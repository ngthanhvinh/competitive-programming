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

const int INF = 1e9, N = 31;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

map <ii, int> f;
ll ans;
int n, x[N], y[N], u, v;

void FirstBackt(int pos, int X, int Y) {
	if (pos == n / 2) {
		f[ii(X, Y)]++; return;
	}
	FirstBackt(pos + 1, X + x[pos + 1], Y + y[pos + 1]);
	FirstBackt(pos + 1, X, Y);
}

void SecondBackt(int pos, int X, int Y) {
	if (pos == n) {
		if (f.count(ii(u - X, v - Y))) ans += f[ii(u - X, v - Y)]; return;
	}
	SecondBackt(pos + 1, X + x[pos + 1], Y + y[pos + 1]);
	SecondBackt(pos + 1, X, Y);
}

int main() {
	//freopen("input.txt", "r", stdin);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; ff(i, 1, n) cin >> x[i] >> y[i];
	cin >> u >> v;
	FirstBackt(0, 0, 0);
	SecondBackt(n / 2, 0, 0);
	printf("%lld\n", ans);
}