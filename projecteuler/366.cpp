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
typedef vector <long long> vi;
typedef vector <ii> vii;

long long n;
long long f[N];

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n; int m = 50;
	f[1] = 1; f[2] = 2; ff(i, 3, 50) f[i] = f[i-1] + f[i-2];
	for (long long i = 1; i <= n; i++) {
		long long tmp = i;
		vi Fib;
		while(tmp != 0) {
			int pos = upper_bound(f + 1, f + m + 1, tmp) - f - 1;
			tmp -= f[pos]; Fib.pb(pos);
		}
		fo(j, 0, Fib.size()) cout << f[Fib[j]] << ' '; cout << endl;
		//if (Fib.size() == 1) { cout << "skip because it is a fib number\n"; continue; }
		reverse(Fib.begin(), Fib.end());
		long long cur = 0, sum = 0; int x = 0;
		fo(j, 0, Fib.size()) {
			if (f[Fib[j]] > 2 * cur) x = Fib[j], sum = cur;
			cur += f[Fib[j]]; //, cout << cur << endl;
		}
		cout << "current " << i << ' ' << sum << endl;
		//cout << sum << ", ";
	}
}