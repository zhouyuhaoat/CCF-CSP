/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-31 22:01:28
 * 	modified: 	2024-07-31 22:07:52
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

    int n, X, Y;
    cin >> n >> X >> Y;
    pair<int, int> d[n];
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        d[i] = {(x - X) * (x - X) + (y - Y) * (y - Y), i + 1};
    }
    sort(d, d + n);
    for (int i = 0; i < 3; i++) {
        cout << d[i].second << "\n";
    }

    return 0;
}