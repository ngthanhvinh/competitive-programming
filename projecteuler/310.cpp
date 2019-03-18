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

const int INF = 1e9, N = 100010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n;
int G[N];
long long f[4][N];

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n;
	G[0] = 0;
	ff(i, 1, n) {
		int j = 1; bitset <N> check;
		while(j * j <= i) check[G[i - j * j]] = 1, j++;
		int x = 0;
		while(check[x]) x++;
		G[i] = x;
	//	cout << i << ' ' << x << "\n";
	}
	f[0][0] = 1;
	ff(i, 0, 2) ff(j, 0, 100) {
		ff(k, 0, n) f[i+1][j ^ G[k]] += f[i][j];
	}
	long long ans = f[3][0];
	long long A = f[1][0] * (n + 1);
	long long B = f[1][0];
	//cout << 3 * (A - B) << endl;
	long long diff = (ans - 3 * (A - B) - B) / 6;
	cout << diff + A << endl;
}