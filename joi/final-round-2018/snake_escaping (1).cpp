// O(L * 3^L + Q)
#include <bits/stdc++.h>
using namespace std;

int L, Q;
string S;
int pw[18], MAX;
int dp[50000005];

int main() {
    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> L >> Q;
    cin >> S;

    pw[0] = 1; for (int i = 1; i <= L; ++i) pw[i] = 3 * pw[i - 1];
    MAX = pw[L];

    for (int mask2 = 0; mask2 < (1 << L); ++mask2) {
        int mask3 = 0;
        for (int i = L - 1; i >= 0; --i) mask3 = 3 * mask3 + (mask2 >> i & 1);
        dp[mask3] = S[mask2] - '0';
    }
    
    for (int i = 0; i < L; ++i) {
        for (int mask = 0; mask < MAX; ++mask) {
            int bit = (mask / pw[i]) % 3;
            if (bit == 2) {
                dp[mask] += dp[mask - pw[i]];
                dp[mask] += dp[mask - 2 * pw[i]];
            }
        }
    }

    while(Q--) {
        string query; cin >> query;
        int mask = 0;
        for (int i = 0; i < L; ++i) {
            int cur = (query[i] == '?') ? 2 : (query[i] - '0');
            mask = 3 * mask + cur;
        }
        printf("%d\n", dp[mask]);
    }
}