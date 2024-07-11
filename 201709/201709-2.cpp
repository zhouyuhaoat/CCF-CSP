/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-05 19:59:13
 * 	modified: 	2024-07-10 17:05:30
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <numeric>
#include <queue>

using namespace std;

struct per {
	int key, time, type;
	per(int key, int time, int type) : key(key), time(time), type(type) {
	}
	friend bool operator<(per a, per b) {
		if (a.time != b.time) {
			return a.time > b.time;
		} else {
			if (a.type != b.type) {
				return a.type < b.type;
			} else {
				return a.key > b.key;
			}
		}
	}
};

int main(int argc, char const *argv[]) {

	int n, k;
	cin >> n >> k;
	priority_queue<per> q;
	for (int i = 0; i < k; i++) {
		int w, s, c;
		cin >> w >> s >> c;
		q.emplace(w, s, 0);
		q.emplace(w, s + c, 1);
	}
	vector<int> t(n + 1);
	iota(t.begin(), t.end(), 0);
	while (!q.empty()) {
		per tp = q.top();
		q.pop();
		if (tp.type != 0) {
			for (int i = 1; i <= n; i++) {
				if (t[i] == -1) {
					t[i] = tp.key;
					break;
				}
			}
		} else {
			for (int i = 1; i <= n; i++) {
				if (t[i] == tp.key) {
					t[i] = -1;
					break;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << t[i];
		i < n ? cout << " " : cout << "\n";
	}

	return 0;
}