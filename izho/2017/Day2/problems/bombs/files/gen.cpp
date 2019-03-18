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


void doit(int x,int y,int a,int b){
	for(int i = x; i <= x + a - 1; i++){
		for(int j = y; j <= y + b - 1; j++){
			res[i][j] = 1;
		}
	}
}


int main(int argc, char* argv[])
{
	registerGen(argc, argv, 1);
	int n = atoi(argv[1]), m = atoi(argv[2]), x = atoi(argv[3]), y = atoi(argv[4]);
  	doit(1,1,x,y);
  	int shift = rnd.next(2,x - 1);
  	doit(shift, y + 1, x , 1);
  	int xx = rnd.next(shift + 1,x);
  	doit(xx, y + 2,x , y);
  	int yy = rnd.next(y + 3, y + y - 2);
  	doit(xx + x, yy, 1, y);
  	int zz = rnd.next(yy + 1,y + y - 1);
  	doit(xx + x + 1, zz, x, y);


  	printf("%d %d\n", n, m);
  	for (int i = 1; i <= n; i++) {
  		for (int j = 1; j <= m; j++) { 
  			printf("%d", res[i][j]);
  		}
  		printf("\n");
  	}


}