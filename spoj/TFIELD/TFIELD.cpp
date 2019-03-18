#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define ff(i, a, b) for(int i = a; i <= b; i++)
#define fo(i, a, b) for(int i = a; i < b; i++)
#define fod(i, a, b) for(int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define x first
#define y second

const int INF = 1e9, N = 1010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;
typedef pair <vii, int> II;

ll area(vector <ii> P) {
	int n = P.size(); ll res = 0;
	fo(i, 0, n) {
		res += 1LL * (P[i].x - P[(i + 1) % n].x) * (P[i].y + P[(i + 1) % n].y);
	}
	return abs(res);
}

bool cmp(II u, II v) { return area(u.first) < area(v.first) || (area(u.first) == area(v.first) && u.second < v.second); }

vector <ii> a[N];
int m, k, c[N], f[N][N];
vector <II> data;
ll S[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> m >> k; data.assign(m, II());
	ff(i, 0, m - 1) {
		int nVertex, c; vii cur;
		cin >> nVertex >> c; data[i].second = c; fo(j, 0, nVertex) { ii val; cin >> val.x >> val.y; cur.pb(val); }
		data[i].first = cur;	 
	}
	sort(data.begin(), data.end(), cmp);
	int n = 0;
	fo(i, 0, data.size()) {
		++n; a[n] = data[i].first; c[n] = data[i].second; S[n] = area(a[n]);
	}
	ff(color, 1, m) {
		ff(i, 1, n) f[color][i] = f[color][i - 1] + (c[i] != color); // number of the land regions which have different color from "color" 
	}
	ll ans = 0;
	ff(i, 0, n - 1) {
		ff(color, 1, m) {
			int l = i, r = n;
			while(l != r) {
				int mid = ((l + r + 1) >> 1);
				if (f[color][mid] - f[color][i] > k) r = mid - 1;
				else l = mid; 
			}
			ans = max(ans, S[l] - S[i]);
		}
	}
	printf("%lld.%d\n", ans / 2, (ans&1) ? 5 : 0);
}