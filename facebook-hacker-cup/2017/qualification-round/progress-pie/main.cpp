#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
typedef pair<int,int> ii;
#define x first
#define y second
const double pi = acos(-1.0);

long long dist(ii a, ii b) {
    return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
}

int Case;

void white() { printf("Case #%d: white\n", ++Case); }
void black() { printf("Case #%d: black\n", ++Case); }

int main() {
//    freopen("progress_pie.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    ii A = ii(50,50);
    ii B = ii(50,100);
    long long a = dist(A, B); double sqrta = sqrt(a);
    while(T--) {
        int P, X, Y; cin >> P >> X >> Y;
        ii C = ii(X,Y);
        long long b = dist(A,C), c = dist(B,C);
        if (b > 50 * 50) { white(); continue; }
        double sqrtb = sqrt(b);
        double cos_alpha = (a + b - c) / ((double)sqrta * sqrtb) / 2.0;
        double alpha = acos(cos_alpha);

        alpha /= pi; alpha *= 180.0;
        double p = (double)P * 3.6;
        if (P <= 50) {
            if (alpha <= p) black();
            else white();
        }
        else {
            if (alpha >= 360.0 - p) black();
            else white();
        }
    }
}
