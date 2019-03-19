#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int N = 1000010;

int n;
string Johnny, Mary;
int a[N], t[N];
long long ans;
int ptr[26];
vector<int> vec[26];

void upd(int x) { for (; x <= n; x += x & -x) t[x]++; }
int get(int x) { int res = 0; for (; x > 0; x -= x & -x) res += t[x]; return res; }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> Johnny >> Mary;
    memset(ptr, -1, sizeof ptr);
    for (int i = 0; i < n; ++i) vec[Mary[i]-'A'].push_back(i);
    for (int i = 0; i < n; ++i) a[i + 1] = vec[Johnny[i]-'A'][++ptr[Johnny[i]-'A']] + 1;

    for (int i = n; i >= 1; --i) {
        ans += get(a[i]);
        upd(a[i]);
    }

    cout << ans << endl;
}
