#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory.h>
#include <cassert>
using namespace std;
 
typedef long long ll;
typedef pair<ll,ll> ii;
typedef pair<ll,ii> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
 
#define pb push_back
#define INF 1e9
#define X first
#define Y second
#define ff(i,a,b) for(ll i=a;i<=b;++i)
#define FF(i,a,b) for(ll i=a;i>=b;--i)
#define f0(i,n) for(ll i=0;i<n;++i)
#define f_all(i,a) for(ll i=0;i<a.size();++i)
#define all(a) a.begin(),a.end()
 
const int mod = (int) 1e9+7;
const int N_  = (int) 1e5+2;
 
struct heavy_light_decomposition{
    vector<int> a,IT;
    int first,last;
    void push(int x){
        if(a.size()==0) first=x;
        last=x;
        a.push_back(x);
        for(int i=0;i<4;i++) IT.pb(0);
    }
 
    void update(int k,int L,int R,int x){
        if(L>R || L>x || x>R) return ;
        if(L==x && x==R){
            if(IT[k]==a[x-1]) IT[k]=0;
            else IT[k]=a[x-1];
        }
        else{
            int mid=(L+R)>>1;
            update(2*k,L,mid,x);
            update(2*k+1,mid+1,R,x);
            if(IT[2*k+1]==0) IT[k]=IT[2*k];
            else IT[k]=IT[2*k+1];
        }
    }
 
    int get(int k,int L,int R,int x,int y){
        if(L>R || R<x || L>y || x>y) return 0;
        if(x<=L && R<=y) return IT[k];
        int mid=(L+R)>>1;
        int tmp=get(2*k+1,mid+1,R,x,y);
        if(tmp!=0) return tmp;
        tmp=get(2*k,L,mid,x,y);
        return tmp;
    }
 
};
heavy_light_decomposition hld[N_];
 
int n,q,cnt;
vector<int> G[N_];
int len[N_];
int root[N_];
int pos[N_];
int parent[N_];
 
void dfs(int u,int pu){
 
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(v==pu) continue ;
        parent[v]=u;
        dfs(v,u);
        len[u]=max(len[u],len[v]+1);
    }
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(v==pu) continue;
        if(len[u]==len[v]+1){
            root[u]=root[v];
            pos[u]=pos[v]+1;
            hld[root[u]].push(u);
            break;
        }
    }
    if(len[u]==0){
        root[u]=++cnt;
        pos[u]=1;
        hld[root[u]].push(u);
    }
}
 
int query(int u){
    if(u==0) return 0;
    int tmp=query(parent[hld[root[u]].last]);
    if(tmp!=0) return tmp;
    tmp=hld[root[u]].get(1,1,hld[root[u]].a.size(),pos[u],hld[root[u]].a.size());
    return tmp;
}
 
int main(){
    //freopen("test.txt","r",stdin);
    scanf("%d %d",&n,&q);
    for(int i=1;i<n;i++){
        int u,v;scanf("%d %d",&u,&v);
        G[u].pb(v);
        G[v].pb(u);
    }
    dfs(1,1);
 
    while(q--){
        int cmd,x;scanf("%d %d",&cmd,&x);
        if(cmd==0){
            hld[root[x]].update(1,1,hld[root[x]].a.size(),pos[x]);
        }
        else{
            if(query(x)==0) printf("-1\n");
            else printf("%d\n",query(x));
        }
    }
 
}