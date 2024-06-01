/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-30 09:32:56
 * 	modified: 	2024-06-01 19:40:30
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

const int maxv = 1e5 + 10;

struct edge {
	int v, w;
};

struct query {
	int u, v; // u -> v
	long long ans;
};

int p[maxv]; // price
query q[maxv];
vector<edge> g[maxv];

int bel[maxv], cnt[maxv], dis1[maxv], dis2[maxv], f[maxv]; // for centroid
// bel: belong to which tree, tree id
// cnt: number of nodes in subtree, size
// dis1: distance from nodes in subtree
// dis2: distance from all nodes in tree to the root
int fa[maxv][18], pri[maxv][18], w[maxv], wsum[maxv]; // doubling array, segment tree
// fa: father or ancestor up to 2^k
// pri: lowest price up to 2^k
// w: weight of the edge from last vertex
// wsum: sum of weight of the path from root
long long up[maxv], down[maxv];
// up: to root; down: from root

class tree {
  private:
	int id = -1, h = 1;	 // tree id; doubling scale
	vector<int> n, subn; // node, subtree node
	vector<query *> qry; // query
	vector<tree *> subt; // subtree
	void dfs1(int u) {
		cnt[u] = 1;
		dis1[u] = 0;
		for (auto e : g[u]) {
			int v = e.v;
			if (bel[v] >= 0 && f[u] != v) { // can not reach outside root, a rooted tree
				f[v] = u;
				dfs1(v);
				cnt[u] += cnt[v];
				// @important!
				// NOT cnt[u] = cnt[v] + 1, otherwise Time Limit Exceeded
				// NOT dis1[u] = dis1[v] + cnt[v], however Accepted
				dis1[u] += dis1[v] + cnt[v]; // trace one edge back
			}
		}
	}
	void dfs2(int u) {
		if (f[u] == -1) { // root in dfs1
			dis2[u] = dis1[u];
		} else {
			dis2[u] = dis2[f[u]] + n.size() - 2 * cnt[u];
			// two part: father/parent + children/subtree
			// father/parent: + n.size() - cnt[u] - 2
			// children/subtree: - cnt[u]
		}
		for (auto e : g[u]) {
			int v = e.v;
			if (f[v] == u) { // same dfs tree
				dfs2(v);
			}
		}
	}
	int centroid() {
		for (auto id : n) {
			f[id] = -1;
		}
		dfs1(n[0]), dfs2(n[0]);
		int cen = n[0];
		for (auto id : n) {
			if (dis2[id] < dis2[cen]) {
				// minimum distance from all nodes in tree rooted at centroid
				cen = id;
			}
		}
		return cen;
	}
	void dfs3(int u, int id) { // tree id: one subtree of centroid
		bel[u] = id;
		subn.emplace_back(u);
		subt[id]->addnode(u);
		for (auto e : g[u]) {
			auto [v, ww] = e;
			if (bel[v] >= 0 && fa[u][0] != v) {
				fa[v][0] = u;
				w[v] = ww;
				dfs3(v, id);
			}
		}
	}

  public:
	tree() {
		++id;
	}
	void addnode(int u) {
		n.emplace_back(u);
	}
	void addquery(query *q) {
		qry.emplace_back(q);
	}
	void solve() {
		if (qry.empty()) {
			return;
		}
		while ((1 << h) <= (int)n.size()) {
			++h;
		}
		int cen = centroid();
		bel[cen] = -1;			// centroid = root
		for (auto e : g[cen]) { // divide all subtree of centroid
			auto [v, ww] = e;
			if (bel[v] >= 0) {
				bel[v] = subt.size();
				subt.emplace_back(new tree());
				fa[v][0] = cen;
				w[v] = ww;
				dfs3(v, subt.size() - 1);
			}
		}
		for (auto id : n) {
			pri[id][0] = p[id];
		}
		fa[cen][0] = cen;
		for (int k = 1; k <= h; k++) {
			for (auto id : n) {
				int anc = fa[id][k - 1]; // ancestor
				// 2^k = 2^(k - 1) + 2^(k - 1)
				fa[id][k] = fa[anc][k - 1];
				pri[id][k] = min(pri[id][k - 1], pri[anc][k - 1]);
			}
		}
		w[cen] = wsum[cen] = up[cen] = down[cen] = 0;
		for (auto id : subn) {
			down[id] = down[fa[id][0]] + (long long)w[id] * pri[fa[id][0]][h];
			wsum[id] = w[id] + wsum[fa[id][0]];
			// down: root -> current = root -> father/parent + father/parent -> current
			int next = id; // next to the root with the lowest price
			for (int k = h; k >= 0; k--) {
				if (pri[next][k] >= p[id]) {
					next = fa[next][k];
				}
			}
			up[id] = up[next] + (long long)p[id] * (wsum[id] - wsum[next]);
			// up: current -> root = current -> next + next -> root
		}
		for (auto q : qry) {
			if (bel[q->u] == bel[q->v] && bel[q->u] >= 0) { // same subtree: divide and conquer
				subt[bel[q->u]]->addquery(q);
			} else if (bel[q->u] != bel[q->v]) { // different subtree: up + down, u -> root -> v
				q->ans = up[q->u];
				int minw = pri[q->u][h], next = q->v;
				// price during up possibly lower than price during down
				for (int k = h; k >= 0; k--) {
					if (pri[fa[next][k]][h] <= minw) {
						next = fa[next][k];
					}
				}
				q->ans += (long long)minw * wsum[next];
				q->ans += down[q->v] - down[next];
				// up + down => up + min + down
			}
		}
		for (auto id : subt) { // divide and conquer
			id->solve();
		}
	}
} t;

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
		t.addnode(i);
	}
	for (int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].emplace_back(edge{v, w});
		g[v].emplace_back(edge{u, w});
	}
	for (int i = 1; i <= m; i++) {
		cin >> q[i].u >> q[i].v;
		// t.addquery(q + i); // pointer
		t.addquery(&q[i]);
	}
	t.solve();
	for (int i = 1; i <= m; i++) {
		cout << q[i].ans << "\n";
	}

	return 0;
}