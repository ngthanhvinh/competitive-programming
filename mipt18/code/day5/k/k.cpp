#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1e5 + 5;

int N, K;
string S;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> K;
	cin >> S;
	sort(S.begin(), S.end());
	int largest = (N + K - 1) / K;
	int num = N % K;
	if (num == 0) num = K;
	int cur = 0;
	string str;
	for (int i = 0; i < largest; ++i) {
		int cnt = 1;
		str.append(1, S[cur++]);
		for (int j = 1; j < num; ++j) {
			if (S[cur] == str.back()) ++cnt;
			else {
				str.back() = S[cur];
				cnt = 1;
			}
			++cur;
		}
		num = cnt;
	}
	cout << str << endl;
}
