/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 22:21:24
 * 	modified: 	2024-07-13 19:16:57
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
	int ans[n];
	ans[0] = (d[0] + d[1]) / 2;
	ans[n - 1] = (d[n - 1] + d[n - 2]) / 2;
	for (int i = 1; i < n - 1; i++) {
		ans[i] = (d[i - 1] + d[i] + d[i + 1]) / 3;
	}
	for (int i = 0; i < n; i++) {
		cout << ans[i];
		i < n - 1 ? cout << " " : cout << "\n";
	}

	return 0;
}