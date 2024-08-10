/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-08-05 21:44:52
 * 	modified: 	2024-08-05 21:50:19
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

    int n, m, L;
    cin >> n >> m >> L;
    int h[256] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int a;
            cin >> a;
            ++h[a];
        }
    }
    for (int i = 0; i < L; i++) {
        cout << h[i];
        i < L - 1 ? cout << " " : cout << "\n";
    }

    return 0;
}