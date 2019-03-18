#include <bits/stdc++.h>
using namespace std;
const int N = 50010, S = 225;
int n, m, B;
int a[N], last_in_blocks[S][N], blockAns[N], prev[N], next[N], ind[N<<1];

void precompute() {
	for (int i = 1; i <= n; i++) prev[i] = 0, next[i] = n+1;
	for (int i = 1; i <= n; i++) {
		int j = ind[a[i] + N];
		if (j) prev[i] = j, next[j] = i;
		ind[a[i] + N] = i;
 	}
 	for (int i = 0; i <= B; i++) {
 		int E = i * S;
 		
 	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; for (int i = 1; i <= n; i++) { int x; cin >> x; a[i] = a[i-1] + x; }
	int B = n / S;
}