/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-03 08:34:35
 * 	modified: 	2024-05-26 18:05:39
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct rec {
	int r; // row
	string order;
	double p;
	long long s;
};

int main(int argc, char const *argv[]) {

	vector<rec> d;		// original data
	map<int, bool> can; // cancel
	string order;
	int r = 0;
	while (cin >> order) {
		++r;
		if (order == "cancel") {
			int id;
			cin >> id;
			can[id] = true;
		} else {
			double p;
			long long s;
			cin >> p >> s;
			d.emplace_back(rec{r, order, p, s});
		}
	}
	vector<rec> buy, sell;
	for (auto it : d) {
		if (can[it.r]) {
			continue;
		}
		if (it.order == "buy") {
			buy.emplace_back(it);
		} else {
			sell.emplace_back(it);
		}
	}
	sort(sell.begin(), sell.end(), [](rec a, rec b) {
		return a.p < b.p; // less
	});
	sort(buy.begin(), buy.end(), [](rec a, rec b) {
		return a.p > b.p; // greater
	});
	long long ress = 0, sums = 0;
	double resp = 0;
	for (int i = 0; i < (int)sell.size(); i++) {
		sums += sell[i].s; // total stocks can sell
		long long sumb = 0;
		for (int j = 0; j < (int)buy.size(); j++) {
			if (buy[j].p >= sell[i].p) {
				sumb += buy[j].s; // total stocks can buy
				if (sumb >= sums) {
					break;
				}
			} else { // buy price < sell price, can not buy/sell
				break;
			}
		}
		long long vol = min(sums, sumb); // volume of trade
		if (ress <= vol) {
			ress = vol;
			resp = sell[i].p; // first volume, second price
		}
	}
	long long sumb = 0;
	for (int i = 0; i < (int)buy.size(); i++) {
		sumb += buy[i].s;
		if (sumb >= ress) {
			resp = max(resp, buy[i].p); // opening price possible higher
			break;
		}
	}
	cout << fixed << setprecision(2) << resp << " " << ress << "\n";
	return 0;
}