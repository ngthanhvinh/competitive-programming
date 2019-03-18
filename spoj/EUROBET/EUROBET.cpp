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
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

double f[101][(N<<1) + 10], ans;
int n, prob, scoreA, scoreB;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	f[0][N] = 1.0;
	ff(i, 1, n) {
		cin >> prob >> scoreA >> scoreB;
		if (prob < 50) { prob = 100 - prob; swap(scoreA, scoreB); }
		ff(sub, -N + scoreA, N - scoreA) {
			int j = sub + N;
			f[i][j] += (double)prob/100.0 * f[i-1][(i & 1) ? (j - scoreA) : (j + scoreA)];
			f[i][j] += (double)(100 - prob) / 100.0 * f[i-1][j];
			//if (f[i][j] != 0.0) cout << i << ' ' << "Ronaldo - Ballotelli = " << j - N << ' ' << " f = " << f[i][j] << "\n";
		}
	}
	fo(i, N + 1, (N<<1) + 10) ans += f[n][i];
	//cout << f[n][N] << "\n";
	ans += f[n][N] / 2.0;
	cout << setprecision(6) << fixed << ans << "\n";
}