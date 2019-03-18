#include "horses.h"
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define double long double
const int MAXN = 500005;
const int mod = 1e9 + 7;

int n, x[MAXN], y[MAXN];
int prodx[MAXN];
double lgx[MAXN];

int binpow(int a, int b) {
	int ret = 1;
	while(b) {
		if (b & 1) ret = 1LL * ret * a % mod; a = 1LL * a * a % mod;
		b >>= 1;
	}
	return ret;
}

int inverse(int a) {
	return binpow(a, mod - 2);
}

pair <double, int> t[MAXN << 2];
pair <double, int> lz[MAXN << 2];
#define mid ((l + r) >> 1)

void build(int v, int l, int r) {
	lz[v] = {0.0, 1};
	if (l == r) {
		t[v] = {lgx[l] + (double)log(y[l]), 1LL * prodx[l] * y[l] % mod};
		return;
	}
	build(v << 1, l, mid);
	build(v << 1 | 1, mid + 1, r);
	t[v] = max(t[v << 1], t[v << 1 | 1]);
}

void merge(pair<double, int> &p, pair<double, int> q) {
	p.first += q.first;
	p.second = 1LL * p.second * q.second % mod;
}

void push(int v, int l, int r) {
	if (lz[v].second == 1) return;
	if (l < r) merge(lz[v << 1], lz[v]), merge(lz[v << 1 | 1], lz[v]);
	t[v].first += lz[v].first; // log
	t[v].second = 1LL * t[v].second * lz[v].second % mod;
	lz[v] = {0.0, 1};
}

void upd(int v, int l, int r, int L, int R, int mul, double lg) {
	push(v, l, r);
	if (R < l || L > r) return;
	if (L <= l && r <= R) {
		lz[v] = {lg, mul}; push(v, l, r); return;
	}
	upd(v << 1, l, mid, L, R, mul, lg);
	upd(v << 1 | 1, mid + 1, r, L, R, mul, lg);
	t[v] = max(t[v << 1], t[v << 1 | 1]);
}

int init(int N, int X[], int Y[]) {
	n = N;
	for (int i = 0; i < n; ++i) {
		x[i] = X[i];
		y[i] = Y[i];
	}
	prodx[0] = x[0];
	lgx[0] = log(x[0]);
	for (int i = 1; i < n; ++i) {
		prodx[i] = 1LL * prodx[i - 1] * x[i] % mod;
		lgx[i] = lgx[i - 1] + log(x[i]);
	}
	build(1, 0, n - 1);
	return t[1].second;
}

int updateX(int pos, int val) {
	int mul = 1LL * inverse(x[pos]) * val % mod;
	double lg = -log(x[pos]) + log(val);
	upd(1, 0, n - 1, pos, n - 1, mul, lg);
	x[pos] = val;
	return t[1].second;
}

int updateY(int pos, int val) {
	int mul = 1LL * inverse(y[pos]) * val % mod;
	double lg = -log(y[pos]) + log(val);
	upd(1, 0, n - 1, pos, pos, mul, lg);
	y[pos] = val;
	return t[1].second;
}
