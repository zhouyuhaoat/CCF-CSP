/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-24 15:11:19
 * 	modified: 	2024-07-24 15:42:44
 * 	item: 		Certified Software Professional
 * 	site: 		92, Yugan
 */
#include <iostream>
#include <tuple>

using namespace std;

int main(int argc, char const *argv[]) {

    int n, m;
    cin >> n >> m;
    tuple<int, int, char> d[n];
    for (int i = 0; i < n; i++) {
        int x, y;
        char t;
        cin >> x >> y >> t;
        d[i] = make_tuple(x, y, t);
    }
    for (int q = 0; q < m; q++) {
        int a, b, c;
        cin >> a >> b >> c;
        int cls[2] = {0, 0};
        bool flag = true;
        for (int i = 0; i < n; i++) {
            int x, y;
            char t;
            tie(x, y, t) = d[i];
            long long res = a + (long long)b * x + (long long)c * y;
            if (res * cls[t - 'A'] < 0) {
                flag = false;
                break;
            }
            res > 0 ? cls[t - 'A'] = 1 : cls[t - 'A'] = -1;
        }
        if (flag && cls[0] * cls[1] < 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}