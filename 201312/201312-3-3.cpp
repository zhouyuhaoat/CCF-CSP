/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-09-28 16:34:29
 * 	modified: 	2024-05-20 14:35:15
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
	vector<int> h(n + 2); // sentinel
	for (int i = 0; i < n; i++) {
		cin >> h[i + 1];
	}
	vector<int> l(n + 2);
	stack<int> monost; // monotonic stack
	monost.emplace(0);
	for (int i = 1; i <= n; i++) {
		while (h[i] <= h[monost.top()]) {
			monost.pop();
		}
		l[i] = monost.top() + 1;
		monost.emplace(i);
	}
	vector<int> r(n + 2);
	r[n + 1] = n + 1;
	while (!monost.empty()) {
		monost.pop();
	}
	monost.emplace(n + 1);
	for (int i = n; i >= 1; i--) {
		while (h[i] <= h[monost.top()]) {
			monost.pop();
		}
		r[i] = monost.top() - 1;
		monost.emplace(i);
	}
	int rec = 0;
	for (int i = 1; i <= n; i++) {
		rec = max(rec, h[i] * (r[i] - l[i] + 1));
	}
	cout << rec << "\n";

	return 0;
}