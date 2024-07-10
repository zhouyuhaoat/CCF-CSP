/*
 * 	author: 	zhouyuhao
 * 	created: 	2023-10-08 21:45:42
 * 	modified: 	2024-07-09 21:24:42
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	int n;
	cin >> n;
	vector<int> d(n), l(n + 1);
	for (int i = 0; i < n; i++) {
		d[i] = i + 1;
		l[i + 1] = i;
	}
	int m;
	cin >> m;
	for (int qq = 0; qq < m; qq++) {
		int p, q;
		cin >> p >> q;
		if (q > 0) {
			for (int i = 0; i < q; i++) {
				d[l[p] + i] = d[l[p] + i + 1];
				l[d[l[p] + i + 1]] = l[p] + i;
			}
			d[l[p] + q] = p;
			l[p] = l[p] + q;
		} else {
			q = -q;
			for (int i = 0; i < q; i++) {
				d[l[p] - i] = d[l[p] - i - 1];
				l[d[l[p] - i - 1]] = l[p] - i;
			}
			d[l[p] - q] = p;
			l[p] = l[p] - q;
		}
	}
	for (int i = 0; i < (int)d.size(); i++) {
		cout << d[i];
		i < (int)d.size() - 1 ? cout << " " : cout << "\n";
	}

	return 0;
}