/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-09-28 16:31:57
 * 	modified: 	2024-05-20 14:01:12
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	vector<int> h(n);
	for (int i = 0; i < n; i++) {
		cin >> h[i];
	}
	int rec = 0;
	for (int i = 0; i < n; i++) {
		int minh = h[i];
		for (int j = i; j < n; j++) {
			minh = min(minh, h[j]);
			rec = max(rec, (j - i + 1) * minh);
		}
	}
	cout << rec << "\n";

	return 0;
}