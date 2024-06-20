/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-06-19 13:21:14
 * 	modified: 	2024-06-20 16:47:15
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#pragma GCC optimize(3, "inline")
#include <bitset>
#include <iostream>

using namespace std;

const int maxm = 1024, maxb = 32;

int m;

class Vector {
  public:
	bitset<maxm> vec;
};

class Matrix {
  public:
	bitset<maxm> mat[maxm];
	Matrix operator*(const Matrix &t) const { // Matrix * Matrix
		Matrix res;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				if (t.mat[i][j]) {
					res.mat[i] ^= mat[j];
				}
			}
		}
		return res;
	}
	Vector operator*(const Vector &t) const { // Matrix * Vector
		Vector res;
		for (int i = 0; i < m; i++) {
			if (t.vec[i]) {
				// (Vector^T) * (Matrix^T) = (Matrix^T) * (Vector^T)
				res.vec ^= mat[i];
			}
		}
		return res;
	}
} A[maxb];

int main(int argc, char const *argv[]) {

	cin >> m;
	for (int i = 0; i < m; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < m; j++) {
			A[0].mat[j][i] = s[j] == '1';
		}
	}
	Vector b;
	string s;
	cin >> s;
	for (int j = 0; j < m; j++) {
		b.vec[j] = s[j] == '1';
	}
	for (int i = 1; i < maxb; i++) {
		A[i] = A[i - 1] * A[i - 1]; // no transpose
	}
	int n;
	cin >> n;
	while (n--) {
		int k;
		cin >> k;
		Vector ans = b;
		for (int i = 0; i < maxb; i++) {
			if (k >> i & 1) {
				// Matrix * Vector = (Vector^T) * (Matrix^T)
				// (Vector^T) * (Matrix^T) = (Matrix^T) * (Vector^T)
				ans = A[i] * ans; // inverse matrix
			}
		}
		for (int i = 0; i < m; i++) {
			cout << ans.vec[i];
		}
		cout << "\n";
	}

	return 0;
}