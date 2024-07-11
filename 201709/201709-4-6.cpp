/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-10 17:57:30
 * 	modified: 	2024-07-11 08:30:45
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

const int maxn = 1000, maxm = 10000;

struct star {
	int h[maxn + 1], e[maxm + 1], ne[maxm + 1];
	bool vis[maxn + 1];
	void addedge(int idx, int u, int v) {
		e[idx] = v, ne[idx] = h[u], h[u] = idx;
	}
};

class tarjan {		// strongly connected component
	int dts = 0, n; // dfs time stamp
	stack<int> s;
	vector<bool> ins;	  // whether in stack
	vector<int> dfn, low; // dfn: dfs number; low: low link
	void dfs(star &fs, int u) {
		dfn[u] = low[u] = ++dts;
		s.emplace(u);
		ins[u] = true;
		for (int e = fs.h[u]; e > 0; e = fs.ne[e]) {
			int v = fs.e[e];
			if (!dfn[v]) { // tree edge
				dfs(fs, v);
				low[u] = min(low[u], low[v]);
			} else if (ins[v]) { // back edge
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (low[u] == dfn[u]) {
			while (s.top() != u) {
				ins[s.top()] = false;
				s.pop();
				++size[u];
			}
			ins[s.top()] = false;
			s.pop();
			++size[u];
		}
	}

  public:
	vector<int> size; // component size
	tarjan(int n) : n(n), ins(n + 1), dfn(n + 1), low(n + 1), size(n + 1) {
	}
	void operator()(star &fs) { // dfs on the whole graph
		for (int i = 1; i <= n; ++i) {
			if (!dfn[i]) {
				dfs(fs, i);
			}
		}
	}
};

class graph {
	int n;
	queue<int> q;
	void bfs(star &f, int start) {
		memset(f.vis, 0, sizeof(f.vis));
		f.vis[start] = true;
		q.emplace(start);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int e = f.h[u]; e > 0; e = f.ne[e]) {
				int v = f.e[e];
				if (!f.vis[v]) {
					f.vis[v] = true;
					q.emplace(v);
				}
			}
		}
	}

  public:
	graph(int n) : n(n) {
	}
	star fs[2];
	void add(int i, int u, int v) {
		fs[0].addedge(i, u, v);
		fs[1].addedge(i, v, u);
	}
	bool reachable(int u) { // reachable to all nodes
		bfs(fs[0], u);
		bfs(fs[1], u);
		for (int i = 1; i <= n; ++i) {
			if (!fs[0].vis[i] && !fs[1].vis[i]) {
				return false;
			}
		}
		return true;
	}
};

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	graph g(n);
	for (int i = 1; i <= m; ++i) {
		int a, b;
		cin >> a >> b;
		g.add(i, a, b);
	}
	tarjan tj(n);
	tj(g.fs[0]); // traverse: node contraction
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		if (tj.size[i] != 0) { // each component
			res += g.reachable(i) * tj.size[i];
		}
	}
	cout << res << "\n";

	return 0;
}