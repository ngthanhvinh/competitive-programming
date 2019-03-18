#include <bits/stdc++.h>
using namespace std;

const int N = 300005;

struct slope {
	priority_queue <long long> pq;
	long long starting_value;
	long long starting_slope;
} S[N];

int n, m, p[N], a[N];
long long ans;

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 2; i <= n + m; ++i) {
		scanf("%d %d", &p[i], &a[i]);
		if (i >= n + 1) { // leaf
			S[i].pq.push(a[i]); S[i].pq.push(a[i]); // -x + a and x - a
			S[i].starting_slope = -1;
			S[i].starting_value = a[i]; // -0 + a
		}
	}

	for (int i = n + m; i >= 2; --i) {
		if (i <= n) { // not leaf
			// fix slopes of S[i]
			long long last_slope = S[i].starting_slope + S[i].pq.size();
			while(last_slope > 1) {
				S[i].pq.pop(); --last_slope;
			}

			long long x1 = S[i].pq.top(); S[i].pq.pop(); // x-coordinate at slope 1
			long long x0 = S[i].pq.top(); S[i].pq.pop(); // x-coordinate at slope 0

			S[i].starting_value += a[i];
			S[i].pq.push(x0 + a[i]);
			S[i].pq.push(x1 + a[i]);
		}

		// update to p[i]
		int par = p[i];
		if (S[par].pq.size() < S[i].pq.size()) {
			swap(S[par], S[i]);
		}
		S[par].starting_value += S[i].starting_value;
		S[par].starting_slope += S[i].starting_slope;
		while(!S[i].pq.empty()) {
			long long x = S[i].pq.top(); S[i].pq.pop();
			S[par].pq.push(x);
		}
	}

	// root: 1
	long long starting_value = S[1].starting_value;
	long long starting_slope = S[1].starting_slope;

	vector<long long> pts;

	while(!S[1].pq.empty()) {
		pts.push_back(S[1].pq.top()); S[1].pq.pop();
	}
	pts.push_back(0);
	reverse(pts.begin(), pts.end());

	ans = starting_value;
	for (int i = 1; i < pts.size(); ++i) {
		starting_value += starting_slope * (pts[i] - pts[i-1]);
		++starting_slope;
		ans = min(ans, starting_value);
	}

	printf("%lld\n", ans);
}