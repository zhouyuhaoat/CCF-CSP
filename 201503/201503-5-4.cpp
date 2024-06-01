/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-06-01 16:01:10
 * 	modified: 	2024-06-01 17:06:33
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int maxv = 1e5 + 10;

int p[maxv];
pair<int, int> q[maxv];
vector<pair<int, int>> g[maxv];
long long ans[maxv], up[maxv], down[maxv];

vector<int> qtr[maxv];
vector<pair<int, int>> qry[maxv];

bool st[maxv];

int bel[maxv], fa[maxv][17], pri[maxv][17], dis[maxv];

int minf[maxv], minp[maxv], top;
// minp: minimum price from root, for binary search

int getsize(int u, int f) {
	if (st[u]) {
		return 0;
	}
	int s = 1;
	for (auto e : g[u]) {
		int v = e.first;
		if (v != f) {
			s += getsize(v, u);
		}
	}
	return s;
}

int centroid(int u, int f, int tot, int &cen) {
	if (st[u]) {
		return 0;
	}
	int s = 1, maxs = 0;
	for (auto e : g[u]) {
		int v = e.first;
		if (v == f) {
			continue;
		}
		int ss = centroid(v, u, tot, cen);
		maxs = max(maxs, ss);
		s += ss;
	}
	maxs = max(maxs, tot - s);
	if (maxs <= tot / 2) {
		cen = u;
	}
	return s;
}

void dfs1(int u, int f, int id) {
	if (st[u]) {
		return;
	}
	bel[u] = id;
	qry[u].clear();
	fa[u][0] = f, pri[u][0] = p[u];
	for (int i = 1; i < 17; i++) {
		int anc = fa[u][i - 1];
		fa[u][i] = fa[anc][i - 1];
		pri[u][i] = min(pri[anc][i - 1], pri[u][i - 1]);
	}
	if (pri[u][16] == p[u]) {
		up[u] = (long long)dis[u] * p[u];
	} else {
		int next = u;
		for (int i = 16; i >= 0; i--) {
			if (pri[next][i] >= p[u]) {
				next = fa[next][i];
			}
		}
		up[u] = up[next] + (long long)(dis[u] - dis[next]) * p[u];
	}
	for (auto e : g[u]) {
		auto [v, w] = e;
		if (v != f && !st[v]) {
			dis[v] = dis[u] + w;
			dfs1(v, u, id);
		}
	}
}

void dfs2(int v, int f) {
	if (st[v]) {
		return;
	}
	if (p[minf[top - 1]] < p[v]) {
		minf[top] = minf[top - 1];
		minp[top] = minp[top - 1];
	} else {
		minf[top] = v;
		minp[top] = p[v];
	}
	++top;
	for (auto qq : qry[v]) {
		auto [u, id] = qq;
		if (pri[u][16] <= p[minf[top - 1]]) {
			ans[id] = up[u] + (long long)dis[v] * pri[u][16];
		} else {
			int idx = upper_bound(minp, minp + top, pri[u][16], greater<int>()) - minp;
			// int idx = lower_bound(minp, minp + top, pri[u][16], greater<int>()) - minp;
			int next = minf[idx];
			ans[id] = up[u] + down[v] - down[next] + (long long)dis[next] * pri[u][16];
		}
	}
	for (auto e : g[v]) {
		auto [u, w] = e;
		if (u != f && !st[u]) {
			down[u] = down[v] + (long long)p[minf[top - 1]] * w;
			dfs2(u, v);
		}
	}
	--top;
}

void calc(int u) {
	if (st[u]) {
		return;
	}
	vector<int> qq;
	qq.swap(qtr[u]);
	centroid(u, -1, getsize(u, -1), u);
	st[u] = true;
	for (int i = 0; i < 17; i++) {
		fa[u][i] = u, pri[u][i] = p[u];
	}
	dis[u] = up[u] = 0, bel[u] = 0;
	for (auto e : g[u]) {
		auto [v, w] = e;
		dis[v] = dis[u] + w;
		dfs1(v, u, v);
	}
	for (auto id : qq) {
		if (q[id].second == u) {
			ans[id] = up[q[id].first];
		} else if (bel[q[id].first] == bel[q[id].second]) {
			qtr[bel[q[id].first]].emplace_back(id);
		} else {
			qry[q[id].second].emplace_back(q[id].first, id);
		}
	}
	down[u] = 0, minf[0] = u, top = 1;
	minp[0] = p[u];
	for (auto e : g[u]) {
		auto [v, w] = e;
		down[v] = down[u] + (long long)p[minf[top - 1]] * w;
		dfs2(v, u);
	}
	for (auto e : g[u]) {
		int v = e.first;
		if (!qtr[v].empty()) {
			calc(v);
		}
	}
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
	}
	for (int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		q[i] = make_pair(u, v);
		if (u != v) {
			qtr[1].emplace_back(i);
		}
	}
	calc(1);
	for (int i = 1; i <= m; i++) {
		cout << ans[i] << "\n";
	}

	return 0;
}