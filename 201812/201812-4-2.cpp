/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 22:21:28
 * 	modified: 	2024-07-14 11:45:13
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <climits>
#include <iostream>
#include <queue>

using namespace std;

class graph {
	struct node {
		int v, d;
		node(int v, int d) : v(v), d(d) {
		}
		friend bool operator<(node a, node b) {
			return a.d > b.d;
		}
	};

  public:
	vector<bool> vis;
	vector<int> d;
	vector<vector<node>> g;
	graph(int n) : vis(n), d(n), g(n) {
	}
	void addnode(int u, int v, int c) {
		g[u].emplace_back(v, c);
		g[v].emplace_back(u, c);
	}
	int prim(int s) {
		fill(d.begin(), d.end(), INT_MAX);
		d[s] = 0;
		priority_queue<node> q;
		q.emplace(s, 0);
		int res = 0;
		while (!q.empty()) {
			node t = q.top();
			q.pop();
			int u = t.v;
			if (vis[u]) {
				continue;
			}
			vis[u] = true;
			res = max(res, d[u]);
			for (int i = 0; i < (int)g[u].size(); i++) {
				int v = g[u][i].v;
				if (!vis[v] && g[u][i].d < d[v]) {
					d[v] = g[u][i].d;
					q.emplace(v, d[v]);
				}
			}
		}
		return res;
	}
};

int main(int argc, char const *argv[]) {

	int n, m, root;
	cin >> n >> m >> root;
	graph g(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		g.addnode(u, v, c);
	}
	cout << g.prim(1) << "\n";

	return 0;
}