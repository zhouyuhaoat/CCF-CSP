/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-26 13:22:24
 * 	modified: 	2024-05-26 14:01:18
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

const int mod = 1e9 + 7, maxs = 1 << 7;
long long n, m, s, trans[maxs][maxs], res[maxs][maxs];

int place(int s, int c1, int c2) {
	s |= 1 << c1;
	if (c2 != -1) {
		s |= 1 << c2;
	}
	return s;
}

bool isempty(int s, int c) {
	if (c >= 0 && c < m && (s & 1 << c) == 0) {
		return true;
	}
	return false;
}

void dfs(int inis, int nows, int nexts, int c) {
	if (nows == (1 << m) - 1) {
		++trans[inis][nexts];
		return;
	}
	if (!isempty(nows, c)) {
		dfs(inis, nows, nexts, c + 1);
	} else {
		if (isempty(nows, c + 1) && isempty(nexts, c + 1)) {
			dfs(inis, place(nows, c, c + 1), place(nexts, c + 1, -1), c + 2);
		}
		if (isempty(nows, c + 1) && isempty(nexts, c)) {
			dfs(inis, place(nows, c, c + 1), place(nexts, c, -1), c + 2);
		}
		if (isempty(nexts, c) && isempty(nexts, c + 1)) {
			dfs(inis, place(nows, c, -1), place(nexts, c, c + 1), c + 1);
		}
		if (isempty(nexts, c - 1) && isempty(nexts, c)) {
			dfs(inis, place(nows, c, -1), place(nexts, c - 1, c), c + 1);
		}
	}
}

void matmul(long long a[maxs][maxs], long long b[maxs][maxs]) {
	long long mat[s][s] = {0}; // optimization: maxs -> s
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			long long v = 0; // optimization: Locality of Reference
			for (int k = 0; k < s; k++) {
				v += a[i][k] * b[k][j];
				if ((k & 7) == 7) { // optimization
					v %= mod;
				}
			}
			mat[i][j] = v % mod;
		}
	}
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			a[i][j] = mat[i][j];
		}
	}
}

int main(int argc, char const *argv[]) {

	cin >> n >> m;
	s = 1 << m;
	for (int i = 0; i < s; i++) {
		dfs(i, i, 0, 0);
	}
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			res[i][j] = i == j ? 1 : 0;
		}
	}
	--n;
	while (n > 0) {
		if (n & 1) {
			matmul(res, trans);
		}
		n >>= 1;
		matmul(trans, trans);
	}
	cout << res[0][(1 << m) - 1] << "\n";

	return 0;
}