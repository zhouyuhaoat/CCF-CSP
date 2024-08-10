// https://www.acwing.com/activity/content/code/content/2119646
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

const int maxn = 2010;
const double inf = 1e8;

int h[maxn], e[maxn], D[maxn], ne[maxn], idx;
double W[maxn], v[maxn], u[maxn], a[maxn], b[maxn], c[maxn], d[maxn];
int r[maxn], cnt[maxn];
double I[1024][maxn / 2];

static unsigned long _next = 1;

/* RAND_MAX assumed to be 32767 */
int myrand(void) {
    _next = _next * 1103515245 + 12345;
    return ((unsigned)(_next / 65536) % 32768);
}

void add(int a, int b, double c, int d) {
    e[idx] = b, W[idx] = c, D[idx] = d, ne[idx] = h[a], h[a] = idx++;
}

int main(int argc, char const *argv[]) {

    memset(h, -1, sizeof(h));
    int n, s, p, T;
    double dt;
    cin >> n >> s >> p >> T >> dt;
    for (int i = 0; i < n;) {
        int rn;
        cin >> rn;
        double vv, uu, aa, bb, cc, dd;
        cin >> vv >> uu >> aa >> bb >> cc >> dd;
        for (int j = 0; j < rn; j++, i++) {
            v[i] = vv, u[i] = uu, a[i] = aa, b[i] = bb, c[i] = cc, d[i] = dd;
        }
    }
    for (int i = n; i < n + p; i++) {
        cin >> r[i];
    }
    int mod = 0;
    while (s--) {
        int a, b, d;
        double c;
        cin >> a >> b >> c >> d;
        add(a, b, c, d);
        mod = max(mod, d + 1);
    }
    for (int i = 0; i < T; i++) {
        int t = i % mod;
        for (int j = n; j < n + p; j++) {
            if (r[j] > myrand()) {
                for (int k = h[j]; ~k; k = ne[k]) {
                    int x = e[k];
                    I[(t + D[k]) % mod][x] += W[k];
                }
            }
        }
        for (int j = 0; j < n; j++) {
            double vv = v[j], uu = u[j];
            v[j] = vv + dt * (0.04 * vv * vv + 5 * vv + 140 - uu) + I[t][j];
            u[j] = uu + dt * a[j] * (b[j] * vv - uu);
            if (v[j] >= 30) {
                for (int k = h[j]; ~k; k = ne[k]) {
                    int x = e[k];
                    I[(t + D[k]) % mod][x] += W[k];
                }
                ++cnt[j];
                v[j] = c[j], u[j] += d[j];
            }
        }
        memset(I[t], 0, sizeof(I[t]));
    }
    double minv = inf, maxv = -inf;
    int minc = inf, maxc = -inf;
    for (int i = 0; i < n; i++) {
        minv = min(minv, v[i]);
        maxv = max(maxv, v[i]);
        minc = min(minc, cnt[i]);
        maxc = max(maxc, cnt[i]);
    }
    cout << fixed << setprecision(3) << minv << " " << maxv << "\n";
    cout << minc << " " << maxc << "\n";

    return 0;
}