/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-16 17:55:51
 * 	modified: 	2024-07-16 21:08:35
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <cstring>
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

const int maxn = 510, maxm = 20010;

int lat; // latency
int h[maxn], e[maxm], ne[maxm], idx;
// persistent linked list: data + index
vector<vector<int>> chain;
int blc[maxn]; // index to (block)chain

struct op {
	int t, id, pid, rid; // p: parent; r: route
	// id in id and pid: node id or number
	// id in rid: index to chain
	op(int t, int id, int pid, int rid) : t(t), id(id), pid(pid), rid(rid) {
	}
	bool operator<(const op &tmp) const {
		return t > tmp.t;
	}
};
priority_queue<op> q;

void add(int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void eval() { // evaluate
	op u = q.top();
	q.pop();
	// reference: avoid copy data
	vector<int> &a = chain[blc[u.id]], &b = chain[u.rid]; // itself & route
	if (b.size() > a.size() || (b.size() == a.size() && b.back() < a.back())) {
		blc[u.id] = u.rid; // update index
		for (int i = h[u.id]; ~i; i = ne[i]) {
			int v = e[i];
			if (v != u.pid && v != u.id) { // do not route back and itself
				q.emplace(u.t + lat, v, u.id, u.rid);
			}
		}
	}
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	// Genesis Block of blockchain
	chain.emplace_back(vector<int>{0});
	memset(h, -1, sizeof(h));
	while (m--) {
		int a, b;
		cin >> a >> b;
		add(a, b), add(b, a);
	}
	int k;
	cin >> lat >> k;
	getchar();
	while (k--) {
		string s;
		getline(cin, s);
		stringstream ss(s);
		int a[3], cnt = 0;
		while (ss >> a[cnt]) {
			++cnt;
		}
		if (cnt == 3) {
			// a[0] = node id; a[1] = time; a[2] = block id
			while (!q.empty() && q.top().t <= a[1]) {
				eval();
			}
			// 1. copy main chain 2. add block to chain 3. update index
			// persistent: copy chain since the chain may be indexed by other node
			chain.emplace_back(chain[blc[a[0]]]);
			chain.back().emplace_back(a[2]);
			blc[a[0]] = chain.size() - 1;
			for (int i = h[a[0]]; ~i; i = ne[i]) {
				int v = e[i];
				if (v != a[0]) { // do not route itself
					q.emplace(a[1] + lat, v, a[0], blc[a[0]]);
					// actually route is the index
				}
			}
		} else {
			// a[0] = node id; a[1] = time
			while (!q.empty() && q.top().t <= a[1]) {
				eval();
			}
			cout << chain[blc[a[0]]].size();
			for (auto x : chain[blc[a[0]]]) {
				cout << " " << x;
			}
			cout << "\n";
		}
	}

	return 0;
}