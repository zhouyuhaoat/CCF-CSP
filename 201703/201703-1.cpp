/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 21:45:42
 * 	modified: 	2024-07-09 21:20:15
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int n, k;
	cin >> n >> k;
	int sum = 0, cnt = 0;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		sum += a;
		if (sum >= k) {
			++cnt;
			sum = 0;
		} else if (i == n - 1) {
			++cnt;
		}
	}
	cout << cnt << "\n";

	return 0;
}