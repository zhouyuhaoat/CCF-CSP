/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 19:01:58
 * 	modified: 	2024-06-01 20:21:20
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

int md[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
				 {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int isleap(int y) {
	return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0);
}

int main(int argc, char const *argv[]) {

	int y, d;
	cin >> y >> d;
	int dd = 1;
	for (int m = 1; m <= 12; m++) {
		if (dd + md[isleap(y)][m] > d) {
			cout << m << "\n" << d - dd + 1 << "\n";
			break;
		} else {
			dd += md[isleap(y)][m];
		}
	}

	return 0;
}