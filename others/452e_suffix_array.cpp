#include <bits/stdc++.h>
using namespace std;

const int N = 300005;
const int INF = 1e9;
const int mod = 1e9 + 7;
#define real _real
#define fi first
#define se second

pair<int,int> real[N]; // (str, ptr)
int id[3][N];
string s[3];
int n[3];
int tot;

// SUFFIX ARRAY
namespace SuffixArray {
	int gap;
	int tmp[N][19]; // temp
	int pos[N];
	int sa[N];
	int lcp[N];

	bool cmpSuf(int x, int y) {
		int str_x = real[x].fi, ptr_x = real[x].se;
		int str_y = real[y].fi, ptr_y = real[y].se;

		ptr_x += gap;
		ptr_y += gap;
		pair <int, int> px = make_pair(pos[x], ptr_x < n[str_x] ? pos[ id[str_x][ptr_x] ] : -INF);
		pair <int, int> py = make_pair(pos[y], ptr_y < n[str_y] ? pos[ id[str_y][ptr_y] ] : -INF);
		
		return px < py;
	}

	void buildSA() {
		for (int i = 1; i <= tot; ++i) sa[i] = i, pos[i] = tmp[i][0] = s[real[i].fi][real[i].se];
		for (int j = 1; j <= 18; ++j) { // "gap""gap"
			gap = (1 << j - 1);
			sort(sa + 1, sa + tot + 1, cmpSuf);
			tmp[sa[1]][j] = 1;
			for (int i = 2; i <= tot; ++i) tmp[sa[i]][j] = tmp[sa[i - 1]][j] + cmpSuf(sa[i - 1], sa[i]);
			for (int i = 1; i <= tot; ++i) pos[sa[i]] = tmp[sa[i]][j];
		}
	}

	int findLCP(int i, int pi, int j, int pj) {
		int ret = 0;
		for (int k = 18; k >= 0; --k) {
			if (pi + (1 << k) - 1 < n[i] && pj + (1 << k) - 1 < n[j] && tmp[id[i][pi]][k] == tmp[id[j][pj]][k]) {
				pi += (1 << k);
				pj += (1 << k);
				ret += (1 << k);
			}
		}
		return ret;
	}

	void buildLCP() {
		for (int i = 1; i <= tot - 1; ++i) {
			lcp[i] = findLCP(real[sa[i]].fi, real[sa[i]].se, real[sa[i + 1]].fi, real[sa[i + 1]].se);
		}
	}
}
using namespace SuffixArray;
// END OF SUFFIX ARRAY

// DSU
int par[N];
int cnt[N][3];
int anc(int p) { return p == par[p] ? p : par[p] = anc(par[p]); }
int join(int p, int q) {
	p = anc(p), q = anc(q);

	int ret = 0;
	ret = (ret + 1LL * cnt[p][0] * cnt[p][1] * cnt[p][2]) % mod;
	ret = (ret + 1LL * cnt[q][0] * cnt[q][1] * cnt[q][2]) % mod;

	par[p] = q;
	for (int i = 0; i < 3; ++i) cnt[q][i] += cnt[p][i], cnt[p][i] = 0;

	ret = (mod - ret) % mod; // - ret
	ret = (ret + 1LL * cnt[q][0] * cnt[q][1] * cnt[q][2]) % mod;

	return ret;
}
// END OF DSU

vector <int> vec[N];
int res[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> s[0] >> s[1] >> s[2];
	
	for (int str = 0; str < 3; ++str) {
		n[str] = s[str].size();
		for (int i = 0; i < n[str]; ++i) {
			++tot;
			real[tot] = make_pair(str, i);
			id[str][i] = tot;
		}
	}

	SuffixArray::buildSA();
	// for (int i = 1; i <= tot; ++i) {
	// 	printf("%d -> str = %d ptr = %d\n", i, real[sa[i]].fi, real[sa[i]].se);
	// }
	SuffixArray::buildLCP();

	// solve
	for (int i = 1; i <= tot; ++i) {
		par[i] = i;
		cnt[i][real[i].fi] = 1;
	}
	for (int i = 1; i <= tot - 1; ++i) {
		vec[lcp[i]].push_back(i);
	}

	for (int w = tot; w >= 1; --w) {
		for (auto &i : vec[w]) {
			res[w] += join(sa[i], sa[i + 1]); if (res[w] >= mod) res[w] -= mod;
		}
	}

	for (int w = tot; w >= 1; --w) {
		res[w] += res[w + 1]; if (res[w] >= mod) res[w] -= mod;
	}
	int minlen = min({n[0], n[1], n[2]});
	for (int w = 1; w <= minlen; ++w) {
		printf("%d ", res[w]);
	}
}