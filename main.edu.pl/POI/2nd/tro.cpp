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

const int INF = 0x3f3f3f3f, N = 100010;
const ll INFL = 0x3f3f3f3f3f3f3f3fLL;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

set <int> a;
set <int>::iterator it, FIRST, END;
int n, A, B, C;
bool exist = 0;
bool TriangleCheck() { return(A + B > C && B + C > A && C + A > B); }
void check() { exist = max(exist, TriangleCheck()); }
int main() {
	ios_base::sync_with_stdio(false);
	while(cin >> n) {
		a.insert(n); if (a.size() < 3) continue;
		it = a.find(n); FIRST = a.begin(); END = a.end();
		if (it == a.begin()) { A = *it; B = *(it++); C = *(it++); it--; it--; check(); }
		if (it == a.end() - 1) { A = *it; B = *(it--); C = *(it--); it++; it++; check(); }
		if (it == )   
	}
}