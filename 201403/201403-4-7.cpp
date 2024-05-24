/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-23 13:10:55
 * 	modified: 	2024-05-24 19:39:33
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <queue>

using namespace std;

int n, m, k, r;
vector<pair<int, int>> p;
vector<vector<int>> g;
vector<int> d;

int point(int l, int v) { // l: layer, v: vertex
	return (n + m) * l + v;
}

void addedge(int l, int u, int v, int flag) { // flag: next layer or current layer
	for (int i = 0; i < l; i++) {
		g[point(i, u)].emplace_back(point(i + flag, v));
	}
}

bool isok(pair<int, int> a, pair<int, int> b) {
	int dx = a.first - b.first, dy = a.second - b.second;
	return (long long)dx * dx + (long long)dy * dy <= (long long)r * r;
}

void bfs(int s) {
	d[point(0, s)] = 0;
	queue<int> q;
	q.emplace(point(0, s));
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto v : g[u]) {
			if (d[v] >= 0x3fffffff) { // unvisited
				d[v] = d[u] + 1;
				q.emplace(v);
			}
		}
	}
}

int main(int argc, char const *argv[]) {

	cin >> n >> m >> k >> r;
	p.resize(n + m);
	for (int i = 0; i < n + m; i++) {
		cin >> p[i].first >> p[i].second;
	}
	g.resize((n + m) * (k + 1)); // layered graph & vertex decomposition
	for (int i = 0; i < n + m; i++) {
		for (int j = i + 1; j < n + m; j++) {
			if (isok(p[i], p[j])) {
				if (i < n && j < n) {
					addedge(k + 1, i, j, 0), addedge(k + 1, j, i, 0);
				} else if (i >= n && j < n) {
					addedge(k + 1, i, j, 0), addedge(k, j, i, 1);
				} else if (i < n && j >= n) {
					addedge(k, i, j, 1), addedge(k + 1, j, i, 0);
				} else {
					addedge(k, i, j, 1), addedge(k, j, i, 1);
				}
			}
		}
	}
	d.resize((n + m) * (k + 1), 0x3fffffff);
	bfs(0);
	int ans = 0x3fffffff;
	for (int l = 0; l <= k; l++) {
		ans = min(ans, d[point(l, 1)]);
	}
	cout << ans - 1 << "\n";

	return 0;
}