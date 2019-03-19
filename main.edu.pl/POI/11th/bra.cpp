#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
int n, f[10005], cnt1[10005], cnt2[10005], sz[10005], s1[10005], s2[10005], pref[10005];
vector<int> a[10005];
string str[] = {"0", "1/2", "1"};
 
void input() {
	cin >> n;
	for(int i = 2; i < n; ++i) {
		cin >> sz[i];
		for(int j = 1; j <= sz[i]; ++j) {
			int u;
			cin >> u;
			a[u].push_back(i);
		}
	}
}
 
void solve(int val) {
	for(int i = 0; i < n; ++i) f[i] = val, cnt1[i] = 0, cnt2[i] = 0, pref[i] = 0;
	queue<int> qu;
	if(val) f[0] = 0, qu.push(0); else f[1] = 2, qu.push(1);
	while(qu.size()) {
		int u = qu.front(); qu.pop();
		for(int i = 0; i < a[u].size(); ++i) {
			int v = a[u][i];
			if(f[u] == 2 - val && pref[u]) cnt2[v]--;
			if(f[u] == 2 - val) cnt1[v]++; else cnt2[v]++;
			if(cnt1[v] * 2 == sz[v] - cnt2[v]) f[v] = 1, pref[v] = true, qu.push(v);
			else if(cnt1[v] * 2 > sz[v] - cnt2[v] && f[v] != 2 - val) f[v] = 2 - val, qu.push(v); 
		}
	}
}
 
int main() {
	input();
	solve(0); for(int i = 0; i < n; ++i) s1[i] = f[i];
	solve(2); for(int i = 0; i < n; ++i) s2[i] = f[i];
	for(int i = 0; i < n; ++i) if(s1[i] == s2[i]) cout << str[s1[i]] << '\n'; else cout << "?\n";
}