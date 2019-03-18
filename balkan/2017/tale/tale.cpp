#include <bits/stdc++.h>
#include <cmath>
#define fl double
using namespace std;
const fl pi = acos(-1.0);
const fl eps = 0.000000001;
int n;
int prv(int i){return i==1?n:i-1;}
int nxt(int i){return i==n?1:i+1;}
int i,j,st,dr,gasit,cnt_st,cnt_dr;
fl X,Y,L,u,sol=0,x[1010],y[1010],
aria(fl,fl,fl,fl,fl,fl),
unghi(fl,fl,fl,fl,fl,fl),
dist(fl,fl,fl,fl);
void vizibil(fl,fl,fl,fl,fl&,fl&);

int cmp(fl a, fl b) {
    if (a + eps < b)
        return -1;
    if (b + eps < a)
        return 1;
    return 0;
}

int main()
{
    cin>>X>>Y>>L>>n;
    for(i=1;i<=n;i++)
        {cin>>x[i]>>y[i];x[i]-=X;y[i]-=Y;}
    for(i=1;i<=n;i++){
        fl ad=aria(0,0,x[i],y[i],x[prv(i)],y[prv(i)]);
        fl as=aria(0,0,x[nxt(i)],y[nxt(i)],x[i],y[i]);
        if(cmp(ad, 0) < 0 &&cmp(as, 0) >= 0){st=i;gasit++;}
        if(cmp(as, 0) <0 && cmp(ad, 0) >=0){dr=i;gasit++;}
        if(gasit==2)break;
    }

    fl Un=2*pi;
    for(i=dr,j=nxt(dr);i!=st;i=nxt(i),j=nxt(j))
    {
        fl ar,un;vizibil(x[j],y[j],x[i],y[i],ar,un);
        sol+=ar;
        Un-=un;
    }
    sol+=Un*L*L/2.0;
    fl RS,RD;int ps,pd,ss,sd;
    RS=L-dist(0,0,x[st],y[st]);ps=prv(st);ss=nxt(st);
    while(cmp(RS, 0) >0){cnt_st++;
        if(st==dr)
        {
            ///cerr<<"L prea mare";
            return 0;
        }
        fl RC=dist(x[st],y[st],x[ss],y[ss]);
        fl UC=unghi(x[ps],y[ps],x[st],y[st],x[ss],y[ss]);
        if(cnt_st==1)UC=unghi(0.0,0.0,x[st],y[st],x[ss],y[ss]);
        if(cmp(RS, RC) < 0)
        {
            sol+=UC*RS*RS/2.0;
            break;
        }
        sol+=UC*RS*RS/2.0;
        RS-=RC;
        ps=nxt(ps);st=nxt(st);ss=nxt(ss);
    }
    RD=L-dist(0,0,x[dr],y[dr]);pd=nxt(dr);sd=prv(dr);
    while(cmp(RD, 0) > 0)
    {
        cnt_dr++;
        if(st==dr)
        {
            ///cerr<<"L prea mare";
            return 0;
        }
        fl RC=dist(x[dr],y[dr],x[sd],y[sd]);
        fl UC=unghi(x[pd],y[pd],x[dr],y[dr],x[sd],y[sd]);
        if(cnt_dr==1) UC=unghi(0,0,x[dr],y[dr],x[sd],y[sd]);
        if(cmp(RD, RC) < 0)
        {
            sol+=UC*RD*RD/2.0;
            break;
        }
        sol+=UC*RD*RD/2.0;
        RD-=RC;
        pd=prv(pd);dr=prv(dr);sd=prv(sd);
    }
    if(ss==dr)
    {
        fl DC=dist(x[st],y[st],x[nxt(st)],y[nxt(st)]);
        if(cmp(RS+RD, DC) > 0)
            sol-=RS*RS*acos((RS*RS+DC*DC-RD*RD)/(2*RS*DC))/2.0+
                 RD*RD*acos((RD*RD+DC*DC-RS*RS)/(2*RD*DC))/2.0-
                 sqrt((DC+RS+RD)*(-DC+RS+RD)*(DC-RS+RD)*(DC+RS-RD))/4.0;
    }
    ///if(cnt_st==0)cerr<<"subtask fara stanga\n";
    ///if(cnt_dr==0)cerr<<"subtask fara dreapta\n";
    ///if(cnt_st&&cnt_dr)cerr<<"subtask cu ambele parti\n";
    ///fl expected_sol;
    ///fexpected>>expected_sol;
    ///fcout<<fixed<<setprecision(10)<<expected_sol<<'\n';
    ///fcout<<fixed<<setprecision(10)<<sol<<'\n';
    ///cerr<<fixed<<setprecision(10)<<fabs(sol-expected_sol)<<'\n';
    ///fcout<<(int)sol;
    cout<<fixed<<setprecision(10)<<sol;
    return 0;
}
fl aria(fl a1,fl b1,fl a2,fl b2,fl a3,fl b3){return a1*b2+a2*b3+a3*b1-b1*a2-b2*a3-b3*a1;}
fl dist(fl a1,fl b1,fl a2,fl b2){return sqrt((a2-a1)*(a2-a1)+(b2-b1)*(b2-b1));}
fl unghi(fl a1,fl b1,fl a2,fl b2,fl a3,fl b3)
{fl a,b,c;a=dist(a1,b1,a2,b2);b=dist(a2,b2,a3,b3);c=dist(a3,b3,a1,b1);return pi-acos ((a*a+b*b-c*c )/(2*a*b));}
void vizibil(fl a1,fl b1,fl a2,fl b2,fl &ar,fl &un)
{
    //cantitate neglijabila
    fl a,b,c,h;c=dist(a1,b1,a2,b2);if(c<eps){ar=eps;un=eps;return;}
    //drepata prea departe
    if(cmp(fabs(a1*b2-a2*b1),L*dist(a1,b1,a2,b2))>=0){ar=eps;un=eps;return;}
    //un capat in interior si unul in exterior => DEI
    a=dist(0,0,a1,b1);b=dist(0,0,a2,b2);
    //cerr<<a<<' '<<b<<' '<<c<<'\n';
    if(cmp((a-L)*(b-L),0)<0)
    {fl ar1,ar2,un1,un2;a=(a1+a2)/2.0;b=(b1+b2)/2.0;vizibil(a1,b1,a,b,ar1,un1);vizibil(a,b,a2,b2,ar2,un2);
        ar=ar1+ar2;un=un1+un2;return;
    }
    //ambele capete in interior
    if(cmp(a,L)<=0&&cmp(b,L)<=0){ar=fabs(a1*b2-b1*a2)/2.0;un=acos((a*a+b*b-c*c)/(2.0*a*b));return;}

    //ramane cazul cu ambele capete in exterior;
    // un unghi obtuz => segmentul este exterior
    if(cmp(a*a+c*c,b*b)<0||cmp(b*b+c*c,a*a)<0){ar=eps;un=eps;return;}
    //triunghi isoscel
    a=b=L;h=fabs(a1*b2-a2*b1)/dist(a1,b1,a2,b2);c=2.0*sqrt(L*L-h*h);ar=c*h/2.0;un=acos((a*a+b*b-c*c)/(2*a*b));
}

