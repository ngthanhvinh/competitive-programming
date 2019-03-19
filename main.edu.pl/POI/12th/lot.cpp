#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, p[N], d[N], p2[N], d2[N], poi[N];
bool ans[N];
const string s[] = {"NIE", "TAK"};
void solve(int *P, int *D) {
	int StartPos = 1;
	long long CurSum = 0, Min = 0;
	for(int i = 1; i <= n; ++ i) {
		CurSum += (P[i] - D[i]);
		if(CurSum < Min) {
			StartPos = i + 1;
			Min = CurSum;
		}
	}
	if(CurSum < 0) return;
	if(StartPos == n + 1) StartPos = 1;
	ans[poi[StartPos]] = 1, CurSum = 0;
	for(int i = StartPos - 1; i >= 1; -- i) {
		CurSum += (P[i] - D[i]);
		if(CurSum >= 0) 
			ans[poi[i]] = 1, CurSum = 0;
	}
	for(int i = n; i > StartPos; -- i) {
		CurSum += (P[i] - D[i]);
		if(CurSum >= 0) 
			ans[poi[i]] = 1, CurSum = 0;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++ i) {
		cin >> p[i] >> d[i];
		poi[i] = i;
	}
	solve(p, d);
	p2[1] = p[1], d2[1] = d[n];
	for(int i = n; i > 1; -- i) {
		p2[n - i + 2] = p[i];
		poi[n - i + 2] = i;
		d2[n - i + 2] = d[i - 1];
	}
	solve(p2, d2);
	for(int i = 1; i <= n; ++ i)
		cout << s[ans[i]] << '\n';
}