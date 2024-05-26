/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 11:13:45
 * 	modified: 	2024-05-26 13:40:05
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

const int mod = 1e9 + 7, maxs = 1 << 7;
long long n, m, trans[maxs][maxs], res[maxs][maxs];

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
	long long mat[maxs][maxs] = {0};
	for (int i = 0; i < maxs; i++) {
		for (int k = 0; k < maxs; k++) {
			long long t = a[i][k];
			for (int j = 0; j < maxs; j++) {
				mat[i][j] += t * b[k][j];
				mat[i][j] %= mod;
			}
		}
	}
	for (int i = 0; i < maxs; i++) {
		for (int j = 0; j < maxs; j++) {
			a[i][j] = mat[i][j];
		}
	}
}

int main(int argc, char const *argv[]) {

	cin >> n >> m;
	for (int s = 0; s < 1 << m; s++) {
		dfs(s, s, 0, 0);
	}
	for (int i = 0; i < maxs; i++) {
		for (int j = 0; j < maxs; j++) {
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
	// row 1: empty -> row n: full -> row (n + 1): empty
	cout << res[0][(1 << m) - 1] << "\n";

	return 0;
}