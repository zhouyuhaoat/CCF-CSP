/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 20:14:41
 * 	modified: 	2024-07-07 12:49:14
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	vector<int> bts = {3500, 3500 + 1500, 3500 + 4500, 3500 + 9000, 3500 + 35000, 3500 + 55000, 3500 + 80000};
	vector<int> tax = {0, 3, 10, 20, 25, 30, 35, 45};
	vector<int> ats;
	ats.emplace_back(bts[0]);
	for (int i = 1; i < 7; i++) {
		ats.emplace_back(ats[i - 1] + bts[i] - bts[i - 1] - (bts[i] - bts[i - 1]) * tax[i] / 100);
	}
	ats.emplace_back(0x3fffffff);
	int t;
	cin >> t;
	int rate = 0;
	while (t > ats[rate]) {
		++rate;
	}
	int sal = 0;
	if (rate == 0) {
		sal = t;
	} else {
		sal = bts[rate - 1] + (t - ats[rate - 1]) * 100 / (100 - tax[rate]);
	}
	cout << sal << "\n";

	return 0;
}