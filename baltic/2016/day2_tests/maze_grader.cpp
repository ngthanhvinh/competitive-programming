// grader for "Maze"
//
// command line parameters:
//   * jury output file
//   * contestant output file
//   * input file
//
// output:
//   * 0 if format is incorrect
//   * 1 if format is correct, followed by score on another line

#include <iostream>
#include <fstream>
#include <queue>
#include <climits>

using namespace std;

constexpr int maxN = 20;
constexpr int maxM = 20;
constexpr int maxK = 13;

int n, m, k;
string X[maxN];
int is[maxK];
int js[maxK];
int d[maxK][maxK];
int d2[maxN][maxM];
int T[1 << maxK][maxK];

int comp(ifstream& out) {
	for(int i = 0; i < n; ++i) {
		out >> X[i];
		if((int)X[i].size() != m) return -1;
	}
	
	int xs = 0;
	int os = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			char c = X[i][j];
			if(c != 'x' && c != 'o' && c != '.' && c != '#') return -1;
			if(c == 'x') ++xs;
			if(c == 'o') ++os;
		}
	}
	if(xs != 1 || os != k - 1) return -1;
	int idx = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(X[i][j] == 'x' || X[i][j] == 'o') {
				is[idx] = i;
				js[idx] = j;
				++idx;
				X[i][j] = '.';
			}
		}
	}
	
	for(int s = 0; s < k; ++s) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				d2[i][j] = -1;
			}
		}
		
		queue<pair<int, int>> Q;
		Q.emplace(is[s], js[s]);
		d2[is[s]][js[s]] = 0;
		while(!Q.empty()) {
			int i = Q.front().first;
			int j = Q.front().second;
			Q.pop();
			auto adv = [&](int i2, int j2) {
				if(i2 < 0 || j2 < 0 || i2 >= n || j2 >= m) return;
				if(d2[i2][j2] != -1) return;
				if(X[i2][j2] == '#') return;
				Q.emplace(i2, j2);
				d2[i2][j2] = d2[i][j] + 1;
			};
			adv(i - 1, j);
			adv(i + 1, j);
			adv(i, j - 1);
			adv(i, j + 1);
		}
		
		for(int t = 0; t < k; ++t) {
			if(d2[is[t]][js[t]] == -1) return -1;
			d[s][t] = d2[is[t]][js[t]];
		}
	}
	
	for(int c = 0; c < (1 << k); ++c) {
		for(int e = 0; e < k; ++e) {
			T[c][e] = INT_MAX;
		}
	}
	
	for(int i = 1; i < k; ++i) {
		T[1 << i][i] = d[0][i];
	}
	
	for(int c = 0; c < (1 << k); ++c) {
		for(int e = 0; e < k; ++e) {
			if(T[c][e] == INT_MAX) continue;
			for(int f = 0; f < k; ++f) {
				if((1 << f) & c) continue;
				T[c | (1 << f)][f] = min(T[c | (1 << f)][f], T[c][e] + d[e][f]);
			}
		}
	}
	
	int res = T[(1 << k) - 1][0];
	if(res < 0 && res == INT_MAX) throw 0;
	return res;
}

int main(int argc, char **argv) {
	if(argc != 4) throw 0;
	
	ifstream correct;
	correct.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
	correct.open(argv[1]);
	ifstream user;
	user.open(argv[2]);
	ifstream input;
	input.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);
	input.open(argv[3]);
	
	int t;
	input >> t;
	
	int score = 0;
	for(int te = 0; te < t; ++te) {
		input >> n >> m >> k;
		++k;
		if(n < 2 || m < 2 || k < 2) throw 0;
		if(n > maxN || m > maxM || k > maxK) throw 0;
		
		int correctVal = comp(correct);
		if(correctVal < 0) throw 0;
		int userVal = comp(user);
		if(userVal < 0) {
			cout << "0\n";
			return 0;
		}
		score += max(0, 100 - 3 * (correctVal - userVal));
	}
	score /= t;
	
	cout << "1\n";
	cout << score << '\n';
	
	return 0;
}
