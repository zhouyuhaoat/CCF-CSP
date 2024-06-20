/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-06-19 11:24:58
 * 	modified: 	2024-06-20 16:46:24
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#pragma GCC optimize(3, "inline")
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

const int maxm = 1024, maxb = 32;

struct matrix {
	int row, col;
	vector<bitset<maxm>> mat;
	matrix(int _row = 0, int _col = 0) : row(_row), col(_col) {
		mat.resize(row);
	}
	matrix operator*(const matrix &t) { // this * t => t * this, since this = t
		matrix res(this->row, t.col);
		for (int i = 0; i < res.row; i++) {
			for (int j = 0; j < t.row; j++) { // for each row
				if (mat[i][j]) {
					res.mat[i] ^= t.mat[j]; // XOR: addition modulo 2
				}
			}
		}
		return res;
	}
	matrix transpose() const { // for bitset operation
		matrix res(col, row);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				res.mat[j][i] = mat[i][j];
			}
		}
		return res;
	}
} A[maxb];

bitset<maxm> mul(const bitset<maxm> &a, const matrix &b) { // transposed matrix
	bitset<maxm> res;
	for (int i = 0; i < b.row; i++) {
		res[i] = (a & b.mat[i]).count() & 1; // AND: bitset operation
	}
	return res;
}

int main(int argc, char const *argv[]) {

	int m;
	cin >> m;
	A[0] = matrix(m, m);
	for (int i = 0; i < A[0].row; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < A[0].col; j++) {
			A[0].mat[j][i] = s[j] == '1'; // transposed
		}
	}
	for (int i = 1; i < maxb; i++) {
		A[i] = A[i - 1] * A[i - 1];
		A[i - 1] = A[i - 1].transpose(); // transpose back for bitset operation
	}
	bitset<maxm> b;
	string s;
	cin >> s;
	for (int i = 0; i < m; i++) {
		b[i] = s[i] == '1'; // transposed
	}
	int n;
	cin >> n;
	while (n--) {
		int k;
		cin >> k;
		bitset<maxm> res = b;
		for (int i = 0; i < maxb; i++) {
			if (k >> i & 1) {
				res = mul(res, A[i]); // (A^k * b)^T = b^T * (A^T)^k
			}
		}
		for (int i = 0; i < m; i++) {
			cout << res[i];
		}
		cout << "\n";
	}

	return 0;
}