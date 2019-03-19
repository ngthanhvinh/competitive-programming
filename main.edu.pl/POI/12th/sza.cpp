#include <iostream>
#include <vector>
using namespace std;

const int N = 500010;

int n, Z[N];
string s;
vector <int> pos[N];
int le[N], ri[N];
int mx = 0;
int ans = 1e9;

void del(int x) {
	int l = le[x], r = ri[x];
	mx = max(mx, r - l);
	ri[l] = r;
	le[r] = l;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> s; n = s.size(); s = ' ' + s;
	Z[1] = n;
	int l = 0, r = 0;
	for (int i = 2; i <= n; ++i) {
		if (r < i) {
			l = r = i; while(r <= n && s[r] == s[r - l + 1]) ++r;
			Z[i] = r - l; --r;
		}
		else {
			int k = i - l + 1;
			if (Z[k] < r - i) Z[i] = Z[k];
			else {
				l = i; while(r <= n && s[r] == s[r - l + 1]) ++r;
				Z[i] = r - l; --r;
			}
		}
		pos[Z[i]].push_back(i);
	}
	
	le[0] = 0; ri[0] = 1; le[n+1] = n; ri[n+1] = n+1; 
	for (int i = 1; i <= n; ++i) le[i] = i-1, ri[i] = i+1;

	for (int len = 1; len <= n; ++len) {
		for (int i = 0; i < pos[len-1].size(); ++i) del(pos[len-1][i]);
		if (mx > len) continue;
		else {
			if (Z[n - len + 1] == len) { ans = len; break; }
		} 
	} 

	cout << ans << endl;
}