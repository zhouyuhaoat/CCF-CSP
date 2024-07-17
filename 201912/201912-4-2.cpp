/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-16 20:24:41
 * 	modified: 	2024-07-16 21:10:51
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

const int maxn = 505, maxm = 10005;

int lat;
vector<int> chain[maxn], g[maxm];

struct op {
	int t, id;
	vector<int> c; // directly route the chain
	bool operator<(const op &tmp) const {
		return t > tmp.t;
	}
};
priority_queue<op> q;

void eval(int t) {
	while (!q.empty()) {
		op u = q.top();
		if (u.t > t) {
			break;
		}
		for (int v : g[u.id]) {
			vector<int> &a = chain[v], &b = u.c;
			if (a.size() < b.size() || (a.size() == b.size() && b.back() < a.back())) {
				a = b;
				q.emplace(op{u.t + lat, v, b});
			}
		}
		q.pop(); // pop out if not break
	}
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	// Genesis Block of blockchain
	for (int i = 1; i <= n; i++) {
		chain[i].emplace_back(0);
	}
	while (m--) {
		int u, v;
		cin >> u >> v;
		if (u == v) { // self-loop
			continue;
		}
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}
	int k;
	cin >> lat >> k;
	getchar();
	for (int i = 1; i <= k; i++) {
		string s;
		getline(cin, s);
		stringstream ss(s);
		int a[3], cnt = 0;
		while (ss >> a[cnt]) {
			++cnt;
		}
		if (cnt == 3) {
			eval(a[1]);
			chain[a[0]].emplace_back(a[2]);
			q.emplace(op{a[1] + lat, a[0], chain[a[0]]});
		} else {
			eval(a[1]);
			cout << chain[a[0]].size();
			for (int it : chain[a[0]]) {
				cout << " " << it;
			}
			cout << "\n";
		}
	}

	return 0;
}