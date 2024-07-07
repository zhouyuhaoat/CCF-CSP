/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 16:55:06
 * 	modified: 	2024-07-06 14:17:20
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <climits>
#include <iostream>
#include <queue>

using namespace std;

class graph {
	struct edge {
		int to, d;
	};
	struct node {
		int id, d;
		node(int id, int d) : id(id), d(d) {
		}
		friend bool operator<(node a, node b) {
			return a.d > b.d;
		}
	};

  public:
	vector<bool> vis;
	vector<int> d, c;
	vector<vector<edge>> g;
	graph(int n) : vis(n), d(n), c(n), g(n) {
	}
	void addedge(int a, int b, int c) {
		g[a].push_back({b, c});
		g[b].push_back({a, c});
	}
	void dijkstra(int sta) {
		fill(d.begin(), d.end(), INT_MAX);
		fill(c.begin(), c.end(), INT_MAX);
		d[sta] = 0, c[sta] = 0;
		priority_queue<node> q;
		q.emplace(sta, 0);
		while (!q.empty()) {
			node t = q.top();
			q.pop();
			if (vis[t.id]) {
				continue;
			}
			int u = t.id;
			vis[u] = true;
			for (int i = 0; i < (int)g[u].size(); i++) {
				int v = g[u][i].to;
				if (!vis[v]) {
					if (d[u] + g[u][i].d < d[v]) {
						d[v] = d[u] + g[u][i].d;
						c[v] = g[u][i].d;
						q.emplace(v, d[v]);
					} else if (d[u] + g[u][i].d == d[v]) {
						c[v] = min(c[v], g[u][i].d);
					}
				}
			}
		}
	}
};

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	graph g(n + 1);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		g.addedge(a, b, c);
	}
	g.dijkstra(1);
	int res = 0;
	for (int i = 1; i < (int)g.c.size(); i++) {
		res += g.c[i];
	}
	cout << res << "\n";

	return 0;
}