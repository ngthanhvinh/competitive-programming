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
const int N = 1000010, mod = (int)1e9 + 7, INF = 1e9;

int n, k, b, c;
char a[N];
vector <int> v;
vector <vi> ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	ff(i, 1, n) cin >> a[i];

	ff(i, 1, n) {
		v.pb(i); b += (a[i]=='b'); c += (a[i]=='c');
		if (v.size() >= k+2) b -= (a[v[v.size()-k-2]] == 'b'), c -= (a[v[v.size()-k-2]] == 'c');
		//cout << b << ' ' << c << endl;
		while(v.size() >= k+1 && b == k && c == 1) {
			vi step;
			ff(i, 1, k+1) step.pb(v.back()), v.pop_back();
			ans.pb(step);
			b = c = 0;
			fod(i, v.size()-1, max((int)v.size()-k-1, 0)) b += (a[v[i]] == 'b'), c += (a[v[i]] == 'c'); 
		}
	}

	fod(i, ans.size()-1, 0) {
		fod(j, ans[i].size()-1, 0) cout << ans[i][j] << ' '; 
		cout << endl;
	}
}