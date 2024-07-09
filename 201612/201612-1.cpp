/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 20:14:41
 * 	modified: 	2024-07-07 14:20:50
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	vector<int> d(n);
	for (int i = 0; i < n; i++) {
		cin >> d[i];
	}
	sort(d.begin(), d.end());
	int can = d[n / 2];
	int lt = 0, gt = 0;
	for (int i = 0; i < n; i++) {
		if (d[i] < can) {
			++lt;
		} else if (d[i] > can) {
			++gt;
		}
	}
	lt == gt ? cout << can << "\n" : cout << "-1\n";

	return 0;
}