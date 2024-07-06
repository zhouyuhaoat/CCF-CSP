/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-05 17:51:04
 * 	modified: 	2024-07-06 11:04:16
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 510, maxp = 6, maxs = 1 << 6 * 3;

int p, fa[7];
// connectivity: state compression
// each 1-bit & 3-bit, all p-bit & 3p-bit
// 3-bit & 3p-bit: for minimum representation
// each 3-bit's base is increased by 1
int w[maxn][maxp], es[maxn], ec[maxn][1 << maxp];
int dpc[2][maxs], dps[2][maxs], dpcnt[2];
// 2: scroll array, odd and even, state compression
int trans[maxs][1 << maxp];

int get(int state, int k) {
	// state: multiple 3-bit segment
	// k: index to 3-bit segment
	// why 3-bit segment? 2^3 > 6, for minimum representation
	// each 3-bit segment represents 1-bit for connectivity
	return state >> k * 3 & 7; // (k * 3)
}

void update(int i, int state, int cost) {
	if (state == -1) {
		return;
	}
	// dpc[vertex][state] = min cost to get state
	// dps[vertex][index to state] = state that can be get
	// dpcnt[vertex] = count of all state that can be get
	if (dpc[i][state] != -1) {
		dpc[i][state] = min(dpc[i][state], cost);
	} else {
		dpc[i][state] = cost;
		dps[i][dpcnt[i]++] = state;
	}
}

void clear(int k) { // scroll array
	for (int i = 0; i < dpcnt[k]; i++) {
		dpc[k][dps[k][i]] = -1;
	}
	dpcnt[k] = 0;
}

// path compression + recursion
int find(int x) {
	if (fa[x] != x) {
		fa[x] = find(fa[x]);
	}
	return fa[x];
}

// add edge set's state to the minimum representation of state
// state transition: trans[origin state][added state] = after state
// origin state: 3p-bit; added state: p-bit; after state: 3p-bit
int get_state(int state, int k) {
	if (k == 1) {
		k = 0;
	}
	if (trans[state][k / 2] >= -1) {
		return trans[state][k / 2];
	}
	for (int i = 0; i <= p; i++) {
		if (get(state, i) || (k >> i & 1)) {
			fa[i] = i;
		} else {
			fa[i] = -1;
		}
	}
	for (int i = 0; i <= p; i++) {
		if (get(state, i)) {
			for (int j = i + 1; j <= p; j++) {
				if (get(state, j) == get(state, i)) {
					fa[find(j)] = find(i);
				}
			}
		}
	}
	for (int i = 0; i <= p; i++) {
		if (k >> i & 1) {
			for (int j = i + 1; j <= p; j++) {
				if (k >> j & 1) {
					fa[find(j)] = find(i);
				}
			}
			// break;
		}
	}
	// the first point must either be unselected
	// or belong to a set with a size of at least 2
	if (fa[0] != -1) {
		bool flag = false;
		for (int i = 1; i <= p; i++) {
			if (fa[i] != -1 && find(i) == find(0)) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			return trans[state][k / 2] = -1;
		}
	}
	int res = 0;
	for (int i = 1, base = 1; i <= p; i++) {
		if (!get(res, i - 1) && fa[i] != -1) {
			res += base << (i - 1) * 3;
			for (int j = i + 1; j <= p; j++) {
				if (!get(res, j - 1) && fa[j] != -1 && find(j) == find(i)) {
					res += base << (j - 1) * 3;
				}
			}
			++base; // encode base
		}
	}
	return trans[state][k / 2] = res;
}

int main(int argc, char const *argv[]) {

	int t;
	cin >> t;
	memset(trans, -0x3f, sizeof(trans));
	while (t--) {
		int n, m;
		cin >> n >> m >> p;
		string s;
		cin >> s;
		memset(w, -1, sizeof(w));
		for (int i = 0; i < m; i++) {
			int u, v, ww;
			cin >> u >> v >> ww;
			w[u][v - u - 1] = ww;
			// w[vertex][gap between vertices] = weight or cost
		}
		memset(es, 0, sizeof(es));
		memset(ec, 0, sizeof(ec));
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < p; j++) {
				if (w[i][j] != -1) {
					es[i] += 1 << j;
					// es[vertex] = edge state of vertex
				}
			}
			for (int j = 0; j < 1 << p; j++) {
				if ((j & es[i]) == j) {
					// j in es[i]: subset or contained
					// all state that can be get
					for (int k = 0; k < p; k++) {
						if (j >> k & 1) {
							ec[i][j] += w[i][k];
							// ec[vertex][state] = cost
						}
					}
				}
			}
		}
		memset(dpc, -1, sizeof(dpc));
		update(1, 0, 0); // initialization
		int res = 0x3fffffff, user = s.rfind('1') + 1;
		for (int i = 1; i <= n; i++) {
			clear((i + 1) & 1);
			for (int j = 0; j < dpcnt[i & 1]; j++) {
				int state = dps[i & 1][j], cost = dpc[i & 1][state];
				for (int k = 0; k < 1 << p; k++) {
					if ((k & es[i]) != k) {
						continue;
					}
					if (s[i - 1] == '1' && get(state, 0) == 0 && k == 0) {
						continue; // user can't be selected
					}
					update((i + 1) & 1, get_state(state, k * 2 + 1), cost + ec[i][k]);
				}
				if (i >= user && state == 1) { // all users are selected
					res = min(res, cost);
				}
			}
		}
		cout << res << "\n";
	}

	return 0;
}