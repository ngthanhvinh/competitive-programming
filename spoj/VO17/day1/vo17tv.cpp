#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

const int MOD = 1e9 + 9, BASE = 26;
const int MAX = 100010;

int pw[MAX];

int N, K, mx;
string s[51];
vector <int> H[51];

int getHash(int pos, int l, int r) {
    int res = (H[pos][r] - 1ll * H[pos][l - 1] * pw[r - l + 1] % MOD) % MOD;
    if (res < 0) res += MOD;
    return res;
}

map <int, int> cnt;
map <int, bool> ex;

bool check(int x) {
    cnt.clear();
    for (int i = 1; i <= N; ++i) {
        ex.clear();
        for (int j = x; j <= (int)s[i].size(); ++j) {
            int h = getHash(i, j - x + 1, j);
            if (!ex.count(h)) ex[h] = 1, cnt[h]++;
        }
    }

    for (map <int, int> :: iterator it = cnt.begin(); it != cnt.end(); ++it) {
        if (it -> second >= K) return 1;
    }

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> K;
    pw[0] = 1; for (int i = 1; i < MAX; ++i) pw[i] = 1LL * pw[i-1] * BASE % MOD;
    for (int i = 1; i <= N; ++i) {
        cin >> s[i];
        mx = max(mx, (int)s[i].size());
        H[i].assign(s[i].size() + 1, 0);
        for (int j = 1; j <= (int)s[i].size(); ++j) H[i][j] = (1LL * H[i][j-1] * BASE % MOD + s[i][j-1] - 'A') % MOD;
    }

    int l = 0, r = mx;
    while(l != r) {
        int mid = ((l + r + 1) >> 1);
        if (check(mid)) l = mid;
        else r = mid - 1;
    }

    cout << l << endl;
}
