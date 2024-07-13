/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 22:21:19
 * 	modified: 	2024-07-12 23:17:58
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct ball {
	int id, pos, dir;
};

int main(int argc, char const *argv[]) {

	int n, l, t;
	cin >> n >> l >> t;
	vector<ball> b(n);
	for (int i = 0; i < n; i++) {
		cin >> b[i].pos;
		b[i].id = i;
		b[i].dir = 1;
	}
	for (int tt = 0; tt < t; tt++) {
		for (int i = 0; i < n; i++) {
			b[i].pos += b[i].dir;
			if (b[i].pos == 0 || b[i].pos == l) {
				b[i].dir = -b[i].dir;
			}
		}
		sort(b.begin(), b.end(), [](ball a, ball b) {
			return a.pos < b.pos;
		});
		for (int i = 1; i < n; i++) {
			if (b[i].pos == b[i - 1].pos) {
				b[i].dir = -b[i].dir;
				b[i - 1].dir = -b[i - 1].dir;
			}
		}
	}
	sort(b.begin(), b.end(), [](ball a, ball b) {
		return a.id < b.id;
	});
	for (int i = 0; i < n; i++) {
		cout << b[i].pos;
		i < n - 1 ? cout << " " : cout << "\n";
	}

	return 0;
}