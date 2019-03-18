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
const int N = 100010, mod = (int)1e9 + 7, INF = 1e9;

int n;
ii a[N];
ll ans;

double angle(ii a) {
	double r = atan2(a.y, a.x);
	return (r < 0) ? r + 2 * pi : r;
}

bool cmp(ii a, ii b) { return angle(a) < angle(b); }

bool same_half(ii a, ii b) {
	double A = angle(a), B = angle(b);
	if (A < pi) return A <= B && B <= A + pi;
	else return ( (A <= B && B <= 2 * pi) || (0 <= B && B <= A - pi) ); 
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n; ff(i, 0, n-1) cin >> a[i].x >> a[i].y;
	sort(a, a + n, cmp);
	ans = 1ll * n * (n-1) * (n-2) / 6;

	int j = 1;
	ff(i, 0, n-1) {
		if (i == j) j = (j+1) % n;
		while(j != i && same_half(a[i], a[j])) j = (j+1) % n;
		j = (j-1+n) % n;
		int m = (j - i + n) % n;
		ans -= 1ll * m * (m-1) / 2;
	}
	cout << ans << endl;
}