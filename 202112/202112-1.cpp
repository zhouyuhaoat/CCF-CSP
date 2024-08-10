#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {

    int n, m;
    cin >> n >> m;
    int a[n + 2];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a[n + 1] = m;
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res += i * (a[i + 1] - a[i]);
    }
    cout << res << "\n";

    return 0;
}