#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector <int> v;
string s[100010];
int sum[100010];

string to_string(int x) {
    string ans = "";
    while(x) ans += (char)(x % 10 + '0'), x /= 10;
    reverse(ans.begin(), ans.end());
    return ans;
}

bool cmp(int a, int b) { return sum[a] < sum[b] || (sum[a] == sum[b] && s[a] < s[b]); }

void solve() {
    v.clear();
    int N, K, T; cin >> T >> N >> K;
    for (int i = 1; i <= N; ++i) sum[i] = sum[i/10] + i%10;
    for (int i = 1; i <= N; ++i) s[i] = to_string(i);
    for (int i = 1; i <= N; ++i) v.push_back(i);
    sort(v.begin(), v.end(), cmp);

    if (T == 1) cout << v[K-1] << endl;
    else cout << lower_bound(v.begin(), v.end(), K, cmp) - v.begin() + 1 << endl;
}

int main() {
    freopen("vo17bach.inp", "r", stdin);
    freopen("vo17bach.ans", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    int nTest; cin >> nTest;
    while(nTest--) {
        solve();
    }
}
