/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-14 13:19:01
 * 	modified: 	2024-07-14 13:33:40
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
// https://www.acwing.com/solution/content/237951
#include <cstring>
#include <iostream>

using namespace std;

using ll = long long;

const int maxn = 205, maxm = 805;

// 1-indexed
namespace MCMF {
	const ll flow_INF = 1145141919810ll;
	const ll cost_offset = 1145141919;
	int n, m, s, t;
	struct edge {
		int from, to, nxt;
		ll flow, cost;
		bool origin;
	} e[maxm << 1];
	int cnt;
	int h[maxn];
	int add_edge(int u, int v, ll flow, ll cost, bool directed = true) {
		++m;
		e[++cnt].from = u, e[cnt].to = v, e[cnt].nxt = h[u], e[cnt].flow = flow, e[cnt].cost = cost, e[cnt].origin = 1;
		h[u] = cnt;
		e[++cnt].from = v, e[cnt].to = u, e[cnt].nxt = h[v], e[cnt].flow = directed ? 0 : flow, e[cnt].cost = -cost,
		e[cnt].origin = 0;
		h[v] = cnt;
		return cnt;
	}
	ll get_remain_flow(int no) {
		return e[no].flow;
	}
	int tme;
	int vis[maxn], fa[maxn], fe[maxn], circle[maxn], mark[maxn];
	ll pi[maxn];
	void clr() {
		n = m = s = t = 0, cnt = tme = 1;
		memset(h, 0, sizeof(h));
		memset(vis, 0, sizeof(vis)), memset(fa, 0, sizeof(fa));
		memset(fe, 0, sizeof(fe)), memset(circle, 0, sizeof(circle));
		memset(mark, 0, sizeof(mark)), memset(pi, 0, sizeof(pi));
	}
	void dfs(int u, int fi) {
		fa[u] = e[fi].from, fe[u] = fi;
		mark[u] = 1;
		for (int i = h[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (e[i].origin && !mark[v]) {
				dfs(v, i);
			}
		}
	}
	ll phi(int u) {
		if (mark[u] == tme) {
			return pi[u];
		}
		mark[u] = tme, pi[u] = phi(fa[u]) + e[fe[u]].cost;
		return pi[u];
	}
	ll pushflow(int eg) {
		int rt = e[eg].from, lca = e[eg].to;
		++tme;
		int circle_cnt = 0;
		while (rt) {
			mark[rt] = tme, rt = fa[rt];
		}
		while (mark[lca] ^ tme) {
			mark[lca] = tme, lca = fa[lca];
		}
		ll minflow = e[eg].flow, p = 2, del_u = 0;
		for (int u = e[eg].from; u ^ lca; u = fa[u]) {
			circle[++circle_cnt] = fe[u];
			if (e[fe[u]].flow < minflow) {
				minflow = e[fe[u]].flow, del_u = u, p = 0;
			}
		}
		for (int u = e[eg].to; u ^ lca; u = fa[u]) {
			int ne = fe[u] ^ 1;
			circle[++circle_cnt] = ne;
			if (e[ne].flow < minflow) {
				minflow = e[ne].flow, del_u = u, p = 1;
			}
		}
		circle[++circle_cnt] = eg;
		ll cost = 0;
		for (int i = 1; i <= circle_cnt; ++i) {
			cost += e[circle[i]].cost * minflow;
			e[circle[i]].flow -= minflow, e[circle[i] ^ 1].flow += minflow;
		}
		if (p == 2) {
			return cost;
		}
		int u = e[eg].from, v = e[eg].to;
		if (p == 1) {
			swap(u, v);
		}
		int last_e = eg ^ p, last_u = v;
		while (last_u ^ del_u) {
			last_e ^= 1, --mark[u], swap(fe[u], last_e);
			int nu = fa[u];
			fa[u] = last_u, last_u = u, u = nu;
		}
		return cost;
	}
	void init_sz(int _n) {
		n = _n, m = 0, cnt = 1, tme = 1;
	}
	pair<ll, ll> solve(int _s, int _t) {
		s = _s, t = _t;
		add_edge(t, s, flow_INF, -cost_offset);
		dfs(t, 0), mark[t] = ++tme;
		fa[t] = 0;
		ll cost = 0, flow = 0;
		bool run = 1;
		while (run) {
			run = 0;
			for (int i = 2; i <= cnt; ++i) {
				if (e[i].flow && e[i].cost + phi(e[i].from) - phi(e[i].to) < 0) {
					cost += pushflow(i), run = 1;
				}
			}
		}
		flow = e[cnt].flow;
		return {flow, cost + flow * cost_offset};
	}
} // namespace MCMF

namespace bound_MCMF {
	ll fl[maxn]; // > 0: supply; < 0: demand
	ll supply_sum, base_cost, extra_cost;
	ll ori_edge_lo[maxm];
	int rev_edge_no[maxm];
	int n, S, T;
	void clr() {
		memset(fl, 0, sizeof(fl)), supply_sum = base_cost = extra_cost = 0;
		memset(ori_edge_lo, 0, sizeof(ori_edge_lo));
		memset(rev_edge_no, 0, sizeof(rev_edge_no));
		n = S = T = 0, MCMF::clr();
	}
	void init(int _n) {
		n = _n, MCMF::init_sz(n + 2), S = n + 1, T = n + 2;
	}
	void standard_supply_or_demand(int no, ll val) {
		fl[no] += val;
	}
	void add_edge(int no, int u, int v, ll lo, ll hi, ll cost) {
		fl[u] -= lo, fl[v] += lo, ori_edge_lo[no] = lo;
		base_cost += lo * cost;
		rev_edge_no[no] = MCMF::add_edge(u, v, hi - lo, cost);
	}
	bool solve() {
		for (int i = 1; i <= n; ++i) {
			if (fl[i] > 0) {
				MCMF::add_edge(S, i, fl[i], 0), supply_sum += fl[i];
			} else if (fl[i] < 0) {
				MCMF::add_edge(i, T, -fl[i], 0);
			}
		}
		pair<ll, ll> ans = MCMF::solve(S, T);
		return extra_cost = ans.second, ans.first == supply_sum;
	}
	ll mincost() {
		return base_cost + extra_cost;
	}
	ll get_pi(int u) {
		return MCMF::cost_offset + MCMF::pi[u];
	}
	ll real_flow(int no) {
		return ori_edge_lo[no] + MCMF::get_remain_flow(rev_edge_no[no]);
	}
} // namespace bound_MCMF

int main(int argc, const char *argv[]) {

	int T, S, E;
	cin >> T >> S >> E;
	while (T--) {
		bound_MCMF::clr();
		int n, m;
		cin >> n >> m;
		bound_MCMF::init(n);
		for (int i = 1; i <= m; ++i) {
			int u, v;
			char type;
			cin >> u >> v >> type;
			switch (type) {
				case 'A':
					bound_MCMF::add_edge(i, u, v, 1, MCMF::flow_INF, E);
					break;
				case 'B':
					bound_MCMF::add_edge(i, u, v, 1, 1, E);
					break;
				case 'C':
					bound_MCMF::add_edge(i, u, v, 0, MCMF::flow_INF, E);
					break;
				case 'D':
					bound_MCMF::add_edge(i, u, v, 0, 1, E);
					break;
				default:
					break;
			}
		}
		if (!bound_MCMF::solve()) {
			cout << "-1\n";
		} else {
			cout << bound_MCMF::mincost() << "\n";
		}
	}

	return 0;
}