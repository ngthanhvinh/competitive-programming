#include <bits/stdc++.h>
using namespace std;

long long mem[10];

long long get(int d) {
	if (mem[d] != -1) return mem[d];
	cout << d << endl;
	long long reply;
	cin >> reply;
	mem[d] = reply;
	return reply;
}

vector<double> gauss(vector< vector<double> > A) {
    int n = A.size();

    for (int i=0; i<n; i++) {
        // Search for maximum in this column
        double maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
                maxRow = k;
            }
        }

        // Swap maximum row with current row (column by column)
        for (int k=i; k<n+1;k++) {
            double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }

        // Make all rows below this one 0 in current column
        for (int k=i+1; k<n; k++) {
            double c = -A[k][i]/A[i][i];
            for (int j=i; j<n+1; j++) {
                if (i==j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] += c * A[i][j];
                }
            }
        }
    }

    // Solve equation Ax=b for an upper triangular matrix A
    vector<double> x(n);
    for (int i=n-1; i>=0; i--) {
        x[i] = A[i][n]/A[i][i];
        for (int k=i-1;k>=0; k--) {
            A[k][n] -= A[k][i] * x[i];
        }
    }
    return x;
}

void solve(int w) {
	memset(mem, -1, sizeof mem);
	if (w == 6) {
		vector < vector<double> > A;
		for (int i = 1; i <= 6; ++i) {
			vector<double> cur;
			for (int j = 1; j <= 6; ++j) {
				cur.push_back(1 << (i / j));
			}
			cur.push_back(get(i));
			A.push_back(cur);
		}

		vector <double> res = gauss(A);
		for (int i = 0; i < res.size(); ++i) {
			cout << (int)res[i] << ' ';
		}
		cout << endl;

		int verdict;
		cin >> verdict;
		assert(verdict == 1);
	}

	else {
		assert(0);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	int t, w; cin >> t >> w;
	while(t--) {
		solve(w);
	}
}