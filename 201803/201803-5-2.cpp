/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-13 10:48:34
 * 	modified: 	2024-07-13 19:04:54
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
// https://www.acwing.com/solution/content/222708/
// by Zi_Gao
#include <bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read() {
	register INPUT_DATA_TYPE x = 0;
	register char f = 0, c = getchar();
	while (c < '0' || '9' < c)
		f = (c == '-'), c = getchar();
	while ('0' <= c && c <= '9')
		x = (x << 3) + (x << 1) + (c & 15), c = getchar();
	return f ? -x : x;
}
void print(OUTPUT_DATA_TYPE x) {
	if (x < 0)
		x = -x, putchar('-');
	if (x > 9)
		print(x / 10);
	putchar(x % 10 ^ 48);
	return;
}

const int NNNN = 100010;
std::vector<int> viscur, cur, e[NNNN];
std::bitset<NNNN> vis;
long long val[NNNN], cntCur[NNNN], cntNow[NNNN], inPath[NNNN];
const long long mod = 1000000007;
int siz[NNNN], par[NNNN], dep[NNNN], L, R, n;

void addEdge(int u, int v) {
	e[u].push_back(v);
	e[v].push_back(u);
	return;
}

void dfsSiz(int u, int p) {
	cur.push_back(u), par[u] = p, siz[u] = 1;
	for (auto v : e[u])
		if (v != p && (!vis[v]))
			dfsSiz(v, u), siz[u] += siz[v];
	return;
}

void dfsDep(int u, int p) {
	viscur.push_back(u), par[u] = p;
	for (auto v : e[u])
		if (v != p && (!vis[v]))
			dep[v] = dep[u] + 1, dfsDep(v, u);
	return;
}

void calc(std::vector<int> &cur, long long op) {
	register int i, maxDep = 0;
	for (auto u : cur)
		maxDep = std::max(maxDep, dep[u]), ++cntCur[dep[u]];

	for (i = 1; i <= maxDep; ++i)
		cntCur[i] += cntCur[i - 1];
	for (auto u : cur) {
		if (dep[u] <= R)
			cntNow[u] += cntCur[std::min(maxDep, R - dep[u])] * op;
		if (dep[u] <= L)
			cntNow[u] -= cntCur[std::min(maxDep, L - dep[u])] * op;
	}

	for (i = 0; i <= maxDep; ++i)
		cntCur[i] = 0;
	return;
}

void getAns(int u, int p) {
	for (auto v : e[u])
		if (v != p && !vis[v])
			getAns(v, u), cntNow[u] += cntNow[v];
	return;
}

void solve(int rt) {
	register int i, newRt = rt, min = 0, tmp;
	siz[rt] = 1, cur.clear();
	for (auto v : e[rt]) {
		if (vis[v])
			continue;
		dfsSiz(v, rt), siz[rt] += siz[v], min = std::max(min, siz[v]);
	}
	for (auto u : cur) {
		tmp = siz[rt] - siz[u];
		for (auto v : e[u]) {
			if (v == par[u] || vis[v])
				continue;
			tmp = std::max(tmp, siz[v]);
		}
		if (tmp < min)
			min = tmp, newRt = u;
	}
	cur.push_back(rt);

	dep[newRt] = 0;
	for (auto u : e[newRt]) {
		if (vis[u])
			continue;
		dep[u] = 1, viscur.clear(), dfsDep(u, newRt);
		calc(viscur, -1);
	}
	calc(cur, 1);
	getAns(newRt, 0);

	cntNow[newRt] >>= 1;
	for (auto u : cur)
		inPath[u] += cntNow[u], cntNow[u] = 0;

	vis[newRt] = 1;
	for (auto v : e[newRt])
		if (!vis[v])
			solve(v);
}
namespace LCA {
#define ln(x) 31 ^ __builtin_clz(x)
	int cntDfn, dfn[NNNN], parsour[NNNN], depsour[NNNN];
#define ST_DATA_TYPE int
#define ST_TYPE >
	const int ST_MAXI = 100010;
	const int ST_MAXJ = 22;
	ST_DATA_TYPE ST_CALC(ST_DATA_TYPE a, ST_DATA_TYPE b) {
		return depsour[a] < depsour[b] ? a : b;
	}
	struct ST {
		ST_DATA_TYPE f[ST_MAXJ][ST_MAXI];

		void build(int size) {
			register int i, j;
			int k = ln(size);
			for (j = 1; j <= k; ++j)
				for (i = 1; i <= size - (1 << j) + 1; ++i)
					f[j][i] = ST_CALC(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
			return;
		}

		ST_DATA_TYPE query(int l, int r) {
			if (l == r)
				return l;
			l = dfn[l];
			r = dfn[r];
			if (l > r)
				std::swap(l, r);
			++l;
			int k = ln(r - l + 1);
			int u = f[k][l];
			int v = f[k][r - (1 << k) + 1];
			if (depsour[u] < depsour[v])
				return parsour[u];
			else
				return parsour[v];
		}
	} st;

	void dfsLca(int u, int p) {
		depsour[u] = depsour[p] + 1;
		st.f[0][dfn[u] = ++cntDfn] = u;
		parsour[u] = p;
		inPath[u] += inPath[p];
		for (auto v : e[u])
			if (v != p)
				dfsLca(v, u);
	}
}; // namespace LCA

void solve() {
	register int i, u, v, lca;
	register long long res = 0, w;
	n = read();
	int m = read();
	L = read() - 2, R = read() - 1;

	for (i = 1; i <= n; ++i)
		val[i] = read();
	for (i = 2; i <= n; ++i)
		addEdge(read(), i);
	solve(1);
	if (L + 2 == 1)
		for (i = 1; i <= n; ++i)
			inPath[i] += 1;
	for (i = 1; i <= n; ++i)
		inPath[i] %= mod, (res += inPath[i] * val[i]) %= mod;

	LCA::dfsLca(1, 0);
	LCA::st.build(n);

	for (i = 0; i < m; ++i) {
		u = read();
		v = read();
		lca = LCA::st.query(u, v);
		w = read();
		(res += ((inPath[u] + inPath[v] + (mod - inPath[LCA::parsour[lca]]) + (mod - inPath[lca])) % mod) * w) %= mod;
		print(res), putchar('\n');
	}

	for (i = 1; i <= n; ++i)
		e[i].clear();
	memset(inPath, 0, sizeof(inPath));
	vis.reset();
	LCA::cntDfn = 0;
}

int main() {

	int T = read();
	while (T--)
		solve();

#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
#endif
	return 0;
}