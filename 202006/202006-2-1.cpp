/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-24 15:43:41
 * 	modified: 	2024-07-24 15:53:51
 * 	item: 		Certified Software Professional
 * 	site: 		92, Yugan
 */
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {

    int n, a, b;
    cin >> n >> a >> b;
    map<int, int> u;
    for (int i = 0; i < a; i++) {
        int idx, val;
        cin >> idx >> val;
        u[idx] = val;
    }
    long long res = 0;
    for (int i = 0; i < b; i++) {
        int idx, val;
        cin >> idx >> val;
        if (u.find(idx) != u.end()) {
            res += (long long)u[idx] * val;
        }
    }
    cout << res << "\n";

    return 0;
}