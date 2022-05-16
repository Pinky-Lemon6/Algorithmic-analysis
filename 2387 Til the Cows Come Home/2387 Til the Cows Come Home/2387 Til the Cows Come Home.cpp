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
		int minw = INF;
		int minv;
		for (int i = 1; i <= N; i++) {
			if(!vis[i] && dis[i] < minw) {
				minw = dis[i];
				minv = i;
			}
		}
		vis[minv] = 1;
		for (int i = 1; i <= N; i++) {
			if (vis[i] == 1) continue;
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
