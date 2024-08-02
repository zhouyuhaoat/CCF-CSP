/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-31 22:08:29
 * 	modified: 	2024-07-31 22:38:57
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <iostream>
#include <vector>

using namespace std;

bool ispass(int x, int y, int xl, int yd, int xr, int yu) {
    return x >= xl && x <= xr && y >= yd && y <= yu;
}

int scan(vector<bool> &in) {
    int res = 0;
    for (size_t i = 0; i < in.size(); i++) {
        if (in[i]) {
            int cnt = 1;
            while (i + 1 < in.size() && in[++i]) {
                ++cnt;
            }
            res = max(res, cnt);
        }
    }
    return res;
}

int main(int argc, char const *argv[]) {

    int n, k, t, xl, yd, xr, yu;
    cin >> n >> k >> t >> xl >> yd >> xr >> yu;
    int pass = 0, overstay = 0;
    for (int i = 0; i < n; i++) {
        vector<bool> in(t);
        for (int j = 0; j < t; j++) {
            int x, y;
            cin >> x >> y;
            if (ispass(x, y, xl, yd, xr, yu)) {
                in[j] = true;
            }
        }
        int cnt = scan(in);
        if (cnt > 0) {
            ++pass;
            if (cnt >= k) {
                ++overstay;
            }
        }
    }
    cout << pass << "\n" << overstay << "\n";

    return 0;
}