#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;
int n;
int a[110][110];
int dp[110][110][110];

int main()
{
	while (~scanf_s("%d", &n)) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf_s("%d", &a[i][j]);
			}
		}
		memset(dp, 0, sizeof(dp));
		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				for (int k = 0; k < n; k++) {
					int t = 0;
					for (int l = i; l <=j; l++) {
						t += a[k][l];
					}
					if (dp[i][j][k-1] >= 0) {
						dp[i][j][k] = dp[i][j][k - 1] + t;
					}
					else {
						dp[i][j][k] = t;
					}
					ans = max(ans, dp[i][j][k]);
				}
			}
		}

		printf("%d\n", ans);
	}
	return 0;
}

