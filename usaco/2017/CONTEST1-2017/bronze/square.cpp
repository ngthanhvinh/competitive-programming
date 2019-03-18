#include <iostream>
#include <cstdio>
using namespace std;

int X1, Y1, X2, Y2;
int XX1, YY1, XX2, YY2;
int mnX, mxX, mnY, mxY;

int main() {
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> X1 >> Y1 >> X2 >> Y2;
    cin >> XX1 >> YY1 >> XX2 >> YY2;
    mnX = min(min(X1, X2), min(XX1, XX2));
    mxX = max(max(X1, X2), max(XX1, XX2));
    mnY = min(min(Y1, Y2), min(YY1, YY2));
    mxY = max(max(Y1, Y2), max(YY1, YY2));
    int val = max(mxX - mnX, mxY - mnY);
    printf("%d", val * val );
}
