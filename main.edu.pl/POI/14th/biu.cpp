#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n, m;
set<int> s;
vector<int> G[N];
bool del[N];
vector<int> ans;

bool found(int u, int v) {
  int pos = lower_bound(G[u].begin(), G[u].end(), v) - G[u].begin();
  if (pos == G[u].size()) return false;
  return G[u][pos] == v;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cin >> n >> m;
  while(m--) {
    int u, v; cin >> u >> v;
    G[u].push_back(v); G[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) s.insert(i);
  for (int i = 1; i <= n; ++i) {
    sort(G[i].begin(), G[i].end());
  }

  for (int i = 1; i <= n; ++i) {
    if (del[i]) continue;
    queue<int> q;
    q.push(i);
    s.erase(i);
    int cnt = 0;

    while(!q.empty()) {
      int u = q.front(); q.pop(); del[u] = 1; ++cnt;
      vector<int> cur;
      for (set<int>::iterator iter = s.begin(); iter != s.end(); ++iter) {
        int v = (*iter);
        if (found(u, v)) continue;
        cur.push_back(v);
        q.push(v);
      }
      for (int v : cur) s.erase(v);
    } 
    ans.push_back(cnt);
  }

  sort(ans.begin(), ans.end());
  printf("%d\n", ans.size());
  for (int val : ans) printf("%d ", val); printf("\n");
}