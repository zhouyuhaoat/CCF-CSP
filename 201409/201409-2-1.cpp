/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-02 21:52:52
 * 	modified: 	2024-05-25 11:05:10
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	bool vis[101][101] = {};
	int cnt = 0;
	for (int q = 0; q < n; q++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		for (int i = x1; i < x2; i++) {
			for (int j = y1; j < y2; j++) {
				if (!vis[i][j]) {
					vis[i][j] = true;
					++cnt;
				}
			}
		}
	}
	cout << cnt << "\n";

	return 0;
}