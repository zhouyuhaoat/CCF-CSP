/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-08-02 10:56:53
 * 	modified: 	2024-08-02 11:46:37
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

    int m;
    cin >> m;
    pair<int, int> d[m];
    for (int i = 0; i < m; i++) {
        cin >> d[i].first >> d[i].second;
    }
    int theta = -1, mc = -1;
    for (int i = 0; i < m; i++) {
        int cnt = 0;
        for (int j = 0; j < m; j++) {
            if (d[j].first >= d[i].first && d[j].second == 1) {
                ++cnt;
            } else if (d[j].first < d[i].first && d[j].second == 0) {
                ++cnt;
            }
        }
        if (cnt > mc) {
            mc = cnt;
            theta = d[i].first;
        } else if (cnt == mc) {
            theta = max(theta, d[i].first);
        }
    }
    cout << theta << "\n";

    return 0;
}