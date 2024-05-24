/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-01 15:10:27
 * 	modified: 	2024-05-21 15:14:07
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

struct win {
	int id;
	int x1, y1, x2, y2;
};

bool inwin(win t, int x, int y) {
	if (x >= t.x1 && y >= t.y1 && x <= t.x2 && y <= t.y2) {
		return true;
	}
	return false;
}

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	vector<win> w;
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		w.emplace_back(win{i + 1, x1, y1, x2, y2});
	}
	for (int q = 0; q < m; q++) {
		int x, y;
		cin >> x >> y;
		bool flag = true;
		for (int i = n - 1; i >= 0; i--) {
			if (inwin(w[i], x, y)) {
				cout << w[i].id << "\n";
				w.emplace_back(w[i]);
				w.erase(w.begin() + i);
				flag = false;
				break;
			}
		}
		if (flag) {
			cout << "IGNORED\n";
		}
	}

	return 0;
}