#include <bits/stdc++.h>
using namespace std;

int n = 5;
int r[5], c[5];
int R[5], C[5];
vector< pair<int,int> > row, col;
int a[5][5], res[5][5];
int val[26];
bool used[26];
bool swapped;

void reset() {
	for (int cell = (n-1) * n; cell < n * n; ++cell) used[val[cell]] = 0, val[cell] = 0;
}

void print() {
	for (int cell = 0; cell < n * n; ++cell) {
		int x = cell / n, y = cell % n;
		if (!swapped) res[row[x].second][col[y].second] = val[cell];
		else res[col[y].second][row[x].second] = val[cell];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) printf("%d ", res[i][j]);
		printf("\n");
	}
	exit(0);
}

void out() {
	int sumR = 0;
	for (int cell = (n-1) * n; cell < n * n; ++cell) {
		int v = c[cell % n] - C[cell % n];
		sumR += v;
		if (v > n * n || v <= 0 || used[v]) {
			reset();
			return;
		}
		val[cell] = v;
		used[val[cell]] = 1;
	}
	if (sumR != r[n-1]) { reset(); return; }
	print();

	exit(0);
}

void backt(int pos) {
	if (pos == (n - 1) * n) return out();
	if (pos % n == n - 1) {
		int v = r[pos / n] - R[pos / n];
		if (v > n * n || v <= 0 || used[v]) return;
		used[v] = 1; val[pos] = v; R[pos / n] += v; C[pos % n] += v; backt(pos + 1);
		used[v] = 0; val[pos] = 0; R[pos / n] -= v; C[pos % n] -= v;
		return;
	}
	int x = pos / n, y = pos % n;
	for (int v = 1; v <= n * n; ++v) if (!used[v] && v + R[x] <= r[x] && v + C[y] <= c[y]) {
		R[x] += v; C[y] += v; val[pos] = v; used[v] = 1; backt(pos + 1);
		R[x] -= v; C[y] -= v; val[pos] = 0; used[v] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	for (int i = 0; i < n; ++i) cin >> r[i], row.push_back(make_pair(r[i],i));
	for (int i = 0; i < n; ++i) cin >> c[i], col.push_back(make_pair(c[i],i));
	sort(row.begin(), row.end());
	sort(col.begin(), col.end());
	if (row[0].first > col[0].first) row.swap(col), swapped = true;
	for (int i = 0; i < n; ++i) r[i] = row[i].first;
	for (int i = 0; i < n; ++i) c[i] = col[i].first;

	backt(0);
	
}