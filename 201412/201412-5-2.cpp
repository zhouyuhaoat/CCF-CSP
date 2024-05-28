/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-27 18:13:28
 * 	modified: 	2024-05-28 13:03:57
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <queue>

using namespace std;

const int inf = 0x3fffffff;

class maxflow {
	struct edge {
		int v, c, w;
		edge(int v, int c, int w) : v(v), c(c), w(w) {
		}
	};
	vector<bool> vis;	// spfa: whether a vertex is in the queue
	vector<int> h, sta; // sta: current arc optimization/path scanning/pruned search
	vector<edge> e;
	vector<vector<int>> g;
	bool spfa(int s, int t) { // shortest path faster algorithm: Bellman-Ford with queue
		fill(vis.begin(), vis.end(), false);
		fill(h.begin(), h.end(), inf);
		h[s] = 0;
		vis[s] = true;
		queue<int> q;
		q.emplace(s);
		while (!q.empty()) {
			int u = q.front();
			for (auto i : g[u]) {
				auto [v, c, w] = e[i];
				if (c > 0 && h[u] + w < h[v]) {
					h[v] = h[u] + w; // level graph
					if (!vis[v]) {
						vis[v] = true;
						q.emplace(v);
					}
				}
			}
			vis[u] = false;
			q.pop();
		}
		return h[t] < inf;
	}
	int dfs(int u, int t, int flow) {
		if (u == t) {
			return flow;
		}
		int rest = flow; // rest flow = flow - used flow
		vis[u] = true;
		for (int &cur = sta[u]; cur < (int)g[u].size(); cur++) {
			int i = g[u][cur]; // cur != i
			auto [v, c, w] = e[i];
			if (c > 0 && h[u] + w == h[v] && !vis[v]) {
				int temp = dfs(v, t, min(rest, c)); // threshold
				e[i].c -= temp;
				e[i ^ 1].c += temp;
				rest -= temp;
				cost += temp * e[i].w;
			}
			if (rest == 0) {
				break;
			}
		}
		vis[u] = false;
		return flow - rest;
	}

  public:
	int flow = 0, cost = 0;
	maxflow(int n) : vis(n), h(n), sta(n), g(n) {
	}
	void addedge(int u, int v, int c, int w) {
		g[u].emplace_back(e.size());
		e.emplace_back(v, c, w);
		g[v].emplace_back(e.size());
		e.emplace_back(u, 0, -w);
	}
	void dinic(int s, int t) {
		while (spfa(s, t)) {
			fill(sta.begin(), sta.end(), 0);
			flow += dfs(s, t, inf);
		}
	}
};

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	int st = 0, en = 7 * n + 1;
	maxflow g(en + 1);
	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= 7; j++) {
			int a;
			cin >> a;
			g.addedge(st, i * 7 + j, a, 0);
		}
		for (int j = 1; j <= 7; j++) {
			int b;
			cin >> b;
			g.addedge(i * 7 + j, en, b, 0);
		}
		int v, w;
		cin >> v >> w;
		for (int j = 1; j <= 7; j++) {
			g.addedge(i * 7 + j, i * 7 + j % 7 + 1, v, w);
		}
	}
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		for (int j = 1; j <= 7; j++) {
			g.addedge((u - 1) * 7 + j, (v - 1) * 7 + j, inf, c);
			g.addedge((v - 1) * 7 + j, (u - 1) * 7 + j, inf, c);
		}
	}
	g.dinic(st, en);
	cout << g.cost << "\n";

	return 0;
}