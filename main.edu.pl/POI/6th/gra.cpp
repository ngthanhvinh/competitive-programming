#include <bits/stdc++.h>
using namespace std;
const int N = 50010;
typedef pair<int,int> ii;
typedef pair<ii, int> II;

int n;
vector <II> v;
int cnt[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n-2; ++i) {
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		if (a > b) swap(a, b); if (a > c) swap(a, c); if (b > c) swap(b, c);
		v.push_back(II(ii(a,b), i));
		v.push_back(II(ii(b,c), i));
		v.push_back(II(ii(a,c), i));
	} 
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); ++i) {
		if (i > 0 && v[i].first == v[i-1].first) cnt[v[i].second]++, cnt[v[i-1].second]++;
	}

	n -= 2;
	if (cnt[1] == 1 || (n-1) % 2 == 1) printf("TAK\n");
	else printf("NIE\n");
}