#include <bits/stdc++.h>
using namespace std;

const int N = 3010;

int e[N][N];
int n, m;
bool del[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	while(m--) {
		int u, v; cin >> u >> v;
		e[u][v] = e[v][u] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i+1; j <= n; ++j) if (!del[i] && !del[j] && !e[i][j]) {
			del[i] = del[j] = 1;
		} 
	}

	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (cnt == n / 3) break;
		if (!del[i]) ++cnt, cout << i << ' ';
	}
	cout << endl;
}