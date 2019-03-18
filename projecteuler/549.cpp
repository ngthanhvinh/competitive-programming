#include <bits/stdc++.h>
using namespace std;

const int N = 100000001;
int n, Div[N];
int f[N];

void sieve() {
	Div[0] = Div[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!Div[i]) for (int j = i; j < N; j += i) Div[j] = i;
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	sieve();
	cin >> n; f[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (Div[i] == i) { f[i] = i; continue; }
		int tmp = i, ans = 0;
		while(tmp != 1) {
			int x = Div[tmp];
			int cur = 1, cnt = 0;
			while(tmp % x == 0) {
				//cout << tmp << "\n";
				tmp /= x; cur *= x; cnt++;
			}
			if (cur < i) ans = max(f[cur], ans);
			else {
				//cout << "x " << x << "\n";
				int l = 1, r = 1e9;
				while(l != r) {
					int mid = ((l + r) >> 1);
					int Cur = 1; long long ans = 0LL;
					//cout << "mid " << mid << "\n";
					while(Cur <= mid) {
						if (1LL * Cur * x > mid) break;
						Cur *= x; ans += mid / Cur;
						//cout << Cur << ' ' << mid / Cur << "\n";
					} 
					//cout << "search " << mid << ' ' << ans << "\n";
					if (ans >= cnt) r = mid;
					else l = mid + 1;
				}
				ans = l;
			}
		} 
		f[i] = ans;
		//cout << i << ' ' << f[i] << "\n";
	}
	//cout << f[30] << "\n";
	long long res = 0LL;
	for (int i = 2; i <= n; i++) res += f[i]; 
	cout << res << "\n";
}