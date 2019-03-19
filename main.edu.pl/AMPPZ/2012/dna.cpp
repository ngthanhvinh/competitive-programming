#include <bits/stdc++.h>
using namespace std;

int n;
string s;
char ch[] = {'A','G','C','T'};
int cnt[26];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> s;
	for (int i = 0; i < n; ++i) {
		cnt[s[i] - 'A']++;
	}
	int mn = 0;
	for (int i = 0; i < 4; ++i) if (cnt[ch[i] - 'A'] < cnt[ch[mn] - 'A']) mn = i;

	cout << cnt[ch[mn]-'A'] << endl;
	for (int i = 0; i < n; ++i) cout << ch[mn]; cout << endl;
}