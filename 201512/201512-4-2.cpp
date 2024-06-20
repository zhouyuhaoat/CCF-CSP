/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-06-17 20:24:42
 * 	modified: 	2024-06-18 14:26:57
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

vector<int> f, ep;
vector<set<int>> g;

int find(int x) {
	int a = x;
	while (x != f[x]) {
		x = f[x];
	}
	while (a != f[a]) {
		int z = a;
		a = f[a], f[z] = x;
	}
	return x;
}

bool joint(int a, int b) {
	int fa = find(a), fb = find(b);
	if (fa != fb) {
		f[fa] = fb;
		return true;
	}
	return false;
}

void dfs(int u) { // the path itself
	while (!g[u].empty()) {
		int v = *g[u].begin();
		g[u].erase(v), g[v].erase(u);
		dfs(v);
	}
	ep.emplace_back(u);
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	f.resize(n + 1), g.resize(n + 1);
	iota(f.begin(), f.end(), 0);
	int cntc = 0;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		g[a].insert(b), g[b].insert(a);
		if (joint(a, b)) {
			++cntc;
		}
	}
	int cntd = 0;
	for (int i = 1; i <= n; i++) {
		if (g[i].size() % 2 != 0) {
			++cntd;
		}
	}
	if (cntc == n - 1 && (cntd == 0 || (cntd == 2 && g[1].size() % 2 != 0))) {
		dfs(1);
		for (int i = ep.size() - 1; i >= 0; i--) {
			cout << ep[i];
			i > 0 ? cout << " " : cout << "\n";
		}
	} else {
		cout << "-1\n";
	}

	return 0;
}