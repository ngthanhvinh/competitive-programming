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
const char inpFile[10][20] = {"01.in", "02.in", "03.in", "04.in", "05.in", "06.in", "07.in", "08.in", "09.in", "10.in"};

int main() {
	ios_base::sync_with_stdio(false);
	for (int i = 1; i <= 10; i++) {
		freopen(inpFile[i - 1], "w", stdout);
		n = rand() % 10 + 1;	
		cout << n << endl;
		ff(i, 1, n) cout << rand() % 1000000000 + 1 << ' '; cout << endl;
	}
}