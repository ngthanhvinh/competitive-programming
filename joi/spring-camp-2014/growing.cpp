#include <bits/stdc++.h>
using namespace std;

const int N = 300005;

int n;
int a[N];
int t[N];
int l[N];
int r[N];
long long res;
vector<int> z;

void upd(int x) { for (; x > 0; x -= x & -x) t[x]++; }
int get(int x) { int ret = 0; for (; x < N; x += x & -x) ret += t[x]; return ret; }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        z.push_back(a[i]);
    }
    sort(z.begin(), z.end());

    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(z.begin(), z.end(), a[i]) - z.begin() + 1;
    }

    for (int i = 1; i <= n; ++i) {
        l[i] = get(a[i] + 1);
        upd(a[i]);
    }

    memset(t, 0, sizeof t);
    for (int i = n; i >= 1; --i) {
        r[i] = get(a[i] + 1);
        upd(a[i]);
    }

    for (int i = 1; i <= n; ++i) {
        res += min(l[i], r[i]);
    }

    cout << res << endl;
}