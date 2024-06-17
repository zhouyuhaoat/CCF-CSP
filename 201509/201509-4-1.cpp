/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-07 21:52:53
 * 	modified: 	2024-06-02 11:43:19
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class scc { // strongly connected component
  private:
	int n, dts = 0; // dfs time stamp
	stack<int> s;
	vector<bool> ins;	  // whether in stack
	vector<int> dfn, low; // dfn: dfs number; low: low link
	vector<vector<int>> g;

  public:
	int res = 0;
	scc(int n) : n(n), ins(n), dfn(n), low(n), g(n) {
	}
	void addedge(int u, int v) {
		g[u].emplace_back(v);
	}
	void dfs() {
		for (int i = 1; i < n; i++) {
			if (dfn[i] == 0) {
				tarjan(i);
			}
		}
	}
	void tarjan(int u) {
		dfn[u] = low[u] = ++dts;
		s.emplace(u);
		ins[u] = true;
		for (auto v : g[u]) {
			if (!dfn[v]) {
				tarjan(v);
				low[u] = min(low[u], low[v]);
			} else if (ins[v]) {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (dfn[u] == low[u]) {
			int cnt = 1; // component size
			while (s.top() != u) {
				ins[s.top()] = false;
				s.pop();
				++cnt;
			}
			ins[s.top()] = false;
			s.pop();
			res += cnt * (cnt - 1) / 2;
		}
	}
};

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	scc g(n + 1);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		g.addedge(a, b);
	}
	g.dfs();
	cout << g.res << "\n";

	return 0;
}