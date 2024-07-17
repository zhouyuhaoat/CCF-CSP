/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-16 15:04:28
 * 	modified: 	2024-07-16 15:38:34
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <map>
#define x first
#define y second

using namespace std;

map<pair<int, int>, bool> t;

int judge(pair<int, int> p) {
	if (!t[p]) {
		return -1;
	}
	pair<int, int> p1 = {p.x, p.y + 1}, p2 = {p.x, p.y - 1}, p3 = {p.x + 1, p.y}, p4 = {p.x - 1, p.y};
	if (!t[p1] || !t[p2] || !t[p3] || !t[p4]) {
		return -1;
	}
	p1 = {p.x + 1, p.y + 1}, p2 = {p.x + 1, p.y - 1}, p3 = {p.x - 1, p.y + 1}, p4 = {p.x - 1, p.y - 1};
	return t[p1] + t[p2] + t[p3] + t[p4];
}

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	pair<int, int> c[n];
	for (int i = 0; i < n; i++) {
		cin >> c[i].x >> c[i].y;
		t[c[i]] = true;
	}
	int cnt[5] = {0};
	for (int i = 0; i < n; i++) {
		int score = judge(c[i]);
		if (score != -1) {
			++cnt[score];
		}
	}
	for (int i = 0; i < 5; i++) {
		cout << cnt[i] << "\n";
	}

	return 0;
}