/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-11 22:10:32
 * 	modified: 	2024-07-11 22:52:28
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int maxn = 510, maxl = 1010, inf = 1e6;

class graph {
	struct edge {
		int type, to, len;
		edge(int type, int to, int len) : type(type), to(to), len(len) {
		}
	};
	struct node {
		int id, d, last; // last: the last segment of small road
		node(int id, int d, int last) : id(id), d(d), last(last) {
		}
		friend bool operator<(node a, node b) {
			return a.d > b.d;
		}
	};
	vector<edge> g[maxn];
	bool vis[maxn][maxl];

  public:
	int dis[maxn][maxl]; // vertex decontruction
	// dis[i][j]: the shortest distance from 1 to i with last j small road
	void addedge(int t, int a, int b, int c) {
		g[a].emplace_back(t, b, c);
		g[b].emplace_back(t, a, c);
	}
	void dijkstra(int sta, int end) {
		memset(dis, 0x3f, sizeof(dis));
		dis[sta][0] = 0;
		priority_queue<node> q;
		q.emplace(sta, 0, 0);
		while (!q.empty()) {
			node t = q.top();
			q.pop();
			if (vis[t.id][t.last]) {
				continue;
			}
			vis[t.id][t.last] = true;
			int u = t.id;
			for (int i = 0; i < (int)g[u].size(); i++) {
				int v = g[u][i].to, last = t.last;
				if (g[u][i].type == 1) {
					last += g[u][i].len;
					if (last <= 1000) { // pruning
						if (dis[v][last] > t.d + (last * last - t.last * t.last)) {
							dis[v][last] = t.d + (last * last - t.last * t.last);
							if (dis[v][last] <= inf) { // pruning
								q.emplace(v, dis[v][last], last);
							}
						}
					}
				} else {
					if (dis[v][0] > t.d + g[u][i].len) {
						dis[v][0] = t.d + g[u][i].len;
						if (dis[v][0] <= inf) {
							q.emplace(v, dis[v][0], 0);
						}
					}
				}
			}
		}
	}
};

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	graph g;
	for (int i = 0; i < m; i++) {
		int t, a, b, c;
		cin >> t >> a >> b >> c;
		g.addedge(t, a, b, c);
	}
	g.dijkstra(1, n);
	int res = inf;
	for (int i = 0; i <= maxl; i++) {
		res = min(res, g.dis[n][i]);
	}
	cout << res << "\n";

	return 0;
}