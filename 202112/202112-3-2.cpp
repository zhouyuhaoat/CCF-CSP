// https://www.acwing.com/solution/content/102204
#include <iostream>

using namespace std;

const int maxn = 2000, mod = 929;

int w, s, k;
string str;
int d[maxn], cnt;
int g[maxn], res[maxn];

void getd() {
    int mode = 0;
    for (int i = 0; i < (int)str.size(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            if (mode == 1) {
                d[++cnt] = 28, d[++cnt] = 28;
            } else if (mode == 2) {
                d[++cnt] = 28;
            }
            mode = 0, d[++cnt] = str[i] - 'A';
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            if (mode != 1) {
                d[++cnt] = 27;
            }
            mode = 1, d[++cnt] = str[i] - 'a';
        } else {
            if (mode != 2) {
                d[++cnt] = 28;
            }
            mode = 2, d[++cnt] = str[i] - '0';
        }
    }
    if (cnt & 1) {
        d[++cnt] = 29;
    }
    for (int i = 1, j = 1; i < cnt; i += 2, j++) {
        d[j] = 30 * d[i] + d[i + 1];
    }
    cnt >>= 1;
    while ((cnt + 1 + k) % w != 0) {
        d[++cnt] = 900;
    }
    d[0] = cnt + 1;
}

void getg() {
    g[0] = 1;
    int r = -3;
    for (int i = 1; i <= k; r = r * 3 % mod, i++) {
        for (int j = i - 1; j >= 0; j--) {
            g[j + 1] = (g[j + 1] + g[j] * r) % mod;
        }
    }
}

int main(int argc, char const *argv[]) {

    cin >> w >> s >> str;
    k = ~s ? 1 << (s + 1) : 0;
    getd(), getg();
    for (int i = 0; i <= cnt; i++) {
        res[i] = d[i];
    }
    for (int i = 0; i <= cnt; i++) {
        int r = res[i];
        res[i] = 0;
        for (int j = 1; j <= k; j++) {
            res[i + j] = (res[i + j] - r * g[j]) % mod;
        }
    }
    for (int i = 0; i <= cnt; i++) {
        cout << d[i] << "\n";
    }
    for (int i = cnt + 1; i <= cnt + k; i++) {
        cout << (-res[i] % mod + mod) % mod << "\n";
    }

    return 0;
}