/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-08-05 21:50:35
 * 	modified: 	2024-08-05 21:57:33
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

    int n, L, r, t;
    cin >> n >> L >> r >> t;
    int A[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0, cnt = 0;
            for (int p = i - r; p <= i + r; p++) {
                for (int q = j - r; q <= j + r; q++) {
                    if (p >= 0 && p < n && q >= 0 && q < n) {
                        sum += A[p][q];
                        ++cnt;
                    }
                }
            }
            if (sum * 1.0 / cnt <= t) {
                ++res;
            }
        }
    }
    cout << res << "\n";

    return 0;
}