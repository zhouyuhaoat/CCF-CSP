/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-03 08:42:24
 * 	modified: 	2024-05-26 20:02:13
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <numeric>
#include <queue>

using namespace std;

struct edge {
	int u, v, c;
	edge(int u, int v, int c) : u(u), v(v), c(c) {
	}
	friend bool operator<(edge a, edge b) {
		return a.c > b.c;
	}
};

vector<int> f;
priority_queue<edge> e; // greedy, priority by the cost

int find(int x) { // disjoint set union
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

int kruskal(int n, int m) { // minimum spanning tree
	f.resize(n + 1);
	iota(f.begin(), f.end(), 0);
	int res = 0, cnt = 0;
	while (!e.empty()) {
		edge t = e.top();
		e.pop();
		int fu = find(t.u), fv = find(t.v);
		// for each edge, whether the endpoints belong to the same tree, otherwise creating a cycle
		if (fu != fv) { // joins two distinct trees in the forest
			f[fu] = fv; // merging the two trees
			res += t.c;
			++cnt;
		}
	}
	return res;
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		e.emplace(u, v, c);
	}
	cout << kruskal(n, m) << "\n";

	return 0;
}