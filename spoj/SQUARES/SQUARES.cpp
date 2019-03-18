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

const int INF = 1e9, N = 1000010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, Div[N];

void sieve() {
	Div[0] = Div[1] = 1;
	fo(i, 2, N) {
		if (!Div[i]) for (int j = i; j < N; j += i) Div[j] = i;
	}
}

int pw(int a, int b) {
	int res = 1;
	for (int i = 0; (1LL << i) <= b; ++i) {
		if (b & (1LL << i)) res = res * a;
		a = a * a;
	}
	return res;
}

int phi(int m) {
	int ans = 1;
	while(m != 1) {
		int x = Div[m], cnt = 0;
		while(m % x == 0) { cnt++; m /= x; }
		ans = ans * pw(x, cnt - 1) * (x - 1);
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	sieve();
	cin >> n; ll ans = 0;
	ff(i, 1, n) {
		if (n % i) continue;
		int m = (n / i) + 1; //cout << m << ' ' << phi(m) << "\n";
		if (m != 2) ans += phi(m) / 2;
		else ans += 1;
	}
	printf("%lld\n", ans);
}