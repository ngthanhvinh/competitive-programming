#include <bits/stdc++.h>
using namespace std;

#define ff(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define fod(i, a, b) for (int i = (int)(a); i >= (int)(b); i--)
#define ll long long
#define pb push_back
#define x first
#define y second
typedef pair <int, int> ii;
typedef vector <int> vi;
const int N = 1010, maxv = 1000010, INF = (int)1e9, mod = (int)1e9 + 7;

int n, m;
int a[N][N], b[N][N], row[maxv*2], col[maxv*2];

void reset() {
	ff(i, 1, n) ff(j, 1, m) row[b[i][j] + maxv] = col[b[i][j] + maxv] = 0;
}
void No() { reset(); cout << "NIE" << endl; }
void Yes() { cout << "TAK" << endl; }

void solve() {
	cin >> n >> m;
	ff(i, 1, n) ff(j, 1, m) cin >> a[i][j];
	ff(i, 1, n) ff(j, 1, m) cin >> b[i][j], row[b[i][j] + maxv] = i, col[b[i][j] + maxv] = j;

	ff(i, 1, n) {
		int k = row[a[i][1] + maxv]; if (!k) return No();
		ff(j, 1, m) if (row[a[i][j] + maxv] != k) return No(); 
	}
	ff(j, 1, m) {
		int k = col[a[1][j] + maxv]; if (!k) return No();
		ff(i, 1, n) if (col[a[i][j] + maxv] != k) return No();
	}
	reset();
	Yes();
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--) 
		solve();
}