#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int N = 50010;

int n; vector<int> v, ans;
bool check[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; ++i) {
        int x; scanf("%d", &x);
        if (!check[x]) v.push_back(x), check[x] = 1;
        else {
            vector<int>::iterator it = v.end();
            for (int j = v.size()-1; j >= 0; --j) {
                ans.push_back(j+1); --it;
                if (v[j] == x) break;
            }
            v.erase(it);
            ans.pop_back();
        }
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); ++i) printf("%d\n", ans[i]);
}
