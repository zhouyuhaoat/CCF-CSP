/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-02 21:51:42
 * 	modified: 	2024-05-24 22:07:31
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	int cnt = 0;
	map<int, bool> e;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		if (e[a - 1]) {
			++cnt;
		}
		if (e[a + 1]) {
			++cnt;
		}
		e[a] = true;
	}
	cout << cnt << "\n";

	return 0;
}