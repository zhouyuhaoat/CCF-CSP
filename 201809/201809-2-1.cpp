/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 22:21:24
 * 	modified: 	2024-07-13 19:19:01
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	map<int, bool> c;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		for (int j = a; j < b; j++) {
			c[j] = true;
		}
	}
	int res = 0;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		for (int j = a; j < b; j++) {
			if (c[j]) {
				++res;
			}
		}
	}
	cout << res << "\n";

	return 0;
}