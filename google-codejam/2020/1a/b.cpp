#include <bits/stdc++.h>
using namespace std;

long long C[505][505];

void calc() {
    for (int i = 0; i < 505; ++i) C[i][0] = 1;
    for (int i = 1; i < 505; ++i) {
        for (int j = 1; j <= i; ++j) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
}

void solve() {
    long long n; cin >> n;
    if (n <= 500) {
        for (int i = 1; i <= n; ++i) {
            cout << i << ' ' << 1 << endl;
        }
        return;
    }

    int good_nbits = -1;
    int good_more = -1;
    long long good_rem = -1;

    for (int nbits = 0; nbits <= 40; ++nbits) {
        for (int more = nbits; more <= 500; ++more) {
            long long rem = n + nbits - more;
            if (rem < 0) continue;
            if (more <= 40 && rem >= (1LL << more)) continue;
            if (__builtin_popcountll(rem) == nbits) {
                int total_steps = more;
                for (int i = 0; i < 31; ++i) {
                    if (rem >> i & 1) {
                        total_steps += i + 1;
                    }
                }
                if (total_steps <= 500) {
                    good_more = more;
                    good_nbits = nbits;
                    good_rem = rem;
                    break;
                }
            }
        }
    }

    // printf("good_more=%d good_nbits=%d good_rem=%lld\n", good_more, good_nbits, good_rem);

    long long sum = 0;
    bool where = 0;
    for (int i = 0; i < good_more; ++i) {
        if (i <= 40 && (good_rem >> i & 1)) {
            if (!where) {
                for (int j = 0; j <= i; ++j) {
                    cout << i+1 << ' ' << j+1 << endl;
                    sum += C[i][j];
                }
            } else {
                for (int j = i; j >= 0; --j) {
                    cout << i+1 << ' ' << j+1 << endl;
                    sum += C[i][j];
                }
            }
            where ^= 1;
        }
        else {
            if (!where) cout << i+1 << ' ' << 1 << endl, sum += C[i][0];
            else cout << i+1 << ' ' << i+1 << endl, sum += C[i][i];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    calc();
    int ntest; cin >> ntest;
    for (int itest = 1; itest <= ntest; ++itest) {
        cout << "Case #" << itest << ":\n";
        solve();
    }
}