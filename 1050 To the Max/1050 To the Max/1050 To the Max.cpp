/*题目：POJ 1050
  思路：可以将二维的矩阵转变为一维的形式，即dp[i][j][k]表示从di行开始到第j
  行，以第k列为结束的矩阵的最大数字和，则可以将二维矩阵中所有子矩阵的最大数
  字和都保存在dp中，然后再在dp中按照一维问题的形式找出最大值即可*/


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
					if (dp[i][j][k-1] >= 0) {  //将二维转变为一维
						dp[i][j][k] = dp[i][j][k - 1] + t;
					}
					else {
						dp[i][j][k] = t;
					}
					ans = max(ans, dp[i][j][k]);  //寻找最大值
				}
			}
		}

		printf("%d\n", ans);
	}
	return 0;
}

