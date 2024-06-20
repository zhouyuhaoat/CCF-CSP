/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-06-19 13:11:10
 * 	modified: 	2024-06-20 16:50:58
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#pragma GCC optimize(3, "inline")
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

const int maxm = 1024, maxb = 32, block = 5;

int low[maxb];
bitset<maxm> d[maxb];

void lowbit() { // lowest bit
	for (int i = 1; i < maxb; i++) {
		low[i] = i & 1 ? 0 : low[i >> 1] + 1;
	}
}

struct matrix {
	int row, col;
	vector<bitset<maxm>> mat;
	matrix(int _row = 0, int _col = 0) : row(_row), col(_col) {
		mat.resize(row);
	}
	// Method of Four Russians: boolean matrix multiplication
	// https://www.doc88.com/p-2136480081151.html
	matrix operator*(const matrix &t) {
		matrix res(this->row, t.col);
		for (int l = 0; l < row; l += block) {
			int r = min(l + block, row);
			for (int sta = 1; sta < maxb; sta++) { // state compression
				d[sta] = d[sta - (1 << low[sta])] ^ t.mat[l + low[sta]];
			}
			for (int i = 0; i < row; i++) {
				int v = 0;
				for (int j = l; j < r; j++) {
					v ^= mat[i][j] << (j - l);
				}
				res.mat[i] ^= d[v];
			}
		}
		return res;
	}
	matrix transpose() const {
		matrix res(col, row);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				res.mat[j][i] = mat[i][j];
			}
		}
		return res;
	}
} A[maxb];

bitset<maxm> mul(const bitset<maxm> &a, const matrix &b) {
	bitset<maxm> res;
	for (int i = 0; i < b.row; i++) {
		res[i] = (a & b.mat[i]).count() & 1;
	}
	return res;
}

int main(int argc, char const *argv[]) {

	lowbit();
	int m;
	cin >> m;
	A[0] = matrix(m, m);
	for (int i = 0; i < A[0].row; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < A[0].col; j++) {
			A[0].mat[j][i] = s[j] == '1';
		}
	}
	for (int i = 1; i < maxb; i++) {
		A[i] = A[i - 1] * A[i - 1];
		A[i - 1] = A[i - 1].transpose();
	}
	bitset<maxm> b;
	string s;
	cin >> s;
	for (int i = 0; i < m; i++) {
		b[i] = s[i] == '1';
	}
	int n;
	cin >> n;
	while (n--) {
		int k;
		cin >> k;
		bitset<maxm> res = b;
		for (int i = 0; i < maxb; i++) {
			if (k >> i & 1) {
				res = mul(res, A[i]);
			}
		}
		for (int i = 0; i < m; i++) {
			cout << res[i];
		}
		cout << "\n";
	}

	return 0;
}