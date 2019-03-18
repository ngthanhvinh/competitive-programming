#include <bits/stdc++.h>
using namespace std;

const int N = 32005;

int n, a[N], tmp[N];

void call(int l, int r) {
	if (l == r) return;
	int mid = ((l + r) >> 1);
	call(l, mid); call(mid + 1, r);

	// 00...011...100...011...1
	int lef = 1e9;
	for (int i = mid; i >= l; --i) if (tmp[i] == 1) lef = i; else break;
	int rig = -1e9;
	for (int i = mid + 1; i <= r; ++i) if (tmp[i] == 0) rig = i; else break;
	if (lef < rig) {
		printf("%d %d\n", lef, rig);
		if (lef < lef + rig - mid - 1) printf("%d %d\n", lef, lef + rig - mid - 1);
		if (lef + rig - mid < rig) printf("%d %d\n", lef + rig - mid, rig);
		//printf("\n");
	}

	int cnt0 = 0;
	for (int i = l; i <= r; ++i) cnt0 += tmp[i] == 0;
	for (int i = l; i <= l + cnt0 - 1; ++i) tmp[i] = 0;
	for (int i = l + cnt0; i <= r; ++i) tmp[i] = 1;
}

void fill(int l, vector<int> &vec, int &nelement) {
	sort(vec.begin(), vec.end());
	for (int i = 0; i < vec.size(); ++i) {
		tmp[l + nelement] = a[vec[i]], ++nelement;
	}
}

void solve(int l, int r) {
	if (l >= r) return;

	vector< pair<int,int> > buf;
	for (int i = l; i <= r; ++i) {
		buf.push_back(make_pair(a[i], i));
	}
	sort(buf.begin(), buf.end());

	int med = (buf.size() - 1) / 2;

	for (int i = 0; i <= med; ++i) 
		tmp[buf[i].second] = 0;
	for (int i = med + 1; i < buf.size(); ++i) 
		tmp[buf[i].second] = 1;

	call(l, r);

	// reset the array
	int nelement = 0;
	// 0
	vector<int> vec;
	for (int i = 0; i <= med; ++i) vec.push_back(buf[i].second);
	fill(l, vec, nelement);
	// 1
	vec.clear();
	for (int i = med + 1; i < buf.size(); ++i) vec.push_back(buf[i].second);
	fill(l, vec, nelement);

	for (int i = l; i <= r; ++i) a[i] = tmp[i];
	
	solve(l, l + med);
	solve(l + med + 1, r);
}

int main() {
	//freopen("in", "r", stdin);
	//freopen("out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	solve(1, n);
}