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

const int INF = 1e9, N = 1000100, mod = 1e9;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, h, Div[N], a[N], cnt[N];

void sieve() {
	Div[0] = Div[1] = 1;
	fo(i, 2, N) {
		if(!Div[i]) { for (int j = i; j < N; j += i) Div[j] = i; }
	}
}

int pw(int a, int b) {
	int res = 1;
	for (int i = 0; (1LL << i) <= b; ++i) {
		if (b & (1LL << i)) res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
	}
	return res;
}

void solve1() {
	int Count = 1; a[n + 1] = INF;
	fod(i, n, 1) {
		if (a[i] > a[i + 1]) break;
		Count++;
	}
	printf("%d\n", Count);
}

void analize(int x, int v) {
	while(x != 1) { cnt[Div[x]] += v; x /= Div[x]; }	
}

void solve2() {
	++n; int ans = 1;
	ff(i, n + 2, 2 * n) analize(i, 1);
	ff(i, 1, n) analize(i, -1);
	fo(i, 2, N) {
		if (!cnt[i]) continue;
		ans = (1LL * ans * pw(i, cnt[i])) % mod;
	}
	printf("%d\n", ans);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	sieve();
	cin >> n >> h;
	ff(i, 1, n) cin >> a[i];
	solve1();
	solve2();
}