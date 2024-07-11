/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-10 17:51:37
 * 	modified: 	2024-07-11 08:24:14
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <bitset>
#include <iostream>

using namespace std;

const int maxn = 1010;
bitset<maxn> f[maxn], g[maxn];
// update and query relationships between nodes

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		f[a][b] = 1, g[b][a] = 1; // direct
	}
	for (int i = 1; i <= n; i++) {
		f[i][i] = 1, g[i][i] = 1; // self
	}
	// transitive closure
	for (int j = 1; j <= n; j++) { // indirect
		for (int i = 1; i <= n; i++) {
			if (f[i][j] == 1) {
				f[i] |= f[j]; // merge
			}
		}
	}
	// all reachable relationships: direct + indirect
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (f[i][j] == 1) {
				g[j][i] = 1; // transpose all relationships
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		f[i] |= g[i]; // merge: bi-direction
	}
	int res = 0;
	for (int i = 1; i <= n; i++) {
		if ((int)f[i].count() == n) {
			++res;
		}
	}
	cout << res;

	return 0;
}