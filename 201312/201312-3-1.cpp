/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-09-28 16:28:43
 * 	modified: 	2024-05-20 14:18:04
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
		for (int j = 0; j < n; j++) {
			int minh = h[i];
			for (int k = i + 1; k <= j; k++) {
				minh = min(minh, h[k]);
			}
			rec = max(rec, (j - i + 1) * minh);
		}
	}
	cout << rec << "\n";

	return 0;
}