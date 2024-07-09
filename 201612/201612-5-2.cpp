/*
 * 	author: 	zhouyuhao
 * 	created: 	2024-07-09 13:58:59
 * 	modified: 	2024-07-09 21:04:35
 * 	item: 		Certified Software Professional
 * 	site: 		914, Harbin
 */
#include <iomanip>
#include <iostream>

using namespace std;

const int maxn = 15, maxs = 1 << maxn;

double trans[maxs][maxn], series[2][maxs];
double *pre = series[0], *ans = series[1];

int main(int argc, char const *argv[]) {

	int n, m;
	cin >> n >> m;
	double prob[n][n] = {0.};
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			cin >> prob[i][j];
			prob[j][i] = 1 - prob[i][j];
		}
	}
	int U = (1 << n) - 1;
	for (int s = 0; s <= U; s++) {
		double sum[n] = {0.};
		for (int i = 0; i < n; i++) {
			if (s >> i & 1) { // your hand
				for (int j = 0; j < n; j++) {
					if (~s >> j & 1) { // ~: opponent's hand
						sum[i] += prob[i][j];
						sum[j] += prob[j][i];
						// i != j & i union j = n
					}
				}
			}
		}
		double tot[2] = {0., 0.};
		for (int i = 0; i < n; i++) {
			tot[s >> i & 1] += sum[i];
		}
		for (int i = 0; i < n; i++) {
			sum[i] /= tot[s >> i & 1];
		}
		for (int i = 0; i < n; i++) {
			if (s >> i & 1) {
				for (int j = 0; j < n; j++) {
					if (~s >> j & 1) {
						trans[s][i] += sum[i] * sum[j] * prob[j][i];
						trans[s][j] += sum[i] * sum[j] * prob[i][j];
						// prob of state lose card = prob of win cards *
						// prob of lose card * prob[win card][lose card]
					}
				}
			}
		}
	}
	pre[0] = ans[0] = 0.;
	pre[U] = ans[U] = 1.;
	for (int s = 1; s <= U; s++) { // initialization
		ans[s] = ans[s & (s - 1)] + 1. / n;
		// s & (s - 1): remove the rightmost 1
	}
	int iter = 500;
	while (iter--) {
		swap(ans, pre);
		for (int s = 1; s < U; s++) {
			ans[s] = 0.;
			for (int i = 0; i < n; i++) {
				ans[s] += trans[s][i] * pre[s ^ (1 << i)];
				// state lose card -> previous state
			}
		}
	}
	for (int i = 0; i < m; i++) {
		int state = 0;
		for (int j = 0; j < n; j++) {
			int x;
			cin >> x;
			state |= x << j;
		}
		cout << fixed << setprecision(5) << ans[state] << "\n";
	}

	return 0;
}