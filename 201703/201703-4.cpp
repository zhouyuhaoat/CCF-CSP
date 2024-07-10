/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 21:45:42
 * 	modified: 	2024-07-09 21:29:15
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <numeric>
#include <queue>

using namespace std;

struct edge {
	int u, v, d;
	edge(int u, int v, int d) : u(u), v(v), d(d) {
	}
	friend bool operator<(edge a, edge b) {
		return a.d > b.d;
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

void joint(int a, int b) {
	int fa = find(a), fb = find(b);
	if (fa != fb) {
		f[fa] = fb;
	}
}

int kruskal(int n, int m) {
	f.resize(n + 1);
	iota(f.begin(), f.end(), 0);
	int res;
	while (!e.empty()) {
		edge t = e.top();
		e.pop();
		joint(t.u, t.v);
		if (find(1) == find(n)) {
			res = t.d;
			break;
		}
	}
	return res;
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		e.emplace(a, b, c);
	}
	cout << kruskal(n, m) << "\n";

	return 0;
}