/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-28 14:19:11
 * 	modified: 	2024-05-28 14:36:25
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int inf = 0x3fffffff;
const int maxv = 710, maxe = 18210;

class maxflow {
	struct etype {
		int v, cap, cost;
		etype *next, *pair;
		etype() {
		}
		etype(int v, int cap, int cost, etype *next) : v(v), cap(cap), cost(cost), next(next) {
		}
	} *e[maxe];
	bool vis[maxv];
	int mincost = 0, en, pi = 0;
	etype *pe = new etype[maxe];
	int augment(int u, int flow) {
		if (u == en) {
			mincost += pi * flow;
			return flow;
		}
		vis[u] = true;
		int rest = flow;
		for (etype *i = e[u]; i; i = i->next) {
			if (i->cap != 0 && i->cost == 0 && !vis[i->v]) {
				int d = augment(i->v, min(rest, i->cap));
				i->cap -= d, i->pair->cap += d, rest -= d;
				if (rest == 0) {
					return flow;
				}
			}
		}
		return flow - rest;
	}
	bool modlabel() {
		int d = inf;
		for (int i = 0; i < en; i++) { // also can i <= en
			if (vis[i]) {
				for (etype *j = e[i]; j; j = j->next) {
					if (j->cap > 0 && !vis[j->v] && j->cost < d) {
						d = j->cost;
					}
				}
			}
		}
		if (d == inf) {
			return false;
		}
		for (int i = 0; i < en; i++) { // also can i <= en
			if (vis[i]) {
				for (etype *j = e[i]; j; j = j->next) {
					j->cost -= d;
					j->pair->cost += d;
				}
			}
		}
		pi += d;
		return true;
	}

  public:
	maxflow(int en) : en(en) {
	}
	void addedge(int u, int v, int cap, int cost) {
		e[u] = new (pe++) etype(v, cap, cost, e[u]);
		e[v] = new (pe++) etype(u, 0, -cost, e[v]);
		e[u]->pair = e[v];
		e[v]->pair = e[u];
	}
	int zkw() {
		do {
			do {
				memset(vis, 0, sizeof(vis));
			} while (augment(0, inf));
		} while (modlabel());
		return mincost;
	}
};

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	int st = 0, en = 7 * n + 1;
	maxflow g(en);
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
	cout << g.zkw() << "\n";

	return 0;
}