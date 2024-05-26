/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 09:59:47
 * 	modified: 	2024-05-26 12:35:59
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <cstring>
#include <iostream>

using namespace std;

long long n, m;
const int mod = 1e9 + 7, maxs = 1 << 7;
// state compression: bit operation

struct mat { // matrix with multiplication and power
	long long v[maxs][maxs];
	mat() {
		memset(v, 0, sizeof(v));
	}
	mat operator*(const mat &T) const {
		mat res;
		for (int i = 0; i < maxs; i++) {
			for (int k = 0; k < maxs; k++) {
				long long r = v[i][k];
				for (int j = 0; j < maxs; j++) {
					res.v[i][j] += T.v[k][j] * r;
					res.v[i][j] %= mod;
				}
			}
		}
		return res;
	}
	mat operator^(long long x) const {
		mat res, bas; // identity matrix
		for (int i = 0; i < maxs; i++) {
			res.v[i][i] = 1;
		}
		for (int i = 0; i < maxs; i++) {
			for (int j = 0; j < maxs; j++) {
				bas.v[i][j] = v[i][j] % mod;
			}
		}
		while (x != 0) { // fast exponentiation
			if (x & 1) {
				res = res * bas;
			}
			x >>= 1;
			bas = bas * bas;
		}
		return res;
	}
} trans;

int place(int s, int c1, int c2) { // set current column/s to full
	s |= 1 << c1;
	if (c2 != -1) {
		s |= 1 << c2;
	}
	return s; // the state after placing the block, also the now/next state
}

bool isempty(int s, int c) { // current column is empty
	if (c >= 0 && c < m && (s & (1 << c)) == 0) {
		return true;
	}
	return false;
}

/*
4 block types:
L:         L':        inverse L:    inverse L':
 __            __      __ __         __ __
|  |__      __|  |    |   __|       |__   |
|__ __|    |__ __|    |__|             |__|
*/

// initial state, now state, next state, current column
void dfs(int inis, int nows, int nexts, int c) {
	if (nows == (1 << m) - 1) { // all columns are filled
		++trans.v[inis][nexts];
		// the initial state can be transitioned to the next state
		return;
	}
	if (!isempty(nows, c)) {
		dfs(inis, nows, nexts, c + 1);
	} else {
		if (isempty(nows, c + 1) && isempty(nexts, c + 1)) { // inverse L' block
			dfs(inis, place(nows, c, c + 1), place(nexts, c + 1, -1), c + 2);
		}
		if (isempty(nows, c + 1) && isempty(nexts, c)) { // inverse L block
			dfs(inis, place(nows, c, c + 1), place(nexts, c, -1), c + 2);
		}
		if (isempty(nexts, c) && isempty(nexts, c + 1)) { // L block
			dfs(inis, place(nows, c, -1), place(nexts, c, c + 1), c + 1);
		}
		if (isempty(nexts, c - 1) && isempty(nexts, c)) { // L' block
			dfs(inis, place(nows, c, -1), place(nexts, c - 1, c), c + 1);
		}
	}
}

int main(int argc, char const *argv[]) {

	cin >> n >> m;
	for (int s = 0; s < 1 << m; s++) { // enumerate all initial states
		dfs(s, s, 0, 0);
	}
	trans = trans ^ n; // state transition = matrix multiplication
	cout << trans.v[0][0] << "\n";

	return 0;
}