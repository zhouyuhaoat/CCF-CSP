/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-15 23:19:07
 * 	modified: 	2024-07-16 14:07:40
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int m, n;
	cin >> m >> n;
	map<int, int> f[m];
	set<pair<int, int>> g[m];
	for (int i = 0; i < n; i++) {
		int id, score;
		cin >> id >> score;
		for (int j = 0; j < m; j++) {
			f[j][id] = score;
			g[j].emplace(score, -id);
			// score: ascending; id: descending
		}
	}
	int op;
	cin >> op;
	while (op--) {
		int t;
		cin >> t;
		if (t == 1) {
			int type, id, score;
			cin >> type >> id >> score;
			f[type][id] = score;
			g[type].emplace(score, -id);
		} else if (t == 2) {
			int type, id;
			cin >> type >> id;
			g[type].erase({f[type][id], -id});
			// map: type + id -> score
			f[type].erase(id);
		} else {
			int tot;
			cin >> tot;
			vector<int> sum(m), cnt(m), ans[m];
			set<pair<int, int>>::reverse_iterator it[m];
			// reverse_iterator: rbegin() -> rend()
			// k-way merge: iterator array
			for (int i = 0; i < m; i++) {
				cin >> sum[i];
				it[i] = g[i].rbegin();
			}
			while (tot--) {
				int k = -1;
				for (int i = 0; i < m; i++) {
					if (it[i] != g[i].rend() && cnt[i] < sum[i]) {
						if (k == -1 || it[i]->first > it[k]->first) { // not >=
							k = i;
						}
					}
				}
				if (k == -1) {
					break;
				}
				ans[k].emplace_back(-it[k]->second);
				++cnt[k];
				++it[k]; // iteration
			}
			for (int i = 0; i < m; i++) {
				if (!ans[i].empty()) {
					for (int j = 0; j < (int)ans[i].size(); j++) {
						cout << ans[i][j];
						j < (int)ans[i].size() - 1 ? cout << " " : cout << "\n";
					}
				} else {
					cout << "-1\n";
				}
			}
		}
	}

	return 0;
}