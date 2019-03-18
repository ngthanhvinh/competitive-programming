#include <bits/stdc++.h>
using namespace std;

const int N = 100005, S = 325;

int n, q, a[N], id[N];
int cnt[N];
vector<int> Z;
vector<int> buf;
vector<int> val[N];
long long f[S][N];

int get(int v, int l, int r) {
    int R = upper_bound(val[v].begin(), val[v].end(), r) - val[v].begin();
    int L = lower_bound(val[v].begin(), val[v].end(), l) - val[v].begin();
    return R - L;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q;
	for (int i = 0; i < n; ++i) cin >> a[i], Z.push_back(a[i]);

	sort(Z.begin(), Z.end());
	Z.resize(distance(Z.begin(), unique(Z.begin(), Z.end())));

    for (int i = 0; i < n; ++i) {
        id[i] = lower_bound(Z.begin(), Z.end(), a[i]) - Z.begin() + 1;
        val[id[i]].push_back(i);
    }

	for (int bl = 0; bl <= (n - 1) / S; ++bl) {
        for (int i = bl * S; i < n; ++i) {
            cnt[id[i]]++;
            f[bl][i] = max(f[bl][i - 1], 1LL * cnt[id[i]] * a[i]);
        }
        for (int i = 0; i <= n; ++i) cnt[i] = 0;
    }

    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r;
        --l; --r;
        long long res = f[l / S + 1][r];
        
        for (int i = l; i <= min(r, (l / S + 1) * S - 1); ++i) {
            res = max(res, 1LL * get(id[i], l, r) * a[i]);
        }

        printf("%lld\n", res);
    }
}