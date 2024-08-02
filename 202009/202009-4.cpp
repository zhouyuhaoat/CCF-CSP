/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-08-01 09:54:03
 * 	modified: 	2024-08-01 10:41:02
 * 	item: 		Certified Software Professional
 * 	site: 		226, Harbin
 */
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 110, maxm = 2010;

int p[maxm][maxn];

double pow(double x) { // square
    return x * x;
}

int main(int argc, char const *argv[]) {

    int n, m, R;
    cin >> n >> m >> R;
    vector<int> O(n);
    for (int i = 0; i < n; i++) {
        cin >> O[i];
    }
    vector<double> d(m), t(m);
    for (int i = 0; i < m; i++) {
        int s = 0;
        for (int j = 0; j < n; j++) {
            cin >> p[i][j];
            s += pow(p[i][j] - O[j]); // distance to origin
        }
        d[i] = sqrt(s);
        t[i] = sqrt(s - pow(R)); // tangent
    }
    vector<double> ans(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < i; j++) { // j < i
            int s = 0;
            for (int k = 0; k < n; k++) {
                s += pow(p[i][k] - p[j][k]); // distance between two points
            }
            double a = d[i], b = d[j], c = sqrt(s), p = (a + b + c) / 2;
            double area = sqrt(p * (p - a) * (p - b) * (p - c)); // Heron's formula
            double h = area * 2 / c;
            // Computational Geometry: https://www.acwing.com/solution/content/38209
            if (h >= R || pow(b) >= pow(a) + s || pow(a) >= pow(b) + s) {
                // line segment between two points not cross the black hole
                ans[i] += c, ans[j] += c;
            } else {
                // route: tangent -> arc -> tangent
                // two points + origin -> triangle
                // two tangent + radius -> two tangent triangle
                // one arc + radius -> one sector
                double a1 = acos((pow(a) + pow(b) - s) / (2 * a * b)); // Law of Cosines
                double a2 = acos(R / a), a3 = acos(R / b);
                double l = (a1 - a2 - a3) * R + t[i] + t[j];
                ans[i] += l, ans[j] += l;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        cout << fixed << setprecision(12) << ans[i] << "\n";
    }

    return 0;
}