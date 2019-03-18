#include <bits/stdc++.h>
using namespace std;
 
const int maxN = 5e3 + 10,maxD = 5e4 + 10,oo = 1e9 + 1e5;
 
int a[maxN],dis[maxD],m,x,n;
 
typedef pair<int,int> ii;
 
void djiskstra() {
    for(int i = 1; i < a[1]; ++i) dis[i] = oo;
    priority_queue<ii> pq;
    pq.push(ii(0,0));
    while(!pq.empty()) {
        int u = pq.top().second;
        int du = -pq.top().first;
        pq.pop();
        if(du != dis[u]) continue;
        for(int i = 2; i <= n; ++i) {
            int v = (a[i] + u) % a[1];
            int dv = a[i];
            if(dis[v] > dv + du) {
                dis[v] = dv + du;
                pq.push(ii(-dis[v],v));
            }
        }
    }
}
 
int main() {
    scanf("%d",&n);
    for(int i = 1; i <= n; ++i)
        scanf("%d",a+i);
    djiskstra();
    scanf("%d",&m);
    while(m--) {
        scanf("%d",&x);
        int tmp = x % a[1];
        if(x >= dis[tmp]) printf("TAK\n");
        else printf("NIE\n");
    }
}