#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m, a[N];
string s, t;
int f[N], nxt[N][2];
vector <int> vec[2];

bool valid(int l, int r) {
	if (l > r) return true;
	int diff = f[r] - f[l - 1];
	return diff == 0 || diff == r - l + 1;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> s >> t;
	n = s.size();
	m = t.size();
	s = ' ' + s;
	t = ' ' + t;

	// calc f, vec
	for (int i = 1; i <= n; ++i) {
		f[i] = f[i - 1] + (s[i] == 'A');
		vec[s[i] - 'A'].push_back(i);
	}
	// calc nxt
	nxt[n + 1][0] = n + 1;
	nxt[n + 1][1] = n + 1;
	for (int i = n; i >= 1; --i) {
		int cur = s[i] - 'A';
		nxt[i][0] = nxt[i + 1][0];
		nxt[i][1] = nxt[i + 1][1];
		nxt[i][cur] = i;
	}

	// solve
	int ptr = 0;
	for (int i = 1; i <= m; ++i) {
		int cur = t[i] - 'A';
		ptr = nxt[ptr + 1][cur];
		a[i] = ptr;
		if (ptr == n + 1) { // t is not a subsequence of s
			printf("NO\n");
			return 0;
		}
	}

	// fix the positions
	a[m + 1] = n + 1;
	for (int i = m; i >= 1; --i) {
		if (valid(a[i] + 1, a[i + 1] - 1)) {
			continue;
		}
		// binary search for the lowest position that is valid
		int cur = t[i] - 'A';
		int low = lower_bound(vec[cur].begin(), vec[cur].end(), a[i] + 1) - vec[cur].begin();
		int high = upper_bound(vec[cur].begin(), vec[cur].end(), a[i + 1] - 1) - vec[cur].begin() - 1;
		// low <= high
		while(low < high) {
			int mid = ((low + high) >> 1);
			if (valid(vec[cur][mid] + 1, a[i + 1] - 1)) {
				high = mid;
			} else {
				low = mid + 1;
			}
		}
		a[i] = vec[cur][low];
	}

	if (!valid(1, a[1] - 1)) { // first part
		printf("NO\n");
		return 0;
	}

	printf("YES\n");
	for (int i = 1; i <= m; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
}