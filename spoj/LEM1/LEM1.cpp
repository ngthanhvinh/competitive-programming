#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ff(i, a, b) for(int i = a; i <= b; i++)
#define fo(i, a, b) for(int i = a; i < b; i++)
#define fod(i, a, b) for(int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

const int INF = 1e9, N = 10010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, r[N]; double lo = 0.0, hi = 0.0;

bool f(double R) {
	double res = 0.0;
	ff(i, 1, n) {
		int R1 = r[i], R2 = r[i % n + 1];
		double a = (double)R + R1, b = (double)R + R2, c = (double)R1 + R2;
		double angle = (double)acos((double)(a * a + b * b - c * c) / (2 * a * b));
		res += angle;
	}
	if (res < 2 * M_PI) return 0;
	else if (res > 2 * M_PI) return 1;
	else return 0;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	//freopen("input.txt","r",stdin);
	cin >> n; ff(i, 1, n) { cin >> r[i]; hi += r[i]; }
	for(int i = 0; i < 100; ++i) {
		double mid = (double)(lo + hi) / 2;
		if (f(mid)) lo = (double)mid;
		else hi = mid;
	}
	printf("%.3lf\n", lo);
}