/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 19:54:33
 * 	modified: 	2024-07-11 22:47:15
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
/*
with bug
example:
4 4
0 1 3 100
1 1 2 10
1 3 2 1
1 2 4 1
output: 121
but should be 104
121 = (10 + 1) ^ 2
104 = 100 + (1 + 1) ^ 2
the last segment of small road matters
*/
#include <climits>
#include <cmath>
#include <iostream>
#include <queue>

using namespace std;

class graph {
	struct edge {
		int type, to, len;
		edge(int type, int to, int len) : type(type), to(to), len(len) {
		}
	};
	struct node {
		int id;
		long long d;
		node(int id, long long d) : id(id), d(d) {
		}
		friend bool operator<(node a, node b) {
			return a.d > b.d;
		}
	};

  public:
	vector<int> d;
	vector<long long> res;
	vector<bool> vis;
	vector<vector<edge>> g;
	graph(int n) : d(n + 1), res(n + 1), vis(n + 1), g(n + 1) {
	}
	void addedge(int t, int a, int b, int c) {
		g[a].emplace_back(t, b, c);
		g[b].emplace_back(t, a, c);
	}
	void dijkstra(int sta, int end) {
		fill(res.begin(), res.end(), 0x3fffffff);
		res[sta] = 0;
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
					long long c = res[u];
					if (g[u][i].type == 1) {
						c += pow(d[u] + g[u][i].len, 2) - pow(d[u], 2);
					} else {
						c += g[u][i].len;
					}
					if (c < res[v]) {
						res[v] = c;
						if (g[u][i].type == 1) {
							d[v] = d[u] + g[u][i].len;
						} else {
							d[v] = 0;
						}
						q.emplace(v, res[v]);
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
		int t, a, b, c;
		cin >> t >> a >> b >> c;
		g.addedge(t, a, b, c);
	}
	g.dijkstra(1, n);
	cout << g.res[n] << "\n";

	return 0;
}