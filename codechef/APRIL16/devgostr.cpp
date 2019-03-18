#include <bits/stdc++.h>
using namespace std;
#define ff(i, a, b) for (int i = a; i <= b; i++)
typedef vector<int> vi;
const int N = 51;

int n, k, str[N], v, bt[N];
string s;
int ans;
vector <string> S[16];

bool check(int pos, int last, int a[]) {
	for (int d = 1; pos - 2 * d > 0; ++d) if (a[pos-d] == a[pos - 2*d] && a[pos-d] == last) return 0;
	return 1;
}

void backt(int pos, int a[], int cnt, int last, int p) {
	//cout << pos << ' ' << cnt << ' ' << last << ' ' << p << endl;
	if (p > k) return;
    if (pos == n+1) { ans++; return; }
   	if (cnt < 2) { if (check(pos, last, a)) a[pos] = last, backt(pos+1, a, cnt+1, last, p + (last != str[pos])), a[pos] = 0; }
   	for (int next = 1; next <= v; next++) if (next != last) {
   		if (check(pos, next, a)) a[pos] = next, backt(pos+1, a, 1, next, p + (next != str[pos])), a[pos] = 0;
   	}
}

void preBackt(int pos, int a[], int cnt, int last, string cur) {
	//cout << pos << ' ' << cnt << ' ' << last << ' ' << endl;
    if (pos == n+1) { S[n].push_back(cur); return; }
   	if (cnt < 2) { if (check(pos, last, a)) a[pos] = last, preBackt(pos+1, a, cnt+1, last, cur + (char)(last-1+'a')), a[pos] = 0; }
   	for (int next = 1; next <= 3; next++) if (next != last) {
   		if (check(pos, next, a)) a[pos] = next, preBackt(pos+1, a, 1, next, cur + (char)(next-1+'a')), a[pos] = 0;
   	}
}


void solve() {
	cin >> v >> k >> s; n = s.size();
	if (n >= 27) { printf("0\n"); return; }
	ans = 0;
	if (n <= 15) {
		//cout << (char)(v - 1 + 'a') << endl;
		ff(i, 0, S[n].size()-1) {
			string cur = S[n][i]; int cnt = 0; bool ok = 1;
			ff(j, 0, n-1) {
				if (cur[j] != s[j]) ++cnt;
				if (cur[j] > v - 1 + 'a') { ok = 0; break; }
			}
			if (!ok) continue;
			//cout << cur << ' ' << cnt << endl;
			if (cnt <= k) ++ans;
		}
		printf("%d\n", ans);
		return;
	}
	s = '~' + s;
	ff(i, 1, n) str[i] = (s[i] - 'a' + 1);
    backt(1, bt, 3, 0, 0);
    printf("%d\n", ans);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    for (n = 1; n <= 15; ++n) preBackt(1, bt, 3, 0, "");
    int t; cin >> t;
    while(t--) solve();
}