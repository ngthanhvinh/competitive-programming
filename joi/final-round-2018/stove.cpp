#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, k, t[N];
int ans;
vector<int> buf;

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", t + i);

    int need = n;
    for (int i = 2; i <= n; ++i) buf.push_back(t[i] - t[i - 1] - 1);
    sort(buf.begin(), buf.end(), greater<int>());

    ans = n;
    while(need > k) {
        --need;
        assert(buf.size() > 0);
        int best = buf.back();
        buf.pop_back();
        ans += best;
    }

    printf("%d\n", ans);
}