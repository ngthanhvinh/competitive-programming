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

int n, k; 
const char inpFile[10][20] = {"01.in", "02.in", "03.in", "04.in", "05.in", "06.in", "07.in", "08.in", "09.in", "10.in"};

void gen() {
	n = rand() % 1000 + 1;
	k = rand() % 50 + 1;
	cout << n << ' ' << k << endl;
	ff(i, 1, k) {
		cout << rand() % 10000 + 1 << ' ';
	}
	cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	fo(i, 0, 10) {
		freopen(inpFile[i], "w", stdout);
		gen();
	}
}