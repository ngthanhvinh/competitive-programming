/**
 *    author:  tourist
 *    created: 31.03.2018 11:41:48       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    cout << "Case #" << qq << ": ";
    int h, w;
    cin >> h >> w;
    vector< vector<int> > a(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
      string foo;
      cin >> foo;
      for (int j = 0; j < w; j++) {
        a[i][j] = (foo[j] == 'B');
      }
    }
    auto contains = [&](const vector< vector<int> > &pattern) {
      int hp = (int) pattern.size();
      int wp = (int) pattern[0].size();
      for (int i = 0; i <= h - hp; i++) {
        for (int j = 0; j <= w - wp; j++) {
          int ok = 1;
          for (int x = 0; x < hp; x++) {
            for (int y = 0; y < wp; y++) {
              ok &= (a[i + x][j + y] == pattern[x][y]);
            }
          }
          if (ok) {
            return true;
          }
        }
      }
      return false;
    };
    vector< vector<int> > good(h, vector<int>(w));
    vector< vector<int> > was(h, vector<int>(w));
    vector< pair<int,int> > que;
    auto max_comp = [&]() {
      for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
          was[i][j] = 0;
        }
      }
      int ans = 0;
      for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
          if (was[i][j] || !good[i][j]) {
            continue;
          }
          que.assign(1, make_pair(i, j));
          was[i][j] = 1;
          for (int b = 0; b < (int) que.size(); b++) {
            for (int dx = -1; dx <= 1; dx++) {
              for (int dy = -1; dy <= 1; dy++) {
                if (dx * dx + dy * dy == 1) {
                  int xk = que[b].first + dx;
                  int yk = que[b].second + dy;
                  if (xk >= 0 && yk >= 0 && xk < h && yk < w) {
                    if (!was[xk][yk] && good[xk][yk]) {
                      was[xk][yk] = 1;
                      que.emplace_back(xk, yk);
                    }
                  }
                }
              }
            }
          }
          ans = max(ans, (int) que.size());
        }
      }
      return ans;
    };
    int ans = 0;
    for (int bx = 1; bx <= h; bx++) {
      for (int by = 1; by <= w; by++) {
        for (int t = 0; t < (1 << 4); t++) {
          vector< vector<int> > pattern(bx < h ? 2 : 1, vector<int>(by < w ? 2 : 1));
          for (int i = 0; i < (int) pattern.size(); i++) {
            for (int j = 0; j < (int) pattern[i].size(); j++) {
              pattern[i][j] = ((t >> (((i >= 1) << 1) + (j >= 1))) & 1);
            }
          }
          if (!contains(pattern)) {
            continue;
          }
          for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
              int must = pattern[i >= bx][j >= by];
              good[i][j] = (a[i][j] == must);
            }
          }
          ans = max(ans, max_comp());
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}