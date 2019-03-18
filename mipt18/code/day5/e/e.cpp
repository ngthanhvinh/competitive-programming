#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1e5 + 5;

int N, M;
int nxt[maxn][26];
string S, T;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> S >> T;
	N = S.length(); M = T.length();
	S = '~' + S;
	T = '~' + T;
	for (int i = 0; i < 26; ++i) nxt[N + 1][i] = N + 1;
	for (int i = N; i >= 1; --i) {
		for (int j = 0; j < 26; ++j) nxt[i][j] = nxt[i + 1][j];
		nxt[i][S[i] - 'a'] = i;
	}
	int cur = 1;
	int ans = 1e9;
	for (int i = 0; i < M; ++i) {
		if (cur > N + 1) break;
		ans = min(ans, N + 1 - cur + (cur - 1 - i));
		for (int j = 0; j < T[i + 1] - 'a'; ++j)
			ans = min(ans, nxt[cur][j] - cur + (cur - 1 - i));
		while (cur <= N && S[cur] != T[i + 1]) ++cur;
		++cur; 
	}
	cout << ans << endl;
}