// https://www.acwing.com/activity/content/code/content/2122322
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

const int maxn = 16, maxm = 1 << maxn;

int n, m;
double p[maxn];
double f[maxm][maxn * 5 + 1];

double dp(int state, int coins, int r) {
    double &v = f[state][coins];
    if (v >= 0) {
        return v;
    }
    if (coins >= r * m) {
        v = 0;
        return v;
    }
    v = 0;
    for (int i = 0; i < n; i++) {
        if (state >> i & 1) {
            v += p[i] * (dp(state, coins + 1, r) + 1);
        } else {
            v += p[i] * (dp(state | (1 << i), coins, r - 1) + 1);
        }
    }
    return v;
}

int main(int argc, char const *argv[]) {

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    memset(f, -1, sizeof(f));
    cout << fixed << setprecision(10) << dp(0, 0, n) << "\n";

    return 0;
}