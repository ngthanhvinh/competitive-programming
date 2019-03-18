// O(2^7 * (3^13 + Q))
#include <bits/stdc++.h>
using namespace std;

const int MAXQ = 1000005;

int L, L1, L2, Q;
string S, q;
int res[MAXQ];
int qmask1[MAXQ], qmask2[MAXQ];
bool ischild[130][2190]; // [2^7][3^7]
int pw[14];
int dp[1594323];
int last[1594323];

int curmask; // for backtracking
void brute(int pos, int curchild) {
    if (pos == L2) {
        ischild[curchild][curmask] = true; return;
    }
    int cur = (curmask / pw[pos]) % 3;
    if (cur == 2) {
        brute(pos + 1, curchild);
        brute(pos + 1, curchild + (1 << pos));
    } else {
        brute(pos + 1, curchild + cur * (1 << pos));
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> L >> Q;
    cin >> S;

    L1 = min(13, L);
    L2 = L - L1;
    pw[0] = 1; for (int i = 1; i <= L1; ++i) pw[i] = 3 * pw[i - 1];

    for (int i = 0; i < Q; ++i) {
        cin >> q;
        long long qmask = 0;
        for (int j = 0; j < L; ++j) {
            int cur = (q[j] == '?') ? 2 : (q[j] - '0');
            qmask = qmask * 3 + cur;
        }
        qmask1[i] = qmask % pw[L1];
        qmask2[i] = qmask / pw[L1];
    }

    // ischild
    for (int mask = 0; mask < pw[L2]; ++mask) {
        curmask = mask;
        brute(0, 0);
    }

    // prepare
    for (int mask = 0; mask < pw[L1]; ++mask) {
        last[mask] = -1;
        for (int i = 0; i < L1; ++i) {
            int cur = (mask / pw[i]) % 3;
            if (cur == 2) { last[mask] = i; break; }
        }
    }

    // solve
    for (int mask2 = 0; mask2 < (1 << L2); ++mask2) {
        for (int i = 0; i < pw[L1]; ++i) dp[i] = 0;
        for (int mask = 0; mask < (1 << L1); ++mask) {
            int to = 0;
            for (int i = L1 - 1; i >= 0; --i) to = 3 * to + (mask >> i & 1);
            dp[to] += S[mask | (mask2 << L1)] - '0';
        }
        
        for (int mask = 0; mask < pw[L1]; ++mask) {
            if (last[mask] != -1) { // bit(mask, lst) = 2
                dp[mask] = dp[mask - pw[last[mask]]] + dp[mask - pw[last[mask]] - pw[last[mask]]];
            }
        }

        for (int i = 0; i < Q; ++i) {
            if (ischild[mask2][qmask2[i]]) {
                res[i] += dp[qmask1[i]];
            }
        }
    }

    for (int i = 0; i < Q; ++i) printf("%d\n", res[i]);
}