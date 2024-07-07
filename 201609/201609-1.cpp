/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 16:55:06
 * 	modified: 	2024-07-06 16:16:58
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int n, last;
	cin >> n >> last;
	int res = -1;
	for (int i = 1; i < n; i++) {
		int next;
		cin >> next;
		res = max(res, abs(next - last));
		last = next;
	}
	cout << res << "\n";

	return 0;
}