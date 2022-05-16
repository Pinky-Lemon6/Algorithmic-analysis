#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#define INF 0x3f3f3f3f
using namespace std;
const int maxn = 105;

int N, M;
int graph[maxn][maxn];
int value[maxn], level[maxn];
bool limit[maxn];//标记，哪些点参与某次计算
int dis[maxn];//从开始点到各点的花费
bool S[maxn];//标记，点是否在S集合内

int dijkstra() {
	int result = INF;
	for (int i = 0; i < sizeof(S); i++) {
		S[i] = false;
	}
	for (int i = 1; i <= N; i++) {
		if (i == 1) dis[i] = 0;
		else dis[i] = INF;
	}
	for (int i = 1; i <= N; i++) {
		int k = 0;
		int tmp_dis = INF;
		for (int j = 1; j <= N; j++) {//找到未在S集合中距离最短的点
			if (!S[j] && dis[j] <= tmp_dis && limit[j]) {
				tmp_dis = dis[j];
				k = j;
			}
		}
		S[k] = true;
		for (int j = 1; j <= N; j++) {
			if (limit[j] && dis[j] > dis[k] + graph[k][j]) {//更新每个点到原点的距离
				dis[j] = dis[k] + graph[k][j];
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		dis[i] = dis[i] + value[i]; //在每个路径上添加末尾结点
		if (result > dis[i]) {
			result = dis[i];
		}
	}
	return result;
}

int main()
{
	int result = INF;
	cin >> M >> N;
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			if (i == j) {
				graph[i][j] = 0;
			}
			else {
				graph[i][j] = INF;
			}
		}
	}
	
	for (int i = 1; i <= N; i++) {
		int tmp;
		cin >> value[i]>> level[i]>>tmp;
		for (int j = 1; j <= tmp; j++) {
			int num, val;
			cin >> num >> val;
			graph[i][num] = val;
		}
	}

	for (int i = 0; i <= M; i++) {
		for (int j = 0; j < sizeof(limit); j++) {
			limit[j] = false;
		}
		for (int j = 1; j <= N; j++) {
			if (level[j] <= level[1] + i && level[j] >= level[1] - M + i) {
				limit[j] = true;
			}
		}
		int temp_result = dijkstra();
		if (result > temp_result) {
			result = temp_result;
		}
	}
	cout << result;
}


