/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-03 08:53:14
 * 	modified: 	2024-05-28 14:55:12
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iomanip>
#include <iostream>

using namespace std;

int md[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
				 {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int isleap(int y) {
	return (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0));
}

int main(int argc, char const *argv[]) {

	int a, b, c, y1, y2;
	cin >> a >> b >> c >> y1 >> y2;
	int d = 0;
	for (int y = 1850; y < y1; y++) {
		d += 365 + isleap(y);
	}
	for (int y = y1; y <= y2; y++) {
		int dy = d;
		for (int m = 1; m < a; m++) {
			dy += md[isleap(y)][m];
		}
		int wd = dy % 7 + 1; // weekday of the first day of the month
		int dm = (b - 1) * 7 + (wd >= c ? c + 7 - wd : c - wd);
		if (dm > md[isleap(y)][a]) {
			cout << "none\n";
		} else {
			cout << y << "/" << setfill('0') << setw(2) << a << "/" << setfill('0') << setw(2) << dm << "\n";
		}
		d += 365 + isleap(y);
	}

	return 0;
}