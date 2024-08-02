/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-08-02 10:53:14
 * 	modified: 	2024-08-02 10:56:11
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

    int n;
    cin >> n;
    int res = 0;
    for (int i = 0; i < n; i++) {
        int w, s;
        cin >> w >> s;
        res += w * s;
    }
    if (res < 0) {
        res = 0;
    }
    cout << res << "\n";

    return 0;
}