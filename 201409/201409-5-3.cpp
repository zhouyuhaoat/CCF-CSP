/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-26 08:47:21
 * 	modified: 	2024-05-26 13:10:37
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <cstring>
#include <iostream>

using namespace std;

const int mod = 1e9 + 7, maxs = 1 << 7;

struct mat {
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
		mat res, bas;
		for (int i = 0; i < maxs; i++) {
			res.v[i][i] = 1;
		}
		for (int i = 0; i < maxs; i++) {
			for (int j = 0; j < maxs; j++) {
				bas.v[i][j] = v[i][j] % mod;
			}
		}
		while (x != 0) {
			if (x & 1) {
				res = res * bas;
			}
			x >>= 1;
			bas = bas * bas;
		}
		return res;
	}
} trans;

long long n;
int m, s, none = 7; // s: states; none: special flag, not 0 and -1
int b[7 + 2], bt[7 + 2], bb[7 + 2];
// b: block type; b-: binary representation
// t: top row; b: bottom row

/*
4 block types:
L:         L':        inverse L:    inverse L':
 __            __      __ __         __ __
|  |__      __|  |    |   __|       |__   |
|__ __|    |__ __|    |__|             |__|
*/

// none: no place in the current column, since the place of the previous/next column
// 0: place in the current column
// 1: place in the next column
// -1: place in the previous column
// [2]: top/bottom row
int block[5][2][4] = {{{none}, {none}},			  // no block
					  {{0, 1, none}, {0, none}},  // inverse L
					  {{0, none}, {-1, 0, none}}, // L'
					  {{0, 1, none}, {1, none}},  // inverse L'
					  {{0, none}, {0, 1, none}}}; // L

void place() {
	for (int i = 0; i <= m + 1; i++) {
		bt[i] = bb[i] = 0; // all empty
	}
	for (int i = 0; i <= m; i++) { // place blocks
		int t = b[i];			   // block type
		int *pt = block[t][0];	   // place in the top/bottom row
		while (*pt != none) {	   // none: end of place
			++bt[i + *(pt++)];	   // placing in the previous/current/next column
		}
		int *pb = block[t][1];
		while (*pb != none) {
			++bb[i + *(pb++)];
		}
	}
	if (bt[0] > 0 || bt[m + 1] > 0 || bb[0] > 0 || bb[m + 1] > 0) { // out of bound
		return;
	}
	for (int i = 1; i <= m; i++) {
		if (bt[i] > 1 || bb[i] > 1) { // repeat place
			return;
		}
	}
	int st = 0, sb = 0; // s-: state of binary representation
	for (int i = 1; i <= m; i++) {
		st = (st << 1) | bt[i];
		sb = (sb << 1) | bb[i];
	}
	++trans.v[(s - 1) - st][sb];
}

void search(int c) {
	if (c > m) { // enumerate all columns of the top row
		place();
		return;
	}
	for (int i = 0; i < 5; i++) { // 4 block types + none
		b[c] = i;
		// supposedly place a block in the current column
		search(c + 1);
	}
}

int main(int argc, char const *argv[]) {

	cin >> n >> m;
	s = 1 << m;
	search(1);
	trans = trans ^ n;
	cout << trans.v[0][0] << "\n";

	return 0;
}