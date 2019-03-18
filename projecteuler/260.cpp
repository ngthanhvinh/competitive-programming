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

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n;
long long ans;
const int OFFSET = 1001, N = 2010;
bool x[N][N], y[N][N], z[N][N], xy[N][N], yz[N][N], zx[N][N], xyz[N][N];

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n;
	x[OFFSET][OFFSET] = y[OFFSET][OFFSET] = z[OFFSET][OFFSET] = 
	xy[OFFSET][OFFSET] = yz[OFFSET][OFFSET] = zx[OFFSET][OFFSET] = xyz[OFFSET][OFFSET] = 1;

	ff(a, 0, n) ff(b, 0, n) ff(c, 0, n) {
		bool check = 0;
		if (xyz[b-a+OFFSET][c-b+OFFSET]) check = 1;
		if (x[b+OFFSET][c+OFFSET]) check = 1;
		if (y[a+OFFSET][c+OFFSET]) check = 1;
		if (z[a+OFFSET][b+OFFSET]) check = 1;
		if (xy[b-a+OFFSET][c+OFFSET]) check = 1;
		if (yz[a+OFFSET][b-c+OFFSET]) check = 1;
		if (zx[b+OFFSET][c-a+OFFSET]) check = 1;

		if (check) continue;
		xyz[b-a+OFFSET][c-b+OFFSET] = 1;
		x[b+OFFSET][c+OFFSET] = 1;
		y[a+OFFSET][c+OFFSET] = 1;
		z[a+OFFSET][b+OFFSET] = 1;
		xy[b-a+OFFSET][c+OFFSET] = 1;
		yz[a+OFFSET][b-c+OFFSET] = 1;
		zx[b+OFFSET][c-a+OFFSET] = 1;
		if (a <= b && b <= c) { ans += (a + b + c); }
	}
	cout << ans << endl;
}