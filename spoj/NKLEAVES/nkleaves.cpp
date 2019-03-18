#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int n, k, cur;
int w[N];
long long f[N][11], s[N], t[N];
#define ff(i, a, b) for (int i = a; i <= b; i++)

struct line { long long a; long long b; };
bool bad(line l1, line l2, line l3) { return (l1.b - l3.b) * (l2.a - l1.a) < (l3.a - l1.a) * (l1.b - l2.b); }
vector <line> l;
#define l1 l[l.size() - 2]
#define l2 l[l.size() - 1]

void add(long long a, long long b) {
    //cout << "add: " << a << ' ' << b << "\n";
    line l3; l3.a = a; l3.b = b;
    while(l.size() >= 2 && bad(l1, l2, l3)) l.pop_back();
    l.push_back(l3);
    //cout << "line:\n"; ff(i, 0, l.size()-1) cout << l[i].a << ' ' << l[i].b << "\n";
    //cout << "\n";
}

long long query(long long x) {
    if (cur >= l.size()) cur = l.size() - 1;
    while(cur < l.size() - 1 && l[cur+1].a * x + l[cur+1].b < l[cur].a * x + l[cur].b) cur++;
    return l[cur].a * x + l[cur].b;
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k; ff(i, 1, n) cin >> w[i], s[i] = s[i - 1] + i * w[i], t[i] = t[i - 1] + w[i];

    ff(i, 1, n) ff(j, 0, 10) f[i][j] = 1e13;
    ff(cnt, 1, k) {
        l.clear(); add(0, 0); cur = 0;
        ff(i, 1, n) {
            f[i][cnt] = query(t[i]) + (s[i] - t[i]);
            add(-i, f[i][cnt - 1] - s[i] + (i + 1) * t[i]);
            //cout << i << ' ' << cnt << ' ' << f[i][cnt] << "\n";
        }
    }
    printf("%lld\n", f[n][k]);
}
