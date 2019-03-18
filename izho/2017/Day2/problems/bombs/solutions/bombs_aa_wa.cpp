#include<bits/stdc++.h>

using namespace std;

const int N = 2550;

int ans;
int x[N];
int n, m, a[N][N];
int s[N][N], H, W;
int f[N][N], bad[N][N];
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
	int sz = h * w;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			bad[i][j] = 0, f[i][j] = 0;
	int nn = n + 2, mm = m + 2;
	for(int i = 1; i + h < nn; ++i)
		for(int j = 1; j + w < mm; ++j)
			if(s[i + h - 1][j + w - 1] - s[i + h - 1][j - 1] - s[i - 1][j + w - 1] + s[i - 1][j - 1] == sz)
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
			R = w;
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
			R = h;
	}
	return L;
}

inline void read(int &x)
{
	char c = '0'; c--;           
	x = 0;
	while((c < '0' || c > '9')) c = getchar();
	while((c >= '0' && c <= '9')) x = x * 10 + c - '0', c = getchar();
}

int main()
{
	freopen("bomb.in", "r", stdin);
	freopen("bomb.out", "w", stdout);

	read(n);
	read(m);

	for(int i = 2; i <= n + 1; ++i)
	{                 	
		scanf("%s", S);
		for(int j = 2; j <= m + 1; ++j)
		{
			a[i][j] = S[j - 2] - '0';
		}
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
	if(H <= W)
	{
		int cnt = 0;
		for(int i = 1; i <= H;)
		{
			int x = getw(i);
			int y = geth(x);
			cnt++;
			x *= y;
			if(x > ans)
				ans = x;
			i = max(i + 1, y + 1);
		}
		assert(cnt <= 10);
	}
	else
	{
		int cnt = 0;
		for(int i = 1; i <= W;)
		{
			cnt++;
			int x = geth(i);
			int y = getw(x);
			x *= y;
			if(x > ans)
				ans = x;
			i = max(i + 1, y + 1);
		}

		assert(cnt <= 10);
	}
	ans = max(ans, max(W, H));
	printf("%d\n", ans);
		
	return 0;
}