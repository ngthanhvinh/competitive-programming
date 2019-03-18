#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define ff(i, a, b) for(int i = a; i <= b; i++)
#define fo(i, a, b) for(int i = a; i < b; i++)
#define fod(i, a, b) for(int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

const int INF = 1e9, N = 100010;
const ll INFL = 1e18;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n;
const char inpFile[100][20] = {"1.in", "2.in", "3.in", "4.in", "5.in", "6.in", "7.in", "8.in", "9.in", "10.in", "11.in", "12.in", "13.in", "14.in", "15.in", "16.in", "17.in", "18.in", "19.in", "20.in", "21.in", "22.in", "23.in", "24.in", "25.in", "26.in", "27.in", "28.in", "29.in", "30.in", "31.in", "32.in", "33.in", "34.in", "35.in", "36.in", "37.in", "38.in", "39.in", "40.in", "41.in", "42.in", "43.in", "44.in", "45.in", "46.in", "47.in", "48.in", "49.in", "50.in", "51.in", "52.in", "53.in", "54.in", "55.in", "56.in", "57.in", "58.in", "59.in", "60.in", "61.in", "62.in", "63.in", "64.in", "65.in", "66.in", "67.in", "68.in", "69.in", "70.in", "71.in", "72.in", "73.in", "74.in", "75.in", "76.in", "77.in", "78.in", "79.in", "80.in", "81.in", "82.in", "83.in", "84.in", "85.in", "86.in", "87.in", "88.in", "89.in", "90.in", "91.in", "92.in", "93.in", "94.in", "95.in", "96.in", "97.in", "98.in", "99.in", "100.in"};
const char outFile[100][20] = {"1.out", "2.out", "3.out", "4.out", "5.out", "6.out", "7.out", "8.out", "9.out", "10.out", "11.out", "12.out", "13.out", "14.out", "15.out", "16.out", "17.out", "18.out", "19.out", "20.out", "21.out", "22.out", "23.out", "24.out", "25.out", "26.out", "27.out", "28.out", "29.out", "30.out", "31.out", "32.out", "33.out", "34.out", "35.out", "36.out", "37.out", "38.out", "39.out", "40.out", "41.out", "42.out", "43.out", "44.out", "45.out", "46.out", "47.out", "48.out", "49.out", "50.out", "51.out", "52.out", "53.out", "54.out", "55.out", "56.out", "57.out", "58.out", "59.out", "60.out", "61.out", "62.out", "63.out", "64.out", "65.out", "66.out", "67.out", "68.out", "69.out", "70.out", "71.out", "72.out", "73.out", "74.out", "75.out", "76.out", "77.out", "78.out", "79.out", "80.out", "81.out", "82.out", "83.out", "84.out", "85.out", "86.out", "87.out", "88.out", "89.out", "90.out", "91.out", "92.out", "93.out", "94.out", "95.out", "96.out", "97.out", "98.out", "99.out", "100.out"};

int main() {
	ios_base::sync_with_stdio(false);
	ff(i, 1, 100) {
		freopen(inpFile[i - 1], "r", stdin);
		freopen(outFile[i - 1], "w", stdout);
		cin >> n; int ans = 0;
		ff(i, 1, n) ff(j, i, n) {
			if (i + j - __gcd(i, j) == n) ans++;
		} 
		cout << ans << endl;
	}
}