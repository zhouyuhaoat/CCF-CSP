/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 22:21:28
 * 	modified: 	2024-07-14 11:22:10
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int r, y, g;
	cin >> r >> y >> g;
	int n;
	cin >> n;
	int res = 0;
	for (int i = 0; i < n; i++) {
		int k, t;
		cin >> k >> t;
		switch (k) {
			case 0:
				res += t;
				break;
			case 1:
				res += t;
				break;
			case 2:
				res += t, res += r;
				break;
		}
	}
	cout << res << "\n";

	return 0;
}