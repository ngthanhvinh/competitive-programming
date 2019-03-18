#include "Alicelib.h"
#include <bits/stdc++.h>
using namespace std;

static int nver;
static vector < pair<int,int> > edges;

void Alice(int N, int M, int A[], int B[]) {
	nver = N;
	for (int i = 0; i < M; ++i) {
		edges.push_back(make_pair(A[i], B[i]));
	}

	nver += 10;
	vector<int> bits;
	for (int i = N; i < nver; ++i) {
		bits.push_back(i);
	}
	++nver; int s = nver - 1;
	++nver; int t = nver - 1;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < 10; ++j) if (i >> j & 1) {
			edges.push_back(make_pair(i, bits[j]));
		}
	}
	for (int &i : bits) {
		edges.push_back(make_pair(s, i));
		edges.push_back(make_pair(t, i));
	}
	if (N != 1) edges.push_back(make_pair(1, t));

	for (int i = 1; i < 10; ++i) {
		edges.push_back(make_pair(bits[i], bits[i - 1]));
	}

	InitG(nver, edges.size());
	for (int i = 0; i < edges.size(); ++i) {
		MakeG(i, edges[i].first, edges[i].second);
	}
}

