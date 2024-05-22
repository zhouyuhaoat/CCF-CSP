/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-09-28 15:55:52
 * 	modified: 	2024-05-21 20:54:53
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	int res = 0, maxcnt = 0;
	map<int, int> cnt;
	for (int i = 0; i < n; i++) {
		int s;
		cin >> s;
		if (maxcnt < ++cnt[s]) {
			maxcnt = cnt[s];
			res = s;
		} else if (maxcnt == cnt[s] && res > s) {
			res = s;
		}
	}
	cout << res << "\n";

	return 0;
}