#include<bits/stdc++.h>
using namespace std;
const int inf = 1000000000;
char c1[2505][2505],c2[2505][2505];
int n,m,l,r,bolo;
int lf[2505][2505],rg[2505][ 2505],zr[2505];
pair<int, int> ans;

int main(){
  freopen("bomb.in","r",stdin);
  freopen("bomb.out","w",stdout);
scanf("%d%d",&n,&m);
for(int i=1;i<=n;++i) scanf("%s", &c1[i][1]);
for(int i=0;i<2505;++i) zr[i] = inf;

for(int i=0;i<2;++i) {
    memset((lf), 0, sizeof(lf));
    memset((rg), 0, sizeof(rg));
for(int i=1;i<=n;++i){
  for(int j=1;j<=m;++j)
    if(c1[i][j] == '1') lf[i][j] = lf[i][j-1] + 1;
  for(int j=m;j>=1;--j)
    if(c1[i][j] == '1') rg[i][j] = rg[i][j+1] + 1;
  for(int j=1;j<=m;++j)
    if(c1[i][j] == '1' && c1[i][j+1] != '1') zr[1] = min(zr[1], lf[i][j]);
    }

    for(int j=1;j<=m;++j)
    for(int i=0;i<=n+1;++i)
        if(c1[i][j] == '1') {
        l = min(l, lf[i][j]);  r = min(r, rg[i][j]);
        zr[i - bolo] = min(zr[i - bolo], l + r - 1);
        } else {
        if(i && bolo != i-1) zr[i - bolo] = 0;
        l = inf; r = inf;  bolo = i;
        }
 for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            c2[i][j] = c1[n+1-i][j];
 for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
             c1[i][j] = c2[i][j];
}
int b = inf;

for(int a=1;a<=2504;++a) {
  b = min(b, zr[a]);
  ans = max(ans, {a*b, b});
}

cout << ans.first<< endl;
}
