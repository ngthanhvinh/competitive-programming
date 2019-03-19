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

const int INF = 0x3f3f3f3f, N = 10010;
const ll INFL = 0x3f3f3f3f3f3f3f3fLL;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n;
double a[N], b[N];
double F[N][N];

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n; ff(i, 1, n) cin >> a[i] >> b[i];
	if (n == 1) return cout << 1 << "\n", 0;
	ff(i, 1, n) {
		double MIN1 = INF, MIN2 = INF;
		int cnt = 0;
		ff(j, 1, n) {
			if (MIN1 > F[i - 1][j]) { MIN1 = F[i - 1][j]; cnt = j; } }
		}
		ff(j, 1, n) if (j != cnt) MIN2 = min(MIN2, F[i - 1][j]);
		ff(j, 1, n) {
			double curMin;
			if (F[i - 1][j] == MIN1) { curMin = MIN2; }
			else curMin = MIN1;
			F[i][j] = curMin * a[j] + b[j];
		}
	}
	int I = n, J = 0; double mn = INF;
	ff(j, 1, n) if (F[n][j] < mn) { mn = F[n][j]; J = j; }
	while(I--) {
		ff(j, 1, n)  
	}
}