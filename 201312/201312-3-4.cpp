/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-09-28 17:09:19
 * 	modified: 	2024-05-20 14:38:43
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
	vector<int> h(n + 2);
	for (int i = 0; i < n; i++) {
		cin >> h[i + 1];
	}
	int rec = 0;
	stack<int> monost;
	monost.emplace(0);
	for (int i = 1; i <= n + 1; i++) {
		while (h[i] < h[monost.top()]) {
			int w = monost.top();
			monost.pop(); // backtracking
			rec = max(rec, h[w] * (i - monost.top() - 1));
		}
		monost.emplace(i);
	}
	cout << rec << "\n";

	return 0;
}