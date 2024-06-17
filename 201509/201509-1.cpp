/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 19:01:51
 * 	modified: 	2024-06-01 20:20:14
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	int last;
	cin >> last;
	int cnt = 1;
	for (int i = 1; i < n; i++) {
		int next;
		cin >> next;
		if (last != next) {
			++cnt;
		}
		last = next;
	}
	cout << cnt << "\n";

	return 0;
}