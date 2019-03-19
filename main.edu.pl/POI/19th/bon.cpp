#include <bits/stdc++.h>
using namespace std;

const int N = 1000001;

int n, m;
bool del[N];
bool ok[N];
int cur[N];

long long ans;
vector <long long> vec;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> m; for (int i = 1; i <= m; ++i) { int x; cin >> x; ok[x] = 1; }

	cin >> n;
	for (int i = 1; i < N; ++i) cur[i] = i;
	for (int i = 1; i <= n; ++i) {
		int x; cin >> x; int cnt = x;
		while(cur[x] < N && cnt) {
			if (del[cur[x]]) { cur[x] += x; continue; }
			else {
				--cnt, del[cur[x]] = 1, ++ans;
				if (ok[cur[x]]) vec.push_back(ans);
				cur[x] += x;
			} 
		}
		ans += cnt;
	}

	printf("%d\n", (int)vec.size());
	for (int i = 0; i < vec.size(); ++i) printf("%lld\n", vec[i]);
}
