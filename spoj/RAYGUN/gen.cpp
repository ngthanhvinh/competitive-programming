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

int main() {
	freopen("input.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0); srand(time(NULL));
	int t = 100;
	cout << t << "\n";
	while(t--) {
		int n = rand() % 1000 + 1, m = rand() % 1000 + 1;
		cout << n << ' ' << m << "\n";
	}
}