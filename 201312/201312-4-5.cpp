/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-05-21 22:19:50
 * 	modified: 	2024-05-22 10:10:21
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	const int mod = 1e9 + 7;
	long long s2 = 1, s23 = 0, s02 = 0, s023 = 0, s012 = 0, s0123 = 0; // i = 1
	// s2 + 2 = s2, s2 + 3 = s23, s2 + 0 = s02
	// s23 + 3 = s23, s23 + 0 = s023
	// s02 + 0/2 = s02, s02 + 3 = s023, s02 + 1 = s012
	// s023 + 0/3 = s023, s023 + 1 = s0123
	// s012 + 1/2 = s012, s012 + 3 = s0123
	// [s2, s23, s02, s023, s012, s0123] *= state transition matrix
	// [1   0    0    0     0     0]
	// [1   1    0    0     0     0]
	// [1   0    2    0     0     0]
	// [0   1    1    2     0     0]
	// [0   0    1    0     2     0]
	// [0   0    0    1     1     2]
	for (int i = 2; i <= n; i++) {
		s0123 = (s023 + s012 + 2 * s0123) % mod;
		s012 = (s02 + 2 * s012) % mod;
		s023 = (s23 + s02 + 2 * s023) % mod;
		s02 = (s2 + 2 * s02) % mod;
		s23 = (s2 + s23) % mod;
		s2 = 1 % mod;
	}
	cout << s0123;

	return 0;
}