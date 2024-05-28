/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 13:40:46
 * 	modified: 	2024-05-28 12:10:36
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

const int inf = 0x3fffffff;

class maxflow {
	int n;
	vector<vector<int>> g;			// edge index, like chain-forward star
	vector<tuple<int, int, int>> e; // edge: (vertex, capacity, cost = edge weight); reverse edge: [index ^ 1]
	vector<int> h, pre;
	// johnson's algorithm: the fact/shortest distance from the source to the vertex
	// potential or height for shortest path produced by dijkstra
	// prevent negative edge/cycle produced by the reverse edge
	bool dijkstra(int s, int t) {
		// underlying container: vector
		// greater: heap, priority
		// pair: distance, vertex
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
		q.emplace(0, s);
		vector<int> d(n, inf);
		d[s] = 0;
		fill(pre.begin(), pre.end(), -1);
		while (!q.empty()) {
			auto [du, u] = q.top();
			q.pop();
			if (d[u] < du) { // visited
				continue;
			}
			for (auto i : g[u]) {
				auto [v, c, w] = e[i];
				w += h[u] - h[v]; // potential difference
				if (c > 0 && d[v] > d[u] + w) {
					d[v] = d[u] + w;
					pre[v] = i; // the only miminum cost path
					q.emplace(d[v], v);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			if ((h[i] += d[i]) > inf) { // update the potential
				h[i] = inf;
			}
		}
		return h[t] < inf; // sink reached from source: find the augmenting path
	}

  public:
	maxflow(int n) : n(n), g(n), h(n), pre(n) {
	}
	void addedge(int u, int v, int c, int w) {
		g[u].emplace_back(e.size());
		e.emplace_back(v, c, w);
		g[v].emplace_back(e.size());
		e.emplace_back(u, 0, -w);
	}
	pair<int, int> mcmf(int s, int t) { // minimum cost maximum flow
		int flow = 0, cost = 0;
		while (dijkstra(s, t)) { // whether there is augmenting path
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
			cost += f * h[t]; // cost: potential difference from the source to the sink
		}
		return {flow, cost};
	}
};

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	int st = 0, en = 7 * n + 1;
	maxflow g(en + 1);
	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= 7; j++) { // vertex decomposition by day
			int a;
			cin >> a;
			g.addedge(st, i * 7 + j, a, 0); // source: producer
		}
		for (int j = 1; j <= 7; j++) {
			int b;
			cin >> b;
			g.addedge(i * 7 + j, en, b, 0); // sink: consumer
		}
		int v, w;
		cin >> v >> w;
		for (int j = 1; j <= 7; j++) { // depot: between days of a city
			g.addedge(i * 7 + j, i * 7 + j % 7 + 1, v, w);
		}
	}
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		for (int j = 1; j <= 7; j++) { // road: between cities of a day
			g.addedge((u - 1) * 7 + j, (v - 1) * 7 + j, inf, c);
			g.addedge((v - 1) * 7 + j, (u - 1) * 7 + j, inf, c);
		}
	}
	pair<int, int> res = g.mcmf(st, en);
	cout << res.second << "\n";

	return 0;
}