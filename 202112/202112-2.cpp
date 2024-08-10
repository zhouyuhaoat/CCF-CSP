// https://www.acwing.com/activity/content/code/content/2910128
#include <iostream>

using namespace std;

typedef long long ll;

const int maxn = 100010;

int a[maxn];
int R;

ll get(int l, int r) {
    if (l / R == r / R) {
        return (ll)(r - l + 1) * (l / R);
    }
    int a = l / R + 1, b = r / R - 1;
    ll res = (a + b) * (ll)(b - a + 1) / 2 * R;
    res += (a - 1) * (ll)(a * R - l);
    res += (b + 1) * (ll)(r - (b * R + R) + 1);
    return res;
}

int main(int argc, char const *argv[]) {

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a[n + 1] = m;
    R = m / (n + 1);
    ll res = 0;
    for (int i = 0; i <= n; i++) {
        int l = a[i], r = a[i + 1] - 1;
        int x = l / R, y = r / R;
        if (y <= i || x >= i) {
            res += abs((ll)i * (r - l + 1) - get(l, r));
        } else {
            int mid = i * R;
            res += abs((ll)i * (mid - l + 1) - get(l, mid));
            res += abs((ll)i * (r - mid) - get(mid + 1, r));
        }
    }
    cout << res << "\n";

    return 0;
}