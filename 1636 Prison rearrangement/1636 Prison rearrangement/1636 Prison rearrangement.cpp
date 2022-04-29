#include<cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m;
int anum, bnum;
int map[210][210], dp[210][210], vis[2][210];

void DFS(int side, int t) {
	vis[side][t] = 1;
	if (!side) {
		anum++;
		for (int i = 1; i <= n; i++) {
			if (map[t][i] && !vis[1][i]) {
				DFS(1, i);
			}
		}
	}
	else {
		bnum++;
		for (int i = 1; i <= n; i++) {
			if (map[i][t] && !vis[0][i]) {
				DFS(0, i);
			}
		}
	}
}

int main()
{
	int t = 0;
	cin >> t;
	while (t--) {
		memset(map, 0, sizeof(map));
		memset(dp, 0, sizeof(dp));
		memset(vis, 0, sizeof(vis));
		cin>> n >> m;
		for (int i = 0; i < m; i++) {
			int x, y;
			cin>> x >> y;
			map[x][y] = 1;
		}
		int a[210], b[210];
		int k = 0;
		for (int i = 1; i <= n; i++) {
			if (vis[0][i]) continue;
			anum = 0;
			bnum = 0;
			DFS(0, i);
			a[k] = anum;
			b[k++] = bnum;
		}
		for (int i = 1; i <= n; i++) {
			if (vis[1][i]) continue;
			anum = 0;
			bnum = 0;
			DFS(1, i);
			a[k] = anum;
			b[k++] = bnum;
		}
		dp[0][0] = 1;
		for (int i = 0; i < k; i++) {
			for (int j = n / 2; j >= a[i]; j--) {
				for (int l = n / 2; l >= b[i]; l--) {
					if (dp[j][l] || dp[j - a[i]][l - b[i]] == 1) {
						dp[j][l] = 1;
					}
				}
			}
		}
		for (int i = n / 2; i >= 0; i--) {
			if (dp[i][i] == 1) {
				cout << i << endl;
				break;
			}
		}
	}
	return 0;
}


