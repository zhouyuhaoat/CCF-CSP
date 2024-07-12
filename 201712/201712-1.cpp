/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 19:51:43
 * 	modified: 	2024-07-11 16:54:35
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	int d[n];
	for (int i = 0; i < n; i++) {
		cin >> d[i];
	}
	int res = 0x3fffffff;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			res = min(res, abs(d[i] - d[j]));
			if (res == 0) {
				break;
			}
		}
		if (res == 0) {
			break;
		}
	}
	cout << res << "\n";

	return 0;
}