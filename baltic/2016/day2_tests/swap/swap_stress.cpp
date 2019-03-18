#include <bits/stdc++.h>
using namespace std;
 
const int N = 200005;
const int MAX = 1500005;
const int INF = 1e9;
 
typedef pair<int, int> ii;
 
int n, a[N], id;
vector <ii> vec[MAX];
int best[MAX];
map <int, int> mp[N];
 
void merge(vector <ii> &C, const vector <ii> &A, const vector <ii> &B) {
	for (int ia = 0, ib = 0; ia < A.size() || ib < B.size(); ) {
		if (ib == B.size() || (ia < A.size() && A[ia].first < B[ib].first)) {
			C.push_back(A[ia++]);
		} else {
			C.push_back(B[ib++]);
		}
	}
}
 
int dp(int v, int val) {
	if (val == INF) return 0; // empty vector
	if (mp[v].find(val) != mp[v].end()) {
		return mp[v][val];
	}
 
	mp[v][val] = ++id;
	int curid = id;
	int l = (v * 2 <= n) ? a[v * 2] : INF;
	int r = (v * 2 + 1 <= n) ? a[v * 2 + 1] : INF;
 
	int w[3] = {val, l, r};
	if (w[0] < min(w[1], w[2])) {
		vec[curid].push_back(make_pair(v, w[0]));
		merge(vec[curid], vec[dp(v << 1, w[1])], vec[dp(v << 1 | 1, w[2])]);
	}
	else if (w[1] < min(w[0], w[2])) {
		vec[curid].push_back(make_pair(v, w[1]));
		merge(vec[curid], vec[dp(v << 1, w[0])], vec[dp(v << 1 | 1, w[2])]);
	}
	else {
		// -> w[2], w[0], w[1]
		// -> w[2], w[1], w[0]
		vector <ii> cand[2];
		cand[0].push_back(make_pair(v, w[2]));
		cand[1].push_back(make_pair(v, w[2]));
		merge(cand[0], vec[dp(v << 1, w[0])], vec[dp(v << 1 | 1, w[1])]);
		merge(cand[1], vec[dp(v << 1, w[1])], vec[dp(v << 1 | 1, w[0])]);
 
		if (cand[0] < cand[1]) {
			best[curid] = 0;
			vec[curid] = cand[0];
		} else {
			best[curid] = 1;
			vec[curid] = cand[1];
		}
	}
 
	// printf("dp %d %d\n", v, val);
	// for (auto &i : vec[curid]) {
	// 	printf("%d ", i.second);
	// }
	// printf("\n");
	return curid;
}
 
void trace(int v, int val) {
	if (val == INF) return;
	int l = (v * 2 <= n) ? a[v * 2] : INF;
	int r = (v * 2 + 1 <= n) ? a[v * 2 + 1] : INF;
 
	int w[3] = {val, l, r};
	if (w[0] < min(w[1], w[2])) {
		a[v] = w[0];
		trace(v << 1, w[1]);
		trace(v << 1 | 1, w[2]);
	}
	else if (w[1] < min(w[0], w[2])) {
		a[v] = w[1];
		trace(v << 1, w[0]);
		trace(v << 1 | 1, w[2]);
	}
	else {
		a[v] = w[2];
		int curid = dp(v, val);
		trace(v << 1, w[best[curid]]);
		trace(v << 1 | 1, w[best[curid] ^ 1]);
	}
}
 
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
 
	dp(1, a[1]);
	trace(1, a[1]);
 
	for (int i = 1; i <= n; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
}