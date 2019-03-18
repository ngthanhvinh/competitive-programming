#include <bits/stdc++.h>
using namespace std;
typedef pair <int, int> ii;
typedef vector <int> vi;

#define ll long long
#define ff(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define fod(i, a, b) for (int i = (int)(a); i >= (int)(b); i--)
#define pb push_back
#define fi first
#define se second
const int N = 100010, mod = (int)1e9 + 7, INF = 1e9;

int n;

int main() {
	freopen("input.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	n = 1500;
	cout << n << endl;
	ff(i, 1, n) cout << rand() % 1000000 << ' ' << rand() % 1000000 << endl;
}