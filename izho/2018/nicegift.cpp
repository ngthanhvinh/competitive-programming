#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int n, k;
long long a[N];
long long sum;
long long mx;
priority_queue < pair<long long, int> > pq;

vector < vector <int> > vres;
vector <long long> vX;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i], sum += a[i]; mx = max(mx, a[i]);
    }
    if (sum % k != 0 || mx > sum / k) return printf("-1\n"), 0;

    for (int i = 1; i <= n; ++i) {
        pq.push(make_pair(a[i], i));
    }    

    long long average = sum / k;

    while(!pq.empty()) {
        int taken = 0;
        vector<int> cur;
        while(!pq.empty() && taken < k) {
            ++taken;
            int pos = pq.top().second; pq.pop();
            cur.push_back(pos);
        }
        //assert(taken == k);

        long long last = 0;
        if (!pq.empty()) last = pq.top().first;
        
        long long X = min(average - last, a[cur.back()]);

        vX.push_back(X);
        vres.push_back(cur);
        average -= X;

        for (int &pos : cur) {
            a[pos] -= X;
            if (a[pos] > 0) pq.push(make_pair(a[pos], pos));
        }
    }

    printf("%d\n", vres.size());
    for (int i = 0; i < vres.size(); ++i) {
        printf("%lld ", vX[i]);
        for (int &j : vres[i]) printf("%d ", j); printf("\n");
    }
}