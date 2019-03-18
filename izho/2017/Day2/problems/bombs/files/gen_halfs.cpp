#include<bits/stdc++.h>
#include "testlib.h"
using namespace std;

int n, m, len1, len2, cx, cy, d, a[6005][6005];

typedef long long ll;
#define mp make_pair
#define f first
#define s second
#define pii pair<int, int>
#define pb push_back

const int magic = 3000;

int fix, sex, fiy, sey;
int x, y;
int res[magic][magic];


int main(int argc, char* argv[])
{
	registerGen(argc, argv, 1);

	x = atoi(argv[1]);
	y = atoi(argv[2]);	

	int sx = magic, sy = magic;
	int shift = 2;

	for(int cnt = 1; cnt <= x; ++cnt)
	{
		for(int i = 1; i <= x; ++i)
			for(int j = 1; j <= y; ++j)
				a[i + sx - 1][j + sy - 1] = 1;
		sx += x;
		if(rnd.next(0, 1))
		{
			sy -= shift;
	   	 	if(cnt != x)
			for(int i = 1; i <= shift - 1; ++i)
			{
				for(int j = i; j <= shift; ++j)
					a[sx - i][sy + j] = 1;
			}
		}
		else
		{
			sy += shift;
			if(cnt != x)
			for(int i = 1; i <= shift - 1; ++i)
			{
				for(int j = i; j <= shift - 1; ++j)
					a[sx - i][sy + y - j - 1] = 1;
			}
		}
		shift++;
	}
	for(int i = 1; i <= magic + magic; i++)
		for(int j = 1; j <= magic + magic; ++j)
			if(a[i][j])
			{
				if(!fix) fix = i;
				sex = i;
			}
	for(int j = 1; j <= magic + magic; ++j)
		for(int i = 1; i <= magic + magic; ++i)
			if(a[i][j])
			{
				if(!fiy) fiy = j;
				sey = j;
			}
	int n = 2500, m = 2500;

	for(int i = fix; i <= sex; i++){
		for(int j = fiy; j <= sey; j++){
			res[i - fix + 1][j - fiy + 1] = a[i][j];
		}
	}     

	for(int i = fix; i <= sex; i++){
		for(int j = fiy; j <= sey; j++){
			res[n - (i - fix)][n - (j - fiy)] = a[i][j];
		}
	}
	for(int i = n / 2; i <= n; ++i)
		for(int j = 1; j <= n / 2; ++j)
			res[i][j] |= 1;
	for(int i = 1; i <= n/ 2; ++i)
		for(int j = n / 2; j <= n; ++j)
			res[i][j] |= 1;

  	printf("%d %d\n", n, m);
  	for (int i = 1; i <= n; i++) {
  		for (int j = 1; j <= m; j++) { 
  			printf("%d", res[i][j]);
  		}
  		printf("\n");
  	
  	}


}