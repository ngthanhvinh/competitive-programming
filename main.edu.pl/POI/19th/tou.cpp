#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000010;

int N, M, K;
int par[MAX];

typedef pair<int,int> ii;
vector <ii> E;
vector <ii> ans;

int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
void join(int p, int q) { par[anc(p)] = anc(q); }

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> N >> M >> K;
	for (int i = 1; i <= N; ++i) par[i] = i;
	while(M--) {
		int a, b; cin >> a >> b;
		if (a > K) join(a, b);
		else E.push_back(ii(a,b));
	}

	for (int i = 0; i < E.size(); ++i) {
		int a = E[i].first, b = E[i].second;
		if (anc(a) != anc(b)) join(a, b);
		else ans.push_back(ii(a,b));
	}

	printf("%d\n", (int)ans.size());
	for (int i = 0; i < (int)ans.size(); ++i) printf("%d %d\n", ans[i].first, ans[i].second);
}