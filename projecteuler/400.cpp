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

const int INF = 1e9, N = 10010;
const ll mod = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int G[N];
long long f[N][N];
int n, mx;

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n; G[1] = 0; G[2] = 1; 
	for (int i = 3; i <= n; i++) G[i] = ((G[i-1] + 1) ^ (G[i-2] + 1)) + 1;
	for (int i = 3; i <= n; i++) G[i]++;
	f[2][0] = 1LL;
	ff(i, 3, n) fo(j, 0, N) {
		f[i][j] = (f[i][j] + (j-1 == G[i-1])) % mod;
		f[i][j] = (f[i][j] + (j-1 == G[i-2])) % mod;
		f[i][j] = (f[i][j] + f[i-1][(j ^ (G[i-2] + 1)) - 1]) % mod;
		f[i][j] = (f[i][j] + f[i-2][(j ^ (G[i-1] + 1)) - 1]) % mod;
	}
	printf("%018lld\n", f[n][0]);
}