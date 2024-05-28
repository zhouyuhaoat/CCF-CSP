/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-25 22:44:05
 * 	modified: 	2024-05-28 13:20:37
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int inf = 0x3fffffff;
const int maxv = 710, maxe = 18210;

class maxflow {
	struct edge {
		int v, c, w, next; // next edge
	} e[maxe];
	int cnt = -1, head[maxv];
	vector<bool> vis;
	vector<int> h, sta;
	bool spfa(int s, int t) {
		fill(vis.begin(), vis.end(), false);
		fill(h.begin(), h.end(), inf);
		h[s] = 0;
		vis[s] = true;
		queue<int> q;
		q.emplace(s);
		while (!q.empty()) {
			int u = q.front();
			for (int i = head[u]; i > -1; i = e[i].next) {
				auto [v, c, w, next] = e[i];
				if (c > 0 && h[u] + w < h[v]) {
					h[v] = h[u] + w;
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
		int rest = flow;
		vis[u] = true;
		for (int &i = sta[u]; i > -1; i = e[i].next) {
			auto [v, c, w, next] = e[i];
			if (c > 0 && h[u] + w == h[v] && !vis[v]) {
				int temp = dfs(v, t, min(rest, c));
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
	maxflow(int n) : vis(n), h(n), sta(n) {
		memset(head, -1, sizeof(head));
	}
	void addedge(int u, int v, int c, int w) {
		e[++cnt] = {v, c, w, head[u]}, head[u] = cnt;
		e[++cnt] = {u, 0, -w, head[v]}, head[v] = cnt;
	}
	void dinic(int s, int t) {
		while (spfa(s, t)) {
			for (int i = 0; i <= t; i++) {
				sta[i] = head[i];
			}
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