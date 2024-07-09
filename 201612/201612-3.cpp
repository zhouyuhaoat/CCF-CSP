/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-10 14:20:54
 * 	modified: 	2024-07-07 14:29:00
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <map>
#include <set>

using namespace std;

int main(int argc, char const *argv[]) {

	int p, pos;
	cin >> p;
	map<string, bool> l;
	for (int i = 0; i < p; i++) {
		string pri;
		cin >> pri;
		if ((pos = pri.find(':')) != string::npos) {
			l[pri.substr(0, pos)] = true;
		}
	}
	int r;
	cin >> r;
	map<string, set<string>> r2p;
	for (int i = 0; i < r; i++) {
		string role;
		int s;
		cin >> role >> s;
		for (int j = 0; j < s; j++) {
			string pri;
			cin >> pri;
			r2p[role].emplace(pri);
		}
	}
	int u;
	cin >> u;
	map<string, set<string>> u2p;
	map<string, int> u2pl;
	for (int i = 0; i < u; i++) {
		string user;
		int t;
		cin >> user >> t;
		for (int j = 0; j < t; j++) {
			string role;
			cin >> role;
			for (auto it : r2p[role]) {
				if ((pos = it.find(':')) != string::npos) {
					string pri = it.substr(0, pos);
					int lev = stoi(it.substr(pos + 1));
					u2p[user].emplace(pri);
					u2pl[user + pri] = max(u2pl[user + pri], lev);
				} else {
					u2p[user].emplace(it);
				}
			}
		}
	}
	int q;
	cin >> q;
	for (int qq = 0; qq < q; qq++) {
		string user, pri;
		cin >> user >> pri;
		int lev = -1;
		if ((pos = pri.find(':')) != string::npos) {
			lev = stoi(pri.substr(pos + 1));
			pri = pri.substr(0, pos);
		}
		bool flag = false;
		if (u2p[user].find(pri) != u2p[user].end()) {
			if (l[pri]) {
				if (lev != -1) {
					if (lev <= u2pl[user + pri]) {
						flag = true;
					}
				} else {
					cout << u2pl[user + pri] << "\n";
					continue;
				}
			} else {
				flag = true;
			}
		}
		if (flag) {
			cout << "true\n";
		} else {
			cout << "false\n";
		}
	}

	return 0;
}