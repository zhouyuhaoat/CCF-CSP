/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-16 14:52:40
 * 	modified: 	2024-07-16 15:03:02
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

bool judge(int n) {
	if (n % 7 == 0) {
		return true;
	}
	while (n != 0) {
		if (n % 10 == 7) {
			return true;
		}
		n /= 10;
	}
	return false;
}

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	int cnt[4] = {0}, num = 0;
	while (++num <= n) {
		if (judge(num)) {
			++cnt[(num - 1) % 4];
			++n;
		}
	}
	for (int i = 0; i < 4; i++) {
		cout << cnt[i] << "\n";
	}

	return 0;
}