#include <bits/stdc++.h>
using namespace std;
typedef pair <int, int> ii;
typedef vector <int> vi;

#define ll long long
#define ff(i, a, b) for (int i = (int)(a); i <= (int)(b); i++)
#define fod(i, a, b) for (int i = (int)(a); i >= (int)(b); i--)
#define pb push_back
#define x first
#define y second
#define pi acos(-1)
const int N = 1510, mod = (int)1e9 + 7, INF = 1e9;

int n, X[N], Y[N];
ll res;

double angle(ii a) {
	double r = atan2(a.y, a.x);
	return (r < 0) ? r + 2 * pi : r;
}

bool same_half(double A, double B) {
	if (A < pi) return A <= B && B <= A + pi;
	else return ( (A <= B && B <= 2 * pi) || (0 <= B && B <= A - pi) ); 
}

ll solve(int pos) {
	vector <double> a;
	int m = 0; ff(i, 1, n) if (i != pos) a.pb(angle(ii(X[i] - X[pos], Y[i] - Y[pos]))), m++;
	int j = 1;
	
	sort(a.begin(), a.end());
	ll ans = 1ll * m * (m-1) * (m-2) / 6;
	ff(i, 0, m-1) {
		if (i == j) j = (j+1) % m;
		while(j != i && same_half(a[i], a[j])) j = (j + 1) % m;
		j = (j - 1 + m) % m;
		int cnt = (j - i + m) % m;
		ans -= 1ll * cnt * (cnt-1) / 2;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	double start = clock();
	cin >> n; ff(i, 1, n) cin >> X[i] >> Y[i];
	res = 1ll * n * (n-1) * (n-2) * (n-3) / 24;
	ll tricount = 0;
	ff(i, 1, n) tricount += solve(i);
	ll num = 1ll * n * (n-1) * (n-2) / 6;
	printf("%.6lf\n", (double)((res - tricount) * 2 + tricount) / num + 3.0);
}