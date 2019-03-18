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

const int INF = 1e9, N = 33;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, a[N];
map <ll, int> f;
ll S;
const char inpFile[10][20] = {"01.in", "02.in", "03.in", "04.in", "05.in", "06.in", "07.in", "08.in", "09.in", "10.in"};
const char outFile[10][20] = {"01.out", "02.out", "03.out", "04.out", "05.out", "06.out", "07.out", "08.out", "09.out", "10.out"};

int main() {
	ios_base::sync_with_stdio(false);
	fo(i, 0, 10) {
		freopen(inpFile[i], "r", stdin);
		freopen(outFile[i], "w", stdout);
		cin >> n; f.clear(); ff(i, 1, n) { cin >> a[i]; S += a[i]; }
		fo(mask, 0, 1<<n) {
			ll res1 = 0, res2 = 0;
			fo(i, 0, n) {
				if (mask & (1 << i)) res1 += a[i + 1];
				else res2 += a[i + 1];
			}
			//cout << mask << ' ' << res1 << ' ' << res2 << "\n";
			f[abs(res1 - res2)]++;
			//cout << f[abs(res1 - res2)] << "\n";
		}
		//cout << "S: " << S << "\n";
		map <ll, int>::iterator it = f.begin();
		it->se /= 2;
		cout << it->fi << ' ' << it->se << endl;
	}
}