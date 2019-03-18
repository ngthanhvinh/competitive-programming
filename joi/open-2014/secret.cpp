#include <bits/stdc++.h>
#include "secret.h"
using namespace std;
const int N = 1010;
int n, a[N];
int le[N][N], ri[N][N];
vector <int> Pos;

void Solve(int l, int r) {
	if (l >= r) return;
	int m = (l + r) >> 1; Pos.push_back(m);
	Solve(l, m); Solve(m + 1, r);
	le[m][m] = a[m]; for (int i = m-1; i >= l; i--) le[m][i] = Secret(a[i], le[m][i+1]);
	ri[m+1][m+1] = a[m+1]; for (int i = m+2; i <= r; i++) ri[m+1][i] = Secret(ri[m+1][i-1], a[i]); 
}

void Init(int N, int A[]) {
	n = N; for (int i = 0; i < n; i++) a[i+1] = A[i];	
	Solve(1, n);
}

int M;

int Query(int L, int R) {
	L++; R++;
	if (L == R) return a[R];
	for (int i = 0; i < (int)Pos.size(); i++) if (Pos[i] >= L && Pos[i] <= R) { M = Pos[i]; break; }
	if (M == R) return le[M][L];
	else return Secret(le[M][L], ri[M+1][R]);
}

/*
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
	Init(9, A);
	int q; cin >> q;
	while(q--) {
		int l, r; cin >> l >> r;
		cout << Query(l, r) << endl;
	}
}
*/