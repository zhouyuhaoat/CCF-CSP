/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-06-18 14:27:33
 * 	modified: 	2024-06-20 16:46:00
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#pragma GCC optimize(3, "inline")
#include <iostream>

using namespace std;

const int maxm = 1024, maxb = 32;

struct bit {
	unsigned int b[maxb]; // bianry representation: index + mask
	void set1(int x) {
		b[x >> 5] |= 1u << (x & 31); // x >> 5 = x / 32; x & 31 = x % 32
	}
	void set0(int x) {
		b[x >> 5] &= ~(1u << (x & 31)); // ~: NOT
	}
	int get(int x) {
		return b[x >> 5] >> (x & 31) & 1; // only 1, don't need 1u
	}
	// Hamming Weight or population count
	// 1. __builtin_popcount()/std::popcount()
	// 2. bitset<size_t>().count()
	// 3.1. Parallel Bit Deposits/Parallel Bitwise Operations
	// 3.2. SWAR: SIMD within a Register
	// 3.3. SIMD: Single Instruction Multiple Data
	bool parity() { // parity bit
		int s = 0;
		for (int i = 0; i < maxb; i++) {
			int x = b[i];
			x ^= x >> 1; // ^: XOR
			x ^= x >> 2;
			x ^= x >> 4;
			x ^= x >> 8;
			x ^= x >> 16;
			s ^= x;
		}
		return s & 1;
	}
	// XOR/OR: as addition for 0/1, usually XOR since modulo 2
	bit operator&(const bit &t) const { // AND, as multiplication for 0/1
		bit res;
		for (int i = 0; i < maxb; i++) {
			res.b[i] = b[i] & t.b[i];
		}
		return res;
	}
};

struct mat {
	int row, col;
	bit h[maxm], v[maxm]; // horizontal; vertical
	mat operator*(const mat &t) const {
		mat res;
		res.row = row, res.col = t.col;
		for (int i = 0; i < res.row; i++) {
			for (int j = 0; j < res.col; j++) {
				if ((h[i] & t.v[j]).parity()) { // matrix[i][j] = 1
					res.h[i].set1(j), res.v[j].set1(i);
				} else {
					res.h[i].set0(j), res.v[j].set0(i);
				}
			}
		}
		return res;
	}
} A[maxb], b; // matrix (power array); (column) vector

int main(int argc, char const *argv[]) {

	int m;
	cin >> m;
	A[0].row = m, A[0].col = m;
	b.row = m, b.col = 1;
	for (int i = 0; i < m; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < m; j++) {
			if (s[j] == '1') {
				A[0].h[i].set1(j), A[0].v[j].set1(i);
			}
		}
	}
	for (int i = 1; i < maxb; i++) { // preprocessing
		A[i] = A[i - 1] * A[i - 1];	 // A[i] = A^(2^i)
	}
	string s;
	cin >> s;
	for (int i = 0; i < m; i++) {
		if (s[i] == '1') {
			b.h[i].set1(0), b.v[0].set1(i);
		}
	}
	int n;
	cin >> n;
	while (n--) {
		int k;
		cin >> k;
		mat ans = b;
		// Matrix Exponentiation or Matrix Fast Power
		for (int i = 0; i < maxb; i++) {
			if (k >> i & 1) { // k & (1 << i)
				ans = A[i] * ans;
			}
		}
		for (int i = 0; i < m; i++) {
			cout << ans.h[i].get(0);
		}
		cout << "\n";
	}

	return 0;
}