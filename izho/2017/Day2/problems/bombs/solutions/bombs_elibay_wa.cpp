#include<bits/stdc++.h>

using namespace std;

const int N = 2550;
const int inf = 1e9;

int ans;
int x[N];
int n, m, a[N][N];
int s[N][N], H, W;
int f[N][N], bad[N][N];
int dpw[N], dph[N];
char S[N];

inline void press(int i, int j, int h, int w)
{
	bad[i][j]++;
	bad[i + h][j + w]++;
	bad[i + h][j]--;
	bad[i][j + w]--;
}

inline bool can(int h, int w)
{
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			bad[i][j] = 0, f[i][j] = 0;
	for(int i = 1; i + h - 1 <= n; ++i)
		for(int j = 1; j + w - 1 <= m; ++j)
			if(s[i + h - 1][j + w - 1] - s[i + h - 1][j - 1] - s[i - 1][j + w - 1] + s[i - 1][j - 1] == h * w)
				press(i, j, h, w);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
		{
			f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + bad[i][j];
			if(a[i][j] == 1 && f[i][j] <= 0) 
				return false;
		}
	return true;          
}

inline int getw(int h)
{
	int L = 0, R = W + 1;
	while(L + 1 < R)
	{
		int w = (L + R) >> 1;
		if(can(h, w))
			L = w;
		else
		{
			R = w;
		}
	}
	return L;
}

inline int geth(int w)
{
	int L = 0, R = H + 1;
	while(L + 1 < R)
	{
		int h = (L + R) >> 1;
		if(can(h, w))
			L = h;
		else
		{
			R = h;
		}
	}
	return L;
}

int main()
{
	freopen("bomb.in", "r", stdin);
	freopen("bomb.out", "w", stdout);

	scanf("%d%d", &n, &m);

	for(int i = 2; i <= n + 1; ++i)
	{
		scanf("%s\n", S);
		for(int j = 2; j <= m + 1; ++j)
			a[i][j] = S[j - 2] - '0';
	}
	
	n += 2, m += 2;

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
	
	H = n, W = m;

	for(int i = 1; i <= n; ++i)
	{
		int cnt = 0;
		for(int j = 1; j <= m; ++j)
			if(a[i][j] == 1) cnt++;
			else 
			{
				if(cnt) W = min(W, cnt);
				cnt = 0;
			}
	}

	for(int j = 1; j <= m; ++j)
	{
		int cnt = 0;
		for(int i = 1; i <= n; ++i)
			if(a[i][j] == 1) cnt++;
			else
			{
				if(cnt) H = min(H, cnt);
				cnt = 0;
			}
		
	}
	if(0)
	{
		for(int i=1; i<=H;)
		{
			int x=getw(i);
			int y = geth(x);
			ans=max(ans,x*y);
			i=y+1;	
		} 
	}
	else
	{
	int cnt=3e7/(n*m);
	for(int i=H;i>=1&&cnt;--i)
	{
		int x=getw(i);
		ans=max(ans,i*x);
		cnt--;
	}                  
	}
	printf("%d\n", ans);
	
	return 0;
}