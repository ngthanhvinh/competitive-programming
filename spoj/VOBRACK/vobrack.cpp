#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef pair<ii, int> II;

#define sz second
#define x first.first
#define y first.second

const int N = 1010, M = 10010, INF = 1e9;

string str;
int n;
II a[N];
int f[M], g[M];

bool cmp(II u, II v) {
	if (u.first == v.first) return u.sz > v.sz;
	if (u.x >= 0 && v.x >= 0) return u.y > v.y;
	if (u.x < 0 && v.x < 0) return u.x - u.y > v.x - v.y;
	return u.x >= 0 && v.x < 0;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> str; a[i].sz = str.size();
		for (int j = 0; j < str.size(); ++j) a[i].x += (str[j] == '(') ? 1 : -1, a[i].y = min(a[i].y, a[i].x);
	}
	sort(a + 1, a + n + 1, cmp);
	
	for (int j = 0; j < M; ++j) f[j] = -INF; f[0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < M; ++j) g[j] = f[j], f[j] = -INF;
		for (int j = 0; j < M; ++j) {
			if (j + a[i].y >= 0 && j + a[i].x < M) f[j + a[i].x] = max(f[j + a[i].x], g[j] + a[i].sz);
			f[j] = max(f[j], g[j]);
		}
	}
	cout << f[0] << endl;	
}