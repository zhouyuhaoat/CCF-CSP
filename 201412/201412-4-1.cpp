/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-03 08:42:18
 * 	modified: 	2024-05-26 19:59:47
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <queue>

using namespace std;

struct node {
	int v, d;
	node(int v, int d) : v(v), d(d) {
	}
	friend bool operator<(node a, node b) {
		return a.d > b.d;
	}
};

vector<bool> vis;
vector<int> d;
vector<vector<node>> g;

int prim(int s) { // minimum spanning tree
	d[s] = 0;
	priority_queue<node> q; // greedy, priority by the distance
	q.emplace(s, 0);
	int res = 0;
	while (!q.empty()) {
		node t = q.top();
		q.pop();
		int u = t.v;
		if (vis[u]) {
			continue;
		}
		vis[u] = true; // the set form a single tree: grow, span
		res += d[u];
		for (int i = 0; i < (int)g[u].size(); i++) {
			int v = g[u][i].v;
			if (!vis[v] && g[u][i].d < d[v]) {
				d[v] = g[u][i].d; // the distance from/to the set, not the source
				q.emplace(v, d[v]);
			}
		}
	}
	return res;
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	g.resize(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		g[u].emplace_back(v, c);
		g[v].emplace_back(u, c);
	}
	vis.resize(n + 1);
	d.resize(n + 1, 0x7fffffff);
	cout << prim(1) << "\n";

	return 0;
}