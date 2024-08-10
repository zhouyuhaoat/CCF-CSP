// https://www.acwing.com/activity/content/code/content/2122114
#include <algorithm>
#include <iostream>

using namespace std;

const int maxn = 500010, maxm = 10010;

int a[maxn], cnt[maxm];

int main(int argc, char const *argv[]) {

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    n = unique(a + 1, a + n + 1) - (a + 1);
    a[0] = a[n + 1] = 0;
    for (int i = 1; i <= n; i++) {
        int x = a[i - 1], y = a[i], z = a[i + 1];
        if (x < y && z < y) {
            ++cnt[y];
        } else if (x > y && z > y) {
            --cnt[y];
        }
    }
    int res = 0, sum = 0;
    for (int i = maxm - 1; i > 0; i--) {
        sum += cnt[i];
        res = max(res, sum);
    }
    cout << res << "\n";

    return 0;
}