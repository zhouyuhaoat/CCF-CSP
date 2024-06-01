/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-31 13:46:15
 * 	modified: 	2024-06-01 16:41:59
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

const int maxv = 1e5 + 10;

int p[maxv];
pair<int, int> q[maxv];			// query: u -> v
vector<pair<int, int>> g[maxv]; // edge: v(ertex), w(eight)
long long ans[maxv], up[maxv], down[maxv];

vector<int> qtr[maxv];			  // query id of subtree
vector<pair<int, int>> qry[maxv]; // query: u, id

bool st[maxv];

int bel[maxv], fa[maxv][17], pri[maxv][17], dis[maxv];
// dis: distance from root, sum of weight of path, length of weighted path

int getsize(int u, int f) { // size = weight = cnt
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

int centroid(int u, int f, int tot, int &cen) { // tot: total
	if (st[u]) {
		return 0;
	}
	int s = 1, maxs = 0; // size & max size
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
	if (maxs <= tot / 2) { // centroid: half size of tree rooted at centroid
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
	if (pri[u][16] == p[u]) { // without lower price during up to root
		up[u] = (long long)dis[u] * p[u];
	} else {
		int next = u;
		for (int k = 16; k >= 0; k--) {
			if (pri[next][k] >= p[u]) {
				next = fa[next][k];
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
	for (auto qq : qry[v]) {
		auto [u, id] = qq;
		if (pri[u][16] <= pri[v][16]) { // price during up lower than all price during down
			ans[id] = up[u] + (long long)dis[v] * pri[u][16];
		} else {
			int next = v;
			for (int k = 16; k >= 0; k--) {
				if (pri[fa[next][k]][16] <= pri[u][16]) {
					next = fa[next][k];
				}
			}
			ans[id] = up[u] + down[v] - down[next] + (long long)dis[next] * pri[u][16];
		}
	}
	for (auto e : g[v]) {
		auto [u, w] = e;
		if (u != f && !st[u]) {
			down[u] = down[v] + (long long)pri[v][16] * w;
			dfs2(u, v);
		}
	}
}

void calc(int u) {
	if (st[u]) {
		return;
	}
	vector<int> qq;
	qq.swap(qtr[u]); // qrt[u] cleared
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
		if (q[id].second == u) { // up -> root
			ans[id] = up[q[id].first];
		} else if (bel[q[id].first] == bel[q[id].second]) { // divide and conquer
			qtr[bel[q[id].first]].emplace_back(id);
		} else {
			qry[q[id].second].emplace_back(q[id].first, id); // up -> root -> down
		}
	}
	down[u] = 0;
	for (auto e : g[u]) {
		auto [v, w] = e;
		down[v] = down[u] + (long long)pri[u][16] * w;
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