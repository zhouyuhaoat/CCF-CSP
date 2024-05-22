/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-09-28 19:10:00
 * 	modified: 	2024-05-20 14:18:37
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
	vector<int> lo(n);
	stack<int> monost;
	for (int i = 0; i < n; i++) {
		while (!monost.empty() && h[i] <= h[monost.top()]) {
			monost.pop();
		}
		lo[i] = monost.empty() ? 0 : monost.top() + 1;
		monost.emplace(i);
	}
	vector<int> hi(n);
	while (!monost.empty()) {
		monost.pop();
	}
	for (int i = n - 1; i >= 0; i--) {
		while (!monost.empty() && h[i] <= h[monost.top()]) {
			monost.pop();
		}
		hi[i] = monost.empty() ? n : monost.top();
		monost.emplace(i);
	}
	int rec = 0;
	for (int i = 0; i < n; i++) {
		rec = max(rec, h[i] * (hi[i] - lo[i]));
	}
	cout << rec << "\n";

	return 0;
}