/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-15 16:59:46
 * 	modified: 	2024-07-15 17:21:43
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	int tot = 0;
	set<int> fall;
	vector<bool> flag(n);
	for (int i = 0; i < n; i++) {
		int m;
		cin >> m;
		int pre;
		cin >> pre;
		int sub = 0;
		for (int j = 1; j < m; j++) {
			int a;
			cin >> a;
			if (a <= 0) {
				sub += a; // sub: negative
			} else {
				if (pre + sub > a) {
					fall.emplace(i); // fall -> falls
					flag[i] = true;
				}
				pre = a;
				sub = 0;
			}
		}
		tot += pre + sub;
	}
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		bool ok = true;
		for (int j = 0; j < 3; j++) {
			if (!flag[(i + j) % n]) {
				ok = false;
				break;
			}
		}
		if (ok) {
			++cnt;
		}
	}
	cout << tot << " " << fall.size() << " " << cnt << "\n";

	return 0;
}