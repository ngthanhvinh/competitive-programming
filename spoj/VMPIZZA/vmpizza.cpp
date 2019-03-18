#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const ll INF = 1e18;
#define t first
#define fi second.first
#define se second.second
int n, cost;
ll t[N], a[N], b[N];
ll T[N], A[N], B[N];
ll f[N];
typedef pair <ll, ll> ii;
typedef pair <ll, ii> pizza;
pizza p[N];

struct line {
    ll a; ll b;
    line(ll _a, ll _b) { a = _a; b = _b; }
};

bool bad(line l1, line l2, line l3) { return (l1.b - l3.b) * (l2.a - l1.a) < (l3.a - l1.a) * (l1.b - l2.b); }
vector <line> L;
#define l1 L[L.size()-2]
#define l2 L[L.size()-1]
void add(ll a, ll b) {
    line l3 = line(a, b); while(L.size() >= 2 && bad(l1, l2, l3)) L.pop_back();
    L.push_back(l3);
}

int cur;

ll get(ll x) {
    if (cur >= L.size()) cur = L.size()-1;
    while(cur < L.size()-1 && L[cur+1].a * x + L[cur+1].b < L[cur].a * x + L[cur].b) ++cur;
    return L[cur].a * x + L[cur].b;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> cost;
    for (int i = 1; i <= n; i++) cin >> p[i].t >> p[i].fi >> p[i].se;
    sort(p + 1, p + n + 1);
    for (int i = 1; i <= n; i++) {
        t[i] = p[i].t, a[i] = p[i].fi, b[i] = p[i].se;
        T[i] = T[i-1] + t[i] * b[i];
        A[i] = A[i-1] + a[i];
        B[i] = B[i-1] + b[i];
    }
    add(0, 0);
    for (int i = 1; i <= n; i++) {
        f[i] = (A[i] + T[i] - t[i] * B[i] - cost) - get(t[i]);
        add(-B[i], -(f[i] - A[i] - T[i]));
        //cout << i << ' ' << f[i] << endl;
    }
    cout << f[n] << endl;
}
