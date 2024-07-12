/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 19:52:54
 * 	modified: 	2024-07-11 16:56:54
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int n, k;
	cin >> n >> k;
	int d[n];
	for (int i = 0; i < n; i++) {
		cin >> d[i];
	}
	bool flag[n] = {false};
	int out = 0, num = 0;
	while (true) {
		for (int i = 0; i < n; i++) {
			if (!flag[i]) {
				++num;
				if (num % k == 0 || num % 10 == k) {
					flag[i] = true;
					++out;
				}
			}
			if (out == n - 1) {
				break;
			}
		}
		if (out == n - 1) {
			break;
		}
	}
	for (int i = 0; i < n; i++) {
		if (!flag[i]) {
			cout << i + 1 << "\n";
			break;
		}
	}

	return 0;
}