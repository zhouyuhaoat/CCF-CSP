/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-06-15 22:21:31
 * 	modified: 	2024-07-14 12:51:40
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

const int inf = 0x3fffffff;

class flow {
	int n;
	vector<vector<int>> g;
	vector<tuple<int, int, int>> e;
	vector<int> h, pre;
	bool dijkstra(int s, int t) {
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
		q.emplace(0, s);
		fill(pre.begin(), pre.end(), -1);
		vector<int> d(n, inf);
		d[s] = 0;
		while (!q.empty()) {
			int du = q.top().first, u = q.top().second;
			q.pop();
			if (d[u] < du) {
				continue;
			}
			for (auto i : g[u]) {
				int v = get<0>(e[i]), c = get<1>(e[i]), w = get<2>(e[i]);
				w += h[u] - h[v];
				if (c > 0 && d[v] > d[u] + w) {
					d[v] = d[u] + w;
					pre[v] = i;
					q.emplace(d[v], v);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			if ((h[i] += d[i]) > inf) {
				h[i] = inf;
			}
		}
		return h[t] != inf;
	}

  public:
	int addflow = 0;
	vector<int> deg; // in & out flow
	flow(int _n) : n(_n), g(_n), h(_n), pre(_n), deg(_n) {
	}
	void addedge(int u, int v, int c, int w) {
		g[u].emplace_back(e.size());
		e.emplace_back(v, c, w);
		g[v].emplace_back(e.size());
		e.emplace_back(u, 0, -w);
	}
	int maxflow(int s, int t) {
		int flow = 0, cost = 0;
		while (dijkstra(s, t)) {
			int f = inf, tt = t;
			vector<int> path;
			while (tt != s) {
				path.emplace_back(pre[tt]);
				f = min(f, get<1>(e[pre[tt]]));
				tt = get<0>(e[pre[tt] ^ 1]);
			}
			for (auto i : path) {
				get<1>(e[i]) -= f;
				get<1>(e[i ^ 1]) += f;
			}
			flow += f;
			cost += f * h[t];
		}
		if (flow != addflow) {
			return -1; // full flow
		} else {
			return cost;
		}
	}
};

int main(int argc, char const *argv[]) {

	int tt, ss, ee;
	cin >> tt >> ss >> ee;
	for (int q = 0; q < tt; q++) {
		int n, m;
		cin >> n >> m;
		int st = 0, en = n + 1, lowflow = 0;
		// lower_bound flow graph
		flow g(en + 1); // vertex, not edge
		for (int i = 0; i < m; i++) {
			int u, v;
			char t;
			cin >> u >> v >> t;
			switch (t) {
				case 'A': // [1, inf]
					g.addedge(u, v, inf, ee);
					g.deg[u]--;
					g.deg[v]++;
					lowflow += ee;
					break;
				case 'B': // [1, 1]
					g.deg[u]--;
					g.deg[v]++;
					lowflow += ee;
					break;
				case 'C': // [0, inf]
					g.addedge(u, v, inf, ee);
					break;
				case 'D': // [0, 1]
					g.addedge(u, v, 1, ee);
					break;
			}
		}
		for (int i = 1; i <= n; i++) {
			if (g.deg[i] > 0) {
				g.addflow += g.deg[i]; // additional flow
				g.addedge(st, i, g.deg[i], 0);
			} else if (g.deg[i] < 0) {
				g.addedge(i, en, -g.deg[i], 0);
			}
		}
		int res = g.maxflow(st, en);
		if (res != -1) {
			res += lowflow;
		}
		cout << res << "\n";
	}

	return 0;
}