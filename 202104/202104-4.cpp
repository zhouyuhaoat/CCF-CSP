// https://www.acwing.com/activity/content/code/content/1155832
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int maxm = 100010, mod = 1e9 + 7;

vector<int> q[maxm];
bool vis[maxm];

int main(int argc, char const *argv[]) {

    for (int i = 1; i < maxm; i++) {
        for (int j = i * 2; j < maxm; j += i) {
            q[j].emplace_back(i);
        }
    }
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int f[n];
    memset(f, 0, sizeof(f));
    f[0] = 1;
    for (int i = 1; i < n; i++) {
        memset(vis, 0, sizeof(vis));
        for (int j = i - 1; j >= 0; j--) {
            int d = a[i] - a[j], cnt = 0;
            for (int k : q[d]) {
                if (!vis[k]) {
                    ++cnt;
                    vis[k] = true;
                }
            }
            vis[d] = true;
            f[i] = (f[i] + (long long)f[j] * cnt) % mod;
        }
    }
    cout << f[n - 1] << "\n";

    return 0;
}