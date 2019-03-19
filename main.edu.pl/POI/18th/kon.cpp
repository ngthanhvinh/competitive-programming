#include <iostream>
#include <vector>
#include <stack>
#include <bitset>
using namespace std;

const int N = 5010;

int n, step;
bool e[N][N];
int color[N<<1], low[N<<1], num[N<<1];
bool invalid;
stack <int> st;

#define TRUE 1
#define FALSE 2

void setColor(int u, int c) {
	u -= N;
	if (color[u+N] == 3-c) invalid = 1; else color[u+N] = c;
	if (color[-u+N] == c) invalid = 1; else color[-u+N] = 3-c;
}

void dfs(int u) {
	st.push(u); low[u] = num[u] = ++step;
	for (int i = 1; i <= n; ++i) {
		u -= N; int v = 0;
		if (u < 0 && -u != i && e[-u][i]) v = i+N;
		if (u > 0 && u != i && !e[u][i]) v = -i+N;
		u += N; if (!v) continue;
		if (num[v]) low[u] = min(low[u], num[v]);
		else { dfs(v); low[u] = min(low[u], low[v]); }
		if (color[v] == FALSE) setColor(u, FALSE);
	}
	if (low[u] == num[u]) {
		int v = 0; if (!color[u]) setColor(u, TRUE); 
		do {
			v = st.top(); st.pop(); low[v] = num[v] = 1e9;
			setColor(v, color[u]);
		} while(v != u);
	}	
}

bitset <N> bs[N];
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int k; cin >> k; for (int j = 0; j < k; ++j) { int x; cin >> x; e[i][x] = 1; }
	}

	for (int i = 1; i <= n; ++i) if (!num[i+N]) dfs(i+N);
	for (int i = 1; i <= n; ++i) if (!num[-i+N]) dfs(-i+N); 
	
	if (invalid) return printf("0\n"), 0;
	vector <int> T, F;
	for (int i = 1; i <= n; ++i) if (color[i+N] == TRUE) T.push_back(i); else F.push_back(i);

	int ans = (T.size() != n && F.size() != n) ? 1 : 0;
	// F -> T
	for (int i = 0; i < F.size(); ++i) {
		int u = F[i]; bool ok = 1;
		for (int j = 0; j < T.size(); ++j) if (!e[u][T[j]]) { ok = 0; break; }
		if (ok && T.size() + 1 != n) ++ans;
	}

	// T -> F
	for (int i = 0; i < T.size(); ++i) {
		int u = T[i]; bool ok = 1;
		for (int j = 0; j < F.size(); ++j) if (e[u][F[j]]) { ok = 0; break; }
		if (ok && F.size() + 1 != n) ++ans;
	}

	// T->F & F->T
	bitset <N> allF, allT;
	for (int i = 0; i < F.size(); ++i) {
		for (int j = 0; j < T.size(); ++j) if (e[F[i]][T[j]]) bs[F[i]].set(T[j]);
	}
	for (int i = 0; i < F.size(); ++i) allF.set(F[i]);
	for (int i = 0; i < T.size(); ++i) allT.set(T[i]);
	for (int i = 0; i < T.size(); ++i) {
		int u = T[i]; allT.flip(u); bitset <N> ofu;
		for (int j = 0; j < F.size(); ++j) if (!e[u][F[j]]) ofu.set(F[j]);
		for (int j = 0; j < F.size(); ++j) {
			allF.flip(F[j]); ofu.reset(F[j]); bs[F[j]].reset(u);
			if (allF == ofu && allT == bs[F[j]]) ++ans; 
			allF.flip(F[j]); if (!e[u][F[j]]) ofu.set(F[j]); if (e[u][F[j]]) bs[F[j]].set(u);
		}
		allT.flip(u);
	}
	printf("%d\n", ans);
}