#include <bits/stdc++.h>
using namespace std;
#define ff(i, a, b) for (int i = a; i <= b; i++)
#define rep(i, n) for (int i = 0; i < n; i++)
#define fod(i, a, b) for (int i = a; i >= b; i--)
#define fi first
#define se second

typedef pair<int, int> ii;
const int N = 300010;

int n, q;
ii a[N], p[N];
long long f[N];
bool check[N];
int cur = 0;
int Max = 0;

struct line {
    long long a; long long b;
    //line() { a = 0; b = 0; }
};

bool bad(line l1, line l2, line l3) { return (l1.b - l3.b) * (l2.a - l1.a) < (l3.a - l1.a) * (l1.b - l2.b); }
vector <line> l;
#define l1 l[l.size() - 2]
#define l2 l[l.size() - 1]

void add(long long a, long long b) {
    //cout << "size: " << l.size() << "\n";
    //cout << "add: " << a << ' ' << b << "\n";
    line l3; l3.a = a; l3.b = b;
    while(l.size() >= 2 && bad(l1, l2, l3)) l.pop_back();
    l.push_back(l3);
    //cout << "line:\n";
    //ff(i, 0, l.size()-1) cout << l[i].a << ' ' << l[i].b << "\n";
    //cout << "\n";
}

long long query(long long x) {
    if (cur >= l.size()) cur = l.size() - 1;
    while(cur < l.size() - 1 && l[cur+1].a * x + l[cur+1].b <= l[cur].a * x + l[cur].b) cur++;
    return l[cur].a * x + l[cur].b;
}

int main() {
    //freopen("input.txt", "r", stdin);
    scanf("%d", &n); ff(i, 1, n) scanf("%d%d", &a[i].fi, &a[i].se);
    sort(a + 1, a + n + 1);
    fod(i, n, 1) {
        if (a[i].se <= Max) continue;
        check[i] = 1;
        Max = a[i].se;
    }
    ff(i, 1, n) if (check[i]) p[++cur] = a[i];
    ff(i, 1, cur) a[i] = p[i];
    n = cur; cur = 0;
    //ff(i, 1, n) printf("%d %d\n", a[i].fi, a[i].se);
    add(a[1].se, f[0]);
    ff(i, 1, n) {
        // f(i) = f(j - 1) + xi * yj -> line: y = ax + b (a = yj, b - f(j - 1)) with j <= i
        f[i] = query(a[i].fi);
        //cout << i << ' ' << f[i] << endl;
        if (i < n) add(a[i+1].se, f[i]);
    }
    printf("%lld\n", f[n]);
}
