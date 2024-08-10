/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-08-10 19:10:47
 * 	modified: 	2024-08-10 19:36:01
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

    int n, last;
    cin >> n >> last;
    int sum1 = last, sum2 = last;
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        if (x > last) {
            sum1 += x, sum2 += x;
        } else {
            sum1 += last, sum2 += 0;
        }
        last = x;
    }
    cout << sum1 << "\n" << sum2 << "\n";

    return 0;
}