#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

const int N = 3000010;

int n;
long long t, a[N];
deque <int> mn, mx;
long long mxval = 2e9, mnval = -2e9;
int ans;

int main() {
	scanf("%lld%d", &t, &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
	int cur = 1; mn.push_back(1); mx.push_back(1); mxval = a[1], mnval = a[1]; ans = 1;
	for (int i = 2; i <= n; ++i) {
		while(!mn.empty() && a[i] <= a[mn.back()]) mn.pop_back(); mn.push_back(i);
		while(!mx.empty() && a[i] >= a[mx.back()]) mx.pop_back(); mx.push_back(i);
		mxval = max(mxval, a[mx.front()]); mnval = min(mnval, a[mn.front()]);
		while(cur < i && mxval - mnval > t) {
			++cur;
			if (cur > mn.front()) mn.pop_front(), mnval = a[mn.front()];
			if (cur > mx.front()) mx.pop_front(), mxval = a[mx.front()];
		}
		ans = max(ans, i - cur + 1);
	}
	printf("%d\n", ans);
}