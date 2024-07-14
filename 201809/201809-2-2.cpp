/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-17 15:56:43
 * 	modified: 	2024-07-13 19:22:31
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

const int maxn = 1e6 + 1;

int d[maxn];

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	for (int i = 0; i < 2 * n; i++) {
		int l, r;
		cin >> l >> r;
		++d[l], --d[r];
	}
	int cnt = 0;
	for (int i = 1; i < maxn; i++) {
		if ((d[i] = d[i] + d[i - 1]) == 2) {
			++cnt;
		}
	}
	cout << cnt << "\n";

	return 0;
}