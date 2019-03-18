// currently WA
#include <bits/stdc++.h>
using namespace std;

const int N = 300005;
string s, t;
int n; // size of s

//--------------------------------------------------------------------------------
struct SuffixArray {
	typedef pair<int,int> ii;
	typedef pair<ii, int> II;
	int sa[N];
	int lcp[N];
	int p[N][19];

	// for sorting
	ii A[N];
	II AA[N];
	vector<II> srt[N];
	// ---------------------------------------------------------------------------------------

	void buildSA() {
		int cnt;
		// sort by the first character
		ii A[N];
		for (int i = 1; i <= n; ++i) A[i] = make_pair(s[i], i);
		sort(A + 1, A + n + 1);
		cnt = 0;
		for (int i = 1; i <= n; ++i) 
			p[A[i].second][0] = (i == 1 || (i > 1 && A[i].first != A[i-1].first)) ? ++cnt : cnt;
		
		// build Suffix Array using counting sort
		for (int k = 1; k < 19; ++k) {
			for (int i = 1; i <= n; ++i) {
				AA[i] = make_pair(ii(p[i][k-1], (i + (1 << k-1) <= n) ? p[i + (1 << k-1)][k-1] : 0), i);
			}
			// sort by second part
			for (int i = 1; i <= n; ++i) srt[AA[i].first.second].push_back(AA[i]); // second part
			cnt = 0;
			for (int i = 0; i <= n; ++i) {
				while(srt[i].size()) AA[++cnt] = srt[i].back(), srt[i].pop_back();	
			}
			// sort by first part
			for (int i = 1; i <= n; ++i) srt[AA[i].first.first].push_back(AA[i]); // first part
			cnt = 0;
			for (int i = 0; i <= n; ++i) {
				reverse(srt[i].begin(), srt[i].end());
				while(srt[i].size()) AA[++cnt] = srt[i].back(), srt[i].pop_back();
			}
			// restore p[][k]
			cnt = 0;
			for (int i = 1; i <= n; ++i)
				p[AA[i].second][k] = (i == 1 || (i > 1 && AA[i].first != AA[i-1].first)) ? ++cnt : cnt;
		}

		// sa
		for (int i = 1; i <= n; ++i) sa[p[i][18]] = i;
	}

	int getLCP(int x, int y) {
		int ret = 0;
		for (int i = 18; i >= 0; --i) {
			if (x + (1 << i) - 1 <= n && y + (1 << i) - 1 <= n && p[x][i] == p[y][i]) {
				x += (1 << i); y += (1 << i); ret += (1 << i);
			}
		}
		return ret;
	}

	void buildLCP() {
		// lcp[i] (1 <= i < n) is the longest common prefix of sa[i] and sa[i+1]
		for (int i = 1; i < n; ++i) {
			lcp[i] = getLCP(sa[i], sa[i+1]);
		}
		lcp[n] = 0;
	}
} sa;

// -------------------------------------------------------------------------------
int to[N * 2]; // for Manacher
void manacher() {
	int n2 = 2 * n + 1;
	string t = string(n2, '.');
	for (int i = 1; i < n2; i += 2) t[i] = s[(i - 1) / 2];

	int c = 0, r = 0;
	for (int i = 1; i < n2-1; ++i) {
		int i_mirror = 2 * c - i; // i' = c - (i - c)
		to[i] = (r > i) ? min(r - i, to[i_mirror]) : 0;
		// attempt to expand palindrome centered at i
		while(i + 1 + to[i] < n2 && i - 1 - to[i] >= 0 && t[i + 1 + to[i]] == t[i - 1 - to[i]]) ++to[i];
		if (i + to[i] > r) { // update c and r
			c = i;
			r = i + to[i];
		}
	}
}
// -------------------------------------------------------------------------------
int len[N]; // len[i] is the longest palindrome centered at i
int a[N]; // new lcp[]
int l[N], r[N];
long long ans;
void solve(int x) { 
	// x = 0: even
	// x = 1: odd
	for (int i = 1; i <= n; ++i) {
		if (x == 0) { // even
			len[i] = to[2 * i - 2] / 2;
		} else { // odd
			len[i] = (to[2 * i - 1] + 1) / 2;
		}
	}

	// replace lcp[] with a[]
	for (int i = 1; i < n; ++i) {
		a[i] = min(sa.lcp[i], min(len[sa.sa[i]], len[sa.sa[i + 1]]));
	}

	// KAGAIN
	for (int i = 1; i <= n; ++i) {
		l[i] = i;
		while(l[i] > 1 && a[i] <= a[l[i] - 1]) l[i] = l[l[i] - 1];
	}
	for (int i = n; i >= 1; --i) {
		r[i] = i;
		while(r[i] < n && a[i] <= a[r[i] + 1]) r[i] = r[r[i] + 1];
	}
	for (int i = 1; i <= n; ++i) cerr << a[i] << ' '; cerr << endl;
	for (int i = 1; i <= n; ++i) {
		ans = max(ans, 1LL * (a[i] * 2 - x) * (r[i] - l[i] + 2)); // real_len = a[i] * 2 - x
	}
	for (int i = 1; i <= n; ++i) {
		ans = max(ans, (long long)len[i] * 2 - x);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> s;
	n = s.size();
	manacher();
	s = ' ' + s;
	sa.buildSA();
	sa.buildLCP();

	solve(1);
	solve(0);

	cout << ans << endl;
}