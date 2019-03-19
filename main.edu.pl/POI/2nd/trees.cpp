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

const int INF = 0x3f3f3f3f, N = 1000010;
const ll INFL = 0x3f3f3f3f3f3f3f3fLL;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, x, a[N], par[N];
stack <int> s;
bool ok; int nearest[N], L[N], R[N];
string S[N];
vi res;

void fastPush(int v) {
	while(s.size()) {
		//cout << x << ' ' << s.top() << "\n";
		if (s.top() != x) { s.push(x); res.pb(x); return; } 
		s.pop(); res.pb(x);
		x--; 		
		n += v; 
	}
	if (!s.size()) {
		s.push(x); res.pb(x); 
	}
}

void FindPar() {
	nearest[0] = 1;
	fo(i, 1, res.size()) {
		par[i + 1] = nearest[res[i] - 1];
		nearest[res[i]] = i + 1;
	}
}

void bracketForm() {
	ff(i, 1, n) {
		if (!L[par[i]]) L[par[i]] = i;
		else if (!R[par[i]]) R[par[i]] = i;
	}
	fod(i, n, 1) {
		if (!L[i] && !R[i]) S[i] = "()";
		else {
			string str = "(" + S[L[i]] + S[R[i]] + ")";
			S[i] = str;
		}
	}
	cout << S[1] << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n; int tmp = n;
	ff(i, 1, tmp) {
		cin >> x; a[i] = x;
		if (s.size()) fastPush(1);
		else { s.push(x); res.pb(x); }
	}

	if (s.size() == 1 && s.top() == 0) ok = 1;
	
	if (!ok) return cout << "NIE\n", 0;
	
	s = stack <int> ();
	res.clear();
	fod(i, tmp, 1) {
		x = a[i];
		if (s.size()) fastPush(-1);
		else { s.push(x); res.pb(x); } 
	}
	
	reverse(res.begin(), res.end());
	
	//fo(i, 0, res.size()) cout << res[i] << " ";
	n = res.size();
	FindPar();
	ff(i, 1, n) cout << par[i] << ' '; cout << "\n"; 
	bracketForm();
}