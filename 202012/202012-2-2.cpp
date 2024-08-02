/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-08-02 12:17:10
 * 	modified: 	2024-08-02 17:28:25
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

    int n;
    cin >> n;
    pair<int, int> q[n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> q[i].first >> q[i].second;
        // first is threshold, second is predict
    }
    sort(q + 1, q + n + 1);
    int s[2][n + 1]; // prefix sum of predict = 0/1
    memset(s, 0, sizeof(s));
    for (int i = 0; i < 2; i++) {
        for (int j = 1; j <= n; j++) {
            s[i][j] = s[i][j - 1] + (q[j].second == i);
        }
    }
    int mc = -1, t;
    for (int i = 1; i <= n; i++) {
        int cnt = s[0][i - 1] + s[1][n] - s[1][i - 1];
        // s[0][i - 1]: predict = 0 when threshold < supposed threshold
        // s[1][n] - s[1][i - 1]: predict = 1 when threshold >= supposed threshold
        if (cnt >= mc) {
            mc = cnt;
            t = q[i].first;
        }
        // skip same threshold since count 0 of smaller threshold, count 1 of not smaller threshold
        while (i + 1 <= n && q[i + 1].first == q[i].first) {
            ++i;
        }
    }
    cout << t << "\n";

    return 0;
}