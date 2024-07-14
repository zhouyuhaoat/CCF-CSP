/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 22:21:28
 * 	modified: 	2024-07-14 11:43:18
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <queue>

using namespace std;

struct edge {
	int u, v, t;
	friend bool operator<(edge a, edge b) {
		return a.t > b.t;
	}
};

vector<int> f;
priority_queue<edge> e;

int find(int x) {
	int a = x;
	while (x != f[x]) {
		x = f[x];
	}
	while (a != f[a]) {
		int z = a;
		a = f[a];
		f[z] = x;
	}
	return x;
}

int kruskal(int n, int m) {
	f.resize(n + 1);
	for (int i = 0; i < n; i++) {
		f[i] = i;
	}
	int res = 0, cnt = 0;
	while (!e.empty()) {
		edge t = e.top();
		e.pop();
		int fu = find(t.u), fv = find(t.v);
		if (fu != fv) {
			f[fu] = fv;
			++cnt;
			res = max(res, t.t);
			if (cnt == n - 1) {
				break;
			}
		}
	}
	return res;
}

int main(int argc, char const *argv[]) {

	int n, m, root;
	cin >> n >> m >> root;
	for (int i = 0; i < m; i++) {
		int u, v, t;
		cin >> u >> v >> t;
		e.emplace(edge{u, v, t});
	}
	cout << kruskal(n, m) << "\n";

	return 0;
}