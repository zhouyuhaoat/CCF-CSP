/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-26 20:13:03
 * 	modified: 	2024-05-28 13:29:26
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
// https://codeleading.com/article/79944313334/
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int inf = 0x3fffffff;
const int maxv = 710, maxe = 18210;

class maxflow {
	struct edge {
		int u, v, cap, cost, next;
		edge() {
		}
		edge(int u, int v, int cap, int cost, int next) : u(u), v(v), cap(cap), cost(cost), next(next) {
		}
	} e[maxe];
	bool vis[maxv];
	int head[maxv], dis[maxv], SLK[maxv];
	int cnt = 0, st, en;
	bool modlabel() {
		int delta = inf;
		for (int i = 0; i <= en; i++) {
			if (!vis[i] && SLK[i] < delta) {
				delta = SLK[i];
				SLK[i] = inf;
			}
		}
		if (delta == inf) {
			return false;
		}
		for (int i = 0; i <= en; i++) {
			if (vis[i]) {
				dis[i] += delta;
			}
		}
		return true;
	}
	int augment(int u, int flow, int pre) {
		if (u == en) {
			_mincost += flow * dis[st];
			return flow;
		}
		vis[u] = true;
		int rest = flow;
		for (int i = head[u]; ~i; i = e[i].next) {
			int v = e[i].v;
			if (!vis[v] && e[i].cap) {
				int temp = dis[v] + e[i].cost - dis[u];
				if (temp == 0) {
					int delta = augment(v, min(rest, e[i].cap), u);
					if (delta > 0) {
						rest -= delta;
						e[i].cap -= delta;
						e[i ^ 1].cap += delta;
					}
					if (rest == 0) {
						return flow;
					}
				} else if (temp < SLK[v]) {
					SLK[v] = temp;
				}
			}
		}
		return flow - rest;
	}

  public:
	int _maxflow = 0, _mincost = 0;
	maxflow(int st, int en) : st(st), en(en) {
		memset(head, -1, sizeof(head));
	}
	void addedge(int u, int v, int cap, int cost) {
		e[cnt] = edge(u, v, cap, cost, head[u]), head[u] = cnt++;
		e[cnt] = edge(v, u, 0, -cost, head[v]), head[v] = cnt++;
	}
	void costflow() {
		for (int i = 0; i <= en; i++) {
			dis[i] = 0;
			SLK[i] = inf;
		}
		do {
			int ret = 0;
			do {
				_maxflow += ret;
				memset(vis, 0, sizeof(vis));
				ret = augment(st, inf, -1);
			} while (ret);
		} while (modlabel());
	}
};

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	int st = 0, en = 7 * n + 1;
	maxflow g(st, en);
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
	g.costflow();
	cout << g._mincost << "\n";
}