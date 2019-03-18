#include <bits/stdc++.h>
using namespace std;
const int N = 30010;

int n, q, b, a[N];
vector <int> v[200];

void debug() {
	for (int i = 0; i <= n / b; i++) {
		for (int j = 0; j < v[i].size(); j++) cout << v[i][j] << ' ';
		cout << "\n";
	}
	cout << "\n";
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	//ios_base::sync_with_stdio(false); cin.tie(0);
	scanf("%d", &n); for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	b = (int)sqrt(n);
	for (int i = 0; i <= (n / b); i++) {
		for (int j = 0; j < b && i * b + j < n; j++) {
			v[i].push_back(a[i * b + j]);
		}
		sort(v[i].begin(), v[i].end());
	}
	scanf("%d", &q);
	while(q--) {
		int type; scanf("%d", &type);
		if (!type) {
			int pos, val; scanf("%d%d", &pos, &val); pos--;
			int block = pos / b;
			// block i has a[i * b], a[i * b + 1], ..., a[min(i * b + (b - 1), n - 1)];
			int p = lower_bound(v[block].begin(), v[block].end(), a[pos]) - v[block].begin();
			v[block][p] = val; a[pos] = val;
			for (int i = p; i < v[block].size() - 1; i++) if (v[block][i] > v[block][i + 1]) swap(v[block][i], v[block][i + 1]); else break;
			for (int i = p; i > 0; i--) if (v[block][i] < v[block][i - 1]) swap(v[block][i], v[block][i - 1]); else break;
			//debug();
		}
		else {
			int l, r, k; scanf("%d%d%d", &l, &r, &k); l--; r--;
			// a[l] in block (l / b)th
			// a[r] in block (r / b)th
			// so we should find out how many numbers greater than k from block (l / b + 1) to block (r / b - 1) 
			// the remainders we should run with O(b)
			int ans = 0;
			for (int i = (l / b) + 1; i <= (r / b) - 1; i++) {
				int p = upper_bound(v[i].begin(), v[i].end(), k) - v[i].begin();
				// for j from p to (v[i].size() - 1) v[i][j] > k
				ans += (v[i].size() - p);
			}
			if ((l / b) == (r / b)) {
				for (int i = l; i <= r; i++) if (a[i] > k) ans++;
				printf("%d\n", ans); continue;
			}
			for (int i = l; i < ((l / b) + 1) * b; i++) if (a[i] > k) ans++;
			for (int i = r; i >= (r / b) * b; i--) if (a[i] > k) ans++;
			printf("%d\n", ans);
		}
	}
}