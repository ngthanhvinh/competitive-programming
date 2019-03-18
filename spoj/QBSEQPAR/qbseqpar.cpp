#include <bits/stdc++.h>
using namespace std;
const int N = 15010;

int n, a[N], m, s[N], k;
typedef pair <int, int> ii;
vector <int> compress, Fmin, Fmax;

struct FenwickTree {
	int mx[N<<1], mn[N<<1];
	FenwickTree() { for (int i = 0; i < (N<<1); i++) mx[i] = -1e9, mn[i] = 1e9; }
	void upd(int x, int Min, int Max) { for (; x > 0; x -= x & -x) mn[x] = min(mn[x], Min), mx[x] = max(mx[x], Max); }
	ii get(int x) { 
		int Min = 1e9, Max = -1e9; 
		for (; x <= m; x += x & -x) Min = min(Min, mn[x]), Max = max(mx[x], Max); 
		return ii(Min, Max); 
	}
};

void process(int x) {
	compress.clear(); Fmin.assign(n + 1, (int)1e9); Fmax.assign(n + 1, (int)-1e9); Fmin[0] = Fmax[0] = 0;
	for (int i = 0; i <= n; i++) compress.push_back(s[i]), compress.push_back(s[i] + x);
	//for (int i = 0; i < compress.size(); i++) cout << compress[i] << ' '; cout << "\n";
	sort(compress.begin(), compress.end());
}

int pos(int val) { return lower_bound(compress.begin(), compress.end(), val) - compress.begin() + 1; }

bool f(int x) {
	process(x); m = compress.size() + 5;
	FenwickTree bit; int p = pos(x); bit.upd(p, 0, 0);
	for (int i = 1; i <= n; i++) {
		int p = pos(s[i]);
		ii GET = bit.get(p);
		Fmax[i] = max(Fmax[i], GET.second + 1);
		Fmin[i] = min(Fmin[i], GET.first + 1);
		//cout << i << ' ' << Fmin[i] << ' ' << Fmax[i] << "\n";
		p = pos(s[i] + x);
		bit.upd(p, Fmin[i], Fmax[i]);
	}
	if (k >= Fmin[n] && k <= Fmax[n]) return 1;
	else return 0;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k; for (int i = 1; i <= n; i++) cin >> a[i], s[i] = s[i - 1] + a[i];
	int l = -1e9, r = 1e9;
	while(l != r) {
		int mid = ((l + r) >> 1);
		if (f(mid)) r = mid;
		else l = mid + 1; 
	}
	printf("%d\n", l);
}