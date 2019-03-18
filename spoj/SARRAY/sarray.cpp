#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200010;
#define x first
#define y second
typedef pair <int, int> ii;
typedef pair <ii, int> II;

int n, cnt;
string s;
int suf[N][18];
int pos[N];

void build() {
	ii a[N]; for (int i = 1; i <= n; i++) a[i] = ii(s[i], i); sort(a+1, a+n+1);
	cnt = 0; for (int i = 1; i <= n; i++) suf[a[i].y][0] = ((a[i].x == a[i-1].x) ? suf[a[i-1].y][0] : ++cnt);
	II A[N]; 
	for (int i = 0; i < 17; i++) {
		cnt = 0;
		for (int j = 1; j <= n; j++) 
			if (j + (1 << i) <= n) A[j] = II(ii(suf[j][i], suf[j + (1<<i)][i]), j); 
			else A[j] = II(ii(suf[j][i], 0), j);
		sort(A + 1, A + n + 1);
		for (int j = 1; j <= n; j++) suf[A[j].y][i+1] = ((A[j].x == A[j-1].x) ? suf[A[j-1].y][i+1] : ++cnt);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> s; s = '`' + s; n = s.size()-1; 
	build();
	for (int i = 1; i <= n; i++) pos[suf[i][17]] = i-1;
	for (int i = 1; i <= n; i++) cout << pos[i] << endl;
}