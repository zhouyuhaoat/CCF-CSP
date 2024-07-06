/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 16:55:02
 * 	modified: 	2024-06-20 16:56:50
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
	int cnt = 0;
	if (n >= 3) {
		for (int i = 1; i < n - 1; i++) {
			if (d[i] > d[i - 1] && d[i] > d[i + 1]) {
				++cnt;
			} else if (d[i] < d[i - 1] && d[i] < d[i + 1]) {
				++cnt;
			}
		}
	}
	cout << cnt << "\n";

	return 0;
}