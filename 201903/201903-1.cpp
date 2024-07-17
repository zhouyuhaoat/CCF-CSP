/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-14 16:59:29
 * 	modified: 	2024-07-14 22:37:21
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

bool isfloat(float x) {
	return x != (int)x;
}

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	int d[n];
	for (int i = 0; i < n; i++) {
		cin >> d[i];
	}
	float m[3] = {d[0], d[n - 1], d[n / 2]};
	if (!(n & 1)) {
		m[2] = (m[2] + d[n / 2 - 1]) / 2.0;
	}
	sort(m, m + 3, greater<float>());
	for (int i = 0; i < 3; i++) {
		if (isfloat(m[i])) {
			// m[i] = round(m[i] * 10) / 10.0;
			cout << fixed << setprecision(1) << m[i];
			// built-in rounding mechanism
			// 1. round in cmath
			// 2. + 0.5 is ineffective for negative float
		} else {
			cout << (int)m[i]; // @important!
		}
		i < 2 ? cout << " " : cout << "\n";
	}

	return 0;
}