/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-06-19 14:27:56
 * 	modified: 	2024-07-06 11:24:20
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
// official solution, with bug: Segmentation Fault
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

const int N = 511, P = 6, B = 60013, H = 600011, S = 67, inf = 0x3F3F3F3F;

int n, m, p;

namespace hash {
	struct Data {
		int fath[P + 1], swit, hash_save;
		int calc_hash() const {
			int val = 0;
			for (int i = 0; i < p; i++) {
				val = val * (i + 1) + fath[i];
			}
			return (val << p) | swit;
		}
		int hash() {
			return hash_save = calc_hash();
		}
		int hash() const {
			return calc_hash();
		}
		bool link(int s) {
			bool new_swit = false;
			int fath_link = 0;
			for (int i = p - 1; i >= 0; i--) {
				new_swit |= (swit >> fath[i]) & ((s >> i) & 1);
				swit &= ~(((s >> i) & 1) << fath[i]);
				fath_link |= ((s >> i) & 1) << fath[i];
			}
			for (int i = p - 1; i >= 0; i--) {
				fath[i + 1] = ((fath_link >> fath[i]) & 1 ? 0 : fath[i] + 1); // parenthetic
			}
			swit = (swit << 1) | new_swit;
			return !(swit >> p);
		}
		void print(const char *end = "\n") const {
			printf("(");
			for (int i = 0; i <= p; i++) {
				printf("%d,", fath[i]);
			}
			for (int i = 0; i <= p; i++) {
				printf("%d", (swit >> i) & 1);
			}
			printf(",%6d)%s", hash(), end);
		}
	} ds;
	int pbuc, head[H];
	struct Buc {
		Data val;
		int next;
	} buc[B + 10];
	void init() {
		pbuc = 0;
		memset(buc, 0, sizeof(buc));
	}
	void ins(int ha, const Data &da) {
		int bu = ha % H;
		buc[++pbuc] = (Buc){da, head[bu]};
		head[bu] = pbuc;
		/*printf("%4d:", pbuc);
		da.print();*/
	}
	void dfs(int a = 0) {
		if (a == p) {
			return ins(ds.hash(), ds);
		}
		for (int i = 0; i < a; i++) {
			if (ds.fath[i] == i) {
				ds.fath[a] = i;
				dfs(a + 1);
			}
		}
		ds.fath[a] = a;
		dfs(a + 1);
		ds.swit |= (1 << a);
		dfs(a + 1);
		ds.swit &= ~(1 << a);
	}
	int look(Data &a) {
		for (int i = head[a.hash()]; i; i = buc[i].next) {
			if (a.hash_save == buc[i].val.hash_save) {
				return i;
			}
		}
		printf("Error look up\n");
		a.print();
		return 0;
	}
} // namespace hash

namespace dp {
	int &pbuc = hash::pbuc;
	int last, begin_sta, user[B], mig[B][S], price[N][S], links[N][P + 3], graph[N], rec[N][B];
	bool is_user[N], used[N][B];
	void gen_user() {
		for (int i = 1; i <= pbuc; i++) {
			hash::ds = hash::buc[i].val;
			hash::ds.swit |= 1;
			user[i] = hash::look(hash::ds);
		}
	}
	void gen_mig() {
		for (int i = 1; i <= pbuc; i++) {
			for (int j = 0; j < (1 << p); j++) {
				hash::ds = hash::buc[i].val;
				if (!hash::ds.link(j)) {
					mig[i][j] = -1;
				} else {
					mig[i][j] = hash::look(hash::ds);
				}
			}
		}
	}
	void init_graph() {
		memset(price, 0, sizeof(price));
		memset(graph, 0, sizeof(graph));
		memset(links, -1, sizeof(links));
		last = 0;
		for (int i = 1; i <= n; i++) {
			if (is_user[i] = (getchar() == '1')) {
				last = i;
			}
		}
		for (int i = 1; i <= m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			graph[v] |= 1 << (v - u - 1);
			links[v][v - u - 1] = w;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = graph[i]; j; j = (j - 1) & graph[i]) {
				for (int k = 0; k < p; k++) {
					if ((j >> k) & 1) {
						price[i][j] += links[i][k];
					}
				}
			}
		}
	}
	int dp(int a, int s) {
		if (s == -1) {
			return inf;
		}
		if (a >= last && hash::buc[s].val.swit == 1) {
			return 0;
		}
		if (a >= n) {
			return inf;
		}
		if (used[a][s]) {
			return rec[a][s];
		}
		used[a][s] = true;
		int tmp = (mig[s][0] != -1 ? dp(a + 1, is_user[a + 1] ? user[mig[s][0]] : mig[s][0]) : inf);
		int gra = graph[a + 1], *pri = price[a + 1];
		for (int i = gra; i; i = (i - 1) & gra) {
			if (mig[s][i] != -1) {
				tmp = std::min(tmp, dp(a + 1, is_user[a + 1] ? user[mig[s][i]] : mig[s][i]) + pri[i]);
			}
		}
		return rec[a][s] = tmp;
	}
	void calc_dp() {
		if (last == 0) {
			printf("0\n");
			return;
		}
		memset(used, 0, sizeof(used));
		for (int i = 0; i <= p; i++) {
			hash::ds.fath[i] = i;
		}
		hash::ds.swit = 0;
		begin_sta = hash::look(hash::ds);
		int ans = dp(0, begin_sta);
		if (ans >= inf) {
			printf("Error\n");
		} else {
			printf("%d\n", ans);
		}
	}
} // namespace dp

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &p);
		hash::init();
		hash::dfs();
		dp::gen_user();
		dp::gen_mig();
		dp::init_graph();
		dp::calc_dp();
	}
	return 0;
}