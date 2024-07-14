/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 22:21:28
 * 	modified: 	2024-07-14 11:23:05
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
	long long res = 0;
	for (int i = 0; i < n; i++) {
		int k, t;
		cin >> k >> t;
		if (k == 0) {
			res += t;
		} else {
			long long temp = res;
			temp %= (r + y + g);
			while (true) {
				if (temp >= t) {
					temp -= t;
					switch (k) {
						case 1:
							k = 3;
							t = g;
							break;
						case 2:
							k = 1;
							t = r;
							break;
						case 3:
							k = 2;
							t = y;
							break;
					}
				} else {
					t -= temp;
					break;
				}
			}
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
	}
	cout << res << "\n";

	return 0;
}