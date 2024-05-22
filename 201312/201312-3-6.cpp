/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-09-28 19:15:21
 * 	modified: 	2024-05-20 14:18:47
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <stack>
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
	stack<int> monost;
	for (int hi = 0; hi <= n; hi++) {
		while (!monost.empty() && (hi == n || h[hi] < h[monost.top()])) {
			int mi = monost.top();
			monost.pop();
			int lo = monost.empty() ? 0 : monost.top() + 1;
			rec = max(rec, h[mi] * (hi - lo));
		}
		if (hi < n) {
			monost.emplace(hi);
		}
	}
	cout << rec << "\n";

	return 0;
}