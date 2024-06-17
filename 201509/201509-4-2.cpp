/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-07 22:07:14
 * 	modified: 	2024-06-02 11:31:54
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class scc {
	int n, cid;	   // component id
	vector<int> s; // stack: (reverse) topological order
	vector<bool> vis;
	map<int, int> cnt;		   // component size
	vector<vector<int>> g, gt; // t: transpose, reverse

  public:
	scc(int n) : n(n), vis(n), g(n), gt(n) {
	}
	void addedge(int u, int v) {
		g[u].emplace_back(v);
		gt[v].emplace_back(u);
	}
	void dfs(int u) {
		vis[u] = true;
		for (auto v : g[u]) {
			if (!vis[v]) {
				dfs(v);
			}
		}
		s.emplace_back(u);
	}
	void dfst(int u) {
		vis[u] = true;
		++cnt[cid];
		for (auto v : gt[u]) {
			if (!vis[v]) {
				dfst(v);
			}
		}
	}
	int kosaraju() {
		cid = 0;
		for (int i = 1; i < n; i++) {
			if (!vis[i]) {
				dfs(i);
			}
		}
		fill(vis.begin(), vis.end(), false);
		for (int i = s.size() - 1; i >= 0; i--) {
			if (!vis[s[i]]) {
				++cid;
				dfst(s[i]);
			}
		}
		int res = 0;
		for (auto it : cnt) {
			res += it.second * (it.second - 1) / 2;
		}
		return res;
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
	cout << g.kosaraju() << "\n";

	return 0;
}