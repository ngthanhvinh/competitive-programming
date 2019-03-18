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

const int INF = 1e9, N = 30010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, a[N], L[N], R[N];
stack <int> s;

void solve() {
	s = stack<int>();
	ff(i, 1, n) {
		while(!s.empty() && a[s.top()] >= a[i]) s.pop();
		if (!s.empty()) L[i] = s.top() + 1; else L[i] = 1;
		s.push(i);
	}
	s = stack<int>();
	fod(i, n, 1) {
		while(!s.empty() && a[s.top()] >= a[i]) s.pop();
		if (!s.empty()) R[i] = s.top() - 1; else R[i] = n;
		s.push(i);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) {
		cin >> n; ff(i, 1, n) cin >> a[i];
		solve();
		int res = 0, u, v;
		ff(i, 1, n) {
			if (res < a[i] * (R[i] - L[i] + 1)) {
				res = a[i] * (R[i] - L[i] + 1); u = L[i]; v = R[i];
			}
			else if (res == a[i] * (R[i] - L[i] + 1) && u > L[i]) { u = L[i]; v = R[i]; } 
		}
		printf("%d %d %d\n", res, u, v);
	}
}