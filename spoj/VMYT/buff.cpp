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

const char inpFile[10][20] = {"01.in", "02.in", "03.in", "04.in", "05.in", "06.in", "07.in", "08.in", "09.in", "10.in"};
const char outFile[10][20] = {"01.out", "02.out", "03.out", "04.out", "05.out", "06.out", "07.out", "08.out", "09.out", "10.out"};
int n, k, a[N];
void solve() {
	cin >> n >> k;
	ff(i, 1, k) cin >> a[i];
	ff(i, k + 1, n) {
		a[i] = 1;
		ff(j, i - k, i - 1) a[i] = (1LL * a[i] * a[j]) % mod;
	}
	cout << a[n] << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	fo(i, 0, 10) {
		freopen(inpFile[i], "r", stdin);
		freopen(outFile[i], "w", stdout);
		solve();
	}
}