//Solution by Zhusupov Nurlan
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef map<string , int> MSI;
typedef vector<int> VI;
typedef pair<int, int> PII;

#define endl \n
#define pb(x) push_back(x)
#define sqr(x) ((x) * (x))
#define F first
#define S second
#define SZ(t) ((int) t.size())
#define base LL(1e9 + 7)
#define fname ""
#define sz 2550
#define EPS (1e-8)
#define INF ((int)1e9 + 9)
#define mp make_pair
#define left lbjhewq

int n, m, a[sz][sz], up[sz][sz], down[sz][sz], left[sz][sz], dp[sz];
char x;
int u, v;
int H = 1e9, W = 1e9;

int main()
{
  freopen("bomb.in","r",stdin);
  freopen("bomb.out","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    H = n, W = m;
    dp[0] = INF;
    for(int j = 1; j <= m; ++j)
        dp[j] = INF;
    for (int i = 2; i <= n + 1; i++) {
      for (int j = 2; j <= m + 1; j++) {
        cin >> x;
        a[i][j] = x - '0';
      }
    }
    n += 2; m += 2;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {

        if (a[i][j] == 0 && a[i - 1][j] == 1)
          H = min(H, up[i - 1][j]);
        if (a[i][j] == 1) up[i][j] = up[i - 1][j] + 1;

        if (a[i][j] == 0 && a[i][j - 1] == 1)
          W = min(W, left[i][j - 1]);
        if (a[i][j] == 1) left[i][j] = left[i][j - 1] + 1;
      }
    }
    for(int i = n; i >= 1; --i)
      for(int j = 1; j <= m; ++j)
        if(a[i][j] == 1)
            down[i][j] = down[i + 1][j] + 1;

    for(int i = 1; i <= n; ++i)
    {
      for(int j = 1; j <= m; ++j)
         if(a[i - 1][j] == 0 && a[i][j - 1] == 0 && a[i][j] == 1)
         {
            int len = 1;
            int mn = down[i][j];
            while(a[i][j + len - 1] == 1)
            {
              dp[len] = min(dp[len], mn);
              
              dp[len - 1] = min(dp[len - 1], dp[len]);
              len++;
              if(len > W) break;
              mn = min(mn, down[i][j + len - 1]);
            }
          }
      for(int j = m; j >= 1; --j)
        if(a[i - 1][j] == 0 && a[i][j + 1] == 0 && a[i][j] == 1)
        {
          int len = 1;
          int mn = down[i][j];
          while(a[i][j - len + 1] == 1)
          {
            dp[len] = min(dp[len], mn);
            
            dp[len - 1] = min(dp[len - 1], dp[len]);
            len++;
            if(len > W) break;
            mn = min(mn, down[i][j - len + 1]);
          }
        }
    }
    for(int i = n; i >= 1; --i)
    {
      for(int j = 1; j <= m; ++j)
      {
        if(a[i + 1][j] == 0 && a[i][j - 1] == 0 && a[i][j] == 1)
        {
          int len = 1;
          int mn = up[i][j];
          while(a[i][j + len - 1] == 1)
          {
            dp[len] = min(dp[len], mn);
            dp[len - 1] = min(dp[len - 1], dp[len]);
            len++;
            if(len > W) break;
            mn = min(mn, up[i][j + len - 1]);
          }
        }
      }
      for(int j = m; j >= 1; --j)
        if(a[i + 1][j] == 0 && a[i][j + 1] == 0 && a[i][j] == 1)
        {
          int len = 1;
          int mn = up[i][j];
          while(a[i][j - len + 1] == 1)
          {
            dp[len] = min(dp[len], mn);
            dp[len - 1] = min(dp[len - 1], dp[len]);
            len++;
            if(len > W) break;
            mn = min(mn, up[i][j - len + 1]);
          }
        }
    }
    for(int len = 1; len <= W; ++len)
    {
      if(dp[len] == INF) continue;
      int cur = min(dp[len], H);
      if(cur * len > u * v)
        u = cur, v = len;
    }
    cout << u * v << "\n";
}
