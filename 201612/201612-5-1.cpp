/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-09 20:10:44
 * 	modified: 	2024-07-09 21:12:07
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

const int maxn = 15, maxm = 1 << maxn;

double trans[maxm][maxn], dp[2][maxm];

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	double p[n][n] = {0};
	for (int i = 0; i < n - 1; i++) { // 1-based -> 0-based
		for (int j = i + 1; j < n; j++) {
			cin >> p[i][j]; // upper triangle, diagonal is 0
			p[j][i] = 1 - p[i][j];
		}
	}
	int U = (1 << n) - 1; // upper limit with state compression
	for (int s = 1; s < U; s++) {
		double s1[n] = {0}, s2[n] = {0};
		// 1: your hand; 2: opponent's hand
		for (int i = 0; i < n; i++) {
			if (s >> i & 1) { // your hand
				for (int j = 0; j < n; j++) {
					if (!(s >> j & 1)) { // opponent's hand
						s1[i] += p[i][j];
					}
				}
			} else {
				for (int j = 0; j < n; j++) {
					if (s >> j & 1) {
						s2[i] += p[i][j];
					}
				}
			}
		}
		double sum1 = 0, sum2 = 0;
		for (int i = 0; i < n; i++) {
			sum1 += s1[i], sum2 += s2[i];
		}
		for (int i = 0; i < n; i++) {
			if (s >> i & 1) {
				for (int j = 0; j < n; j++) {
					if (!(s >> j & 1)) {
						trans[s][i] += s1[i] / sum1 * s2[j] / sum2 * p[j][i];
						// prob of state lose card = prob of lose cards *
						// prob of win card * prob[win card][lose card]
					}
				}
			} else {
				for (int j = 0; j < n; j++) {
					if (s >> j & 1) {
						trans[s][i] += s1[j] / sum2 * s2[i] / sum1 * p[j][i];
					}
				}
			}
		}
	}
	int iter = 1000;
	while (iter--) {
		// initialization: full state + empty state
		memset(dp[iter & 1], 0, sizeof(dp[iter & 1]));
		dp[iter & 1][U] = 1;
		for (int s = 1; s < U; s++) {
			for (int i = 0; i < n; i++) {
				dp[iter & 1][s] += trans[s][i] * dp[(iter - 1) & 1][s ^ (1 << i)];
				// state lose card -> previous state
			}
		}
	}
	for (int i = 0; i < m; i++) {
		int state = 0;
		for (int j = 0; j < n; j++) {
			int x;
			cin >> x;
			state += x << j;
		}
		cout << fixed << setprecision(5) << dp[0][state] << "\n";
	}

	return 0;
}