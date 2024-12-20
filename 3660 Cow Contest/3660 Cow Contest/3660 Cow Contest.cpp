﻿/*题目：POJ 3660
  思路：牛相互之间的胜负关系的传递，实际上是一个传递闭包，只需要找出
  胜于牛a的牛的数目m，和负于牛a的牛的数目k,然后判断m + k == n-1?
  是否成立即可知道它的名次是否可以确定。若a胜于b，则在建图时添加一条从
  a->b的有向边，胜于关系转变为可达关系，使用Floyd算法，寻找每一点的可达
  和被可达的关系数目之和即可。
*/


#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#define INF 0x3f3f3f3f

using namespace std;

int N, M;
int A[106][106];

void Floyd() {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				A[i][j] = A[i][j] || (A[i][k] && A[k][j]);
			}
		}
	}
}

int main()
{
	while (scanf("%d%d", &N, &M) == 2) {
		int a, b;
		memset(A, 0, sizeof(A));
		for(int i = 1; i <= M; i++) {
			cin >> a >> b;
			A[a][b] = 1;
		}
		Floyd();
		int result = 0;
		for (int i = 1; i <= N; i++) {
			int sum = 0;
			for (int j = 1; j <= N; j++) {
				if (A[i][j]||A[j][i]) {
					sum++;
				}
			}
			if (sum == N - 1) {
				result++;
			}
		}
		cout<< result << endl;
	}
	return 0;
}

