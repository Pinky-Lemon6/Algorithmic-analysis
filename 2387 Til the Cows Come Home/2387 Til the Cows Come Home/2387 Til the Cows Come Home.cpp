/*题目：POJ 2387
  思路：使用Dijkstra算法，把所有的顶点分成P和Q两个集合，P为已知最短路
  的集合，Q为未知最短路的集合，用vis数组进行区分，vis[i]为1则是P;用
  dis数组记录从s到i的最短路，每次从P中找最小的一个点来松弛其他所有点;
  更新dis数组，都松弛后即可得出结果。
*/



#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#define INF 0x3F3F3F3F

using namespace std;

int map[1015][1015];
int dis[1010], vis[1010];
int N, M;

void init() {
	memset(map, INF, sizeof(map));
	memset(dis, INF, sizeof(dis));
	memset(vis, 0, sizeof(vis));
}

void Dijkstra(int sre, int det) {
	dis[sre] = 0;
	for (int k = 1; k <= N; k++) {
		int minw = INF; //松弛边的长度
		int minv;  //松弛的点
		for (int i = 1; i <= N; i++) {
			if(!vis[i] && dis[i] < minw) { //找到最小的松弛点
				minw = dis[i];
				minv = i;
			}
		}
		vis[minv] = 1;
		for (int i = 1; i <= N; i++) {
			if (vis[i] == 1) continue;  //如果是P集合，则不用更新
			dis[i] = min(dis[i], dis[minv] + map[minv][i]);
		}
	}
	cout << dis[det] << endl;
}

int main()
{
	cin >> M >> N;
	init();
	int a, b, w;
	for (int i = 1; i <= M; i++) {
		cin >> a >> b >> w;
		if (w < map[a][b]) {
			map[a][b] = w;
			map[b][a] = w;
		}
	}
	Dijkstra(1, N);
	return 0;
}
