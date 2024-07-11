/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 19:58:30
 * 	modified: 	2024-07-10 16:18:45
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	int sum = 0;
	sum += n / 50 * 7;
	n %= 50;
	sum += n / 30 * 4;
	n %= 30;
	sum += n / 10;
	cout << sum << "\n";

	return 0;
}