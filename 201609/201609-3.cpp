/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-10 12:19:11
 * 	modified: 	2024-07-06 15:25:50
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	vector<vector<pair<int, int>>> t(2);
	t[0].emplace_back(0, 30);
	t[1].emplace_back(0, 30);
	int win = 0, run = 0;
	for (int i = 0; i < n; i++) {
		string act;
		cin >> act;
		if (act == "summon") {
			int p, a, h;
			cin >> p >> a >> h;
			t[run].insert(t[run].begin() + p, {a, h});
		} else if (act == "attack") {
			int a, d;
			cin >> a >> d;
			t[run][a].second -= t[(run + 1) % 2][d].first;
			t[(run + 1) % 2][d].second -= t[run][a].first;
			// first update health, then update followers
			// since attack and defense are simultaneous
			// once update followers, followers' position will change
			if (t[run][a].second <= 0 && a > 0) {
				t[run].erase(t[run].begin() + a);
			}
			if (t[(run + 1) % 2][d].second <= 0 && d > 0) {
				t[(run + 1) % 2].erase(t[(run + 1) % 2].begin() + d);
			}
			if (t[0][0].second > 0 && t[1][0].second <= 0) {
				win = 1;
				break;
			} else if (t[0][0].second <= 0 && t[1][0].second > 0) {
				win = -1;
				break;
			}
		} else {
			run = (run + 1) % 2; // run ^ 1
		}
	}
	cout << win << "\n" << t[0][0].second << "\n" << t[0].size() - 1;
	for (int i = 1; i < (int)t[0].size(); i++) {
		cout << " " << t[0][i].second;
	}
	cout << "\n" << t[1][0].second << "\n" << t[1].size() - 1;
	for (int i = 1; i < (int)t[1].size(); i++) {
		cout << " " << t[1][i].second;
	}
	cout << "\n";

	return 0;
}