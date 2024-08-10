/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-08-05 21:57:58
 * 	modified: 	2024-08-05 22:10:10
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

const int maxn = 610;

int s[maxn][maxn]; // prefix sum: 2-dim

int getsum(int x1, int y1, int x2, int y2) {
    return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
}

int getsize(int x1, int y1, int x2, int y2) {
    return (x2 - x1 + 1) * (y2 - y1 + 1);
}

int main(int argc, char const *argv[]) {

    int n, L, r, t;
    cin >> n >> L >> r >> t;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            s[i][j] = x + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x1 = max(1, i - r), y1 = max(1, j - r); // left up
            int x2 = min(n, i + r), y2 = min(n, j + r); // right down
            if (getsum(x1, y1, x2, y2) <= t * getsize(x1, y1, x2, y2)) {
                ++res;
            }
        }
    }
    cout << res << "\n";

    return 0;
}