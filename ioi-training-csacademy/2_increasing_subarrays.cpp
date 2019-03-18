#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n, a[N];
long long m;
long long sum[N];
long long ans;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i], sum[i] = sum[i - 1] + a[i];

    deque< pair<int,int> > dq;
    // (pos, num)

    long long cur = 0;
    int ptr = n;
    for (int i = n; i >= 1; --i) {
        int cnt = 1;
        while(!dq.empty() && a[i] >= a[dq.back().first]) {
            int pos = dq.back().first, num = dq.back().second;
            cur -= 1LL * num * a[pos] - sum[pos + num - 1] + sum[pos - 1];
            cnt += num;
            dq.pop_back();
        }
        dq.push_back(make_pair(i, cnt));
        cur += 1LL * cnt * a[i] - sum[i + cnt - 1] + sum[i - 1];

        while(ptr > i && cur > m) {
            if (dq.front().first == ptr) { --ptr; dq.pop_front(); continue; }
            cur -= a[dq.front().first] - a[ptr];
            --dq.front().second;
            --ptr;
        }

        ans += ptr - i + 1;
    }

    printf("%lld\n", ans);
}
