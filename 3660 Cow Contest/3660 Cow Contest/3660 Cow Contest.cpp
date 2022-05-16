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

