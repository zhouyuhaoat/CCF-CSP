/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 22:21:19
 * 	modified: 	2024-07-12 23:17:04
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int n, sum = 0;
	int last = -1, cnt = 0;
	while (cin >> n && n != 0) {
		++cnt;
		if (n == 1) {
			++sum;
			last = n;
		} else {
			if (last == 1 || cnt == 1) {
				last = 2;
			} else {
				last += 2;
			}
			sum += last;
		}
	}
	cout << sum << "\n";

	return 0;
}