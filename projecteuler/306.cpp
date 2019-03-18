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

const int INF = 1e9, N = 1000010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int G[N];
int n;
int a[] = {1, 1, 2, 0, 3, 1, 1, 0, 3, 3, 2, 2, 4, 4, 5, 5, 2, 3, 3, 0, 1, 1, 3, 0, 2, 1, 1, 0, 4, 5, 3, 7, 4, 8};

int main() {
	ios_base::sync_with_stdio(false);
	memset(G, -1, sizeof G);
	cin >> n;
	G[0] = G[1] = 0;
	int ans = 27;
	ff(i, 36, n) {
		if (i % 34 == 2) G[i] = a[0];
		else if (i % 34 == 1) G[i] = a[33];
		else if (i % 34 == 0) G[i] = a[32];
		else G[i] = a[i % 34 - 2];
		if (G[i] > 0) ans++;
		//cout << G[i] << '\n'; 
	}
	cout << ans << endl;
}