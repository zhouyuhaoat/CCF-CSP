/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-15 16:56:30
 * 	modified: 	2024-07-15 16:58:34
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	int tot = 0, id = 0, sub = -1;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		int pre = t;
		for (int j = 0; j < m; j++) {
			int a;
			cin >> a;
			t += a;
		}
		tot += t;
		if (pre - t > sub) {
			sub = pre - t;
			id = i + 1;
		}
	}
	cout << tot << " " << id << " " << sub << "\n";

	return 0;
}