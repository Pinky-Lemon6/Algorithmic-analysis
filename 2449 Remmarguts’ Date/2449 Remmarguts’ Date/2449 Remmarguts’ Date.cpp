/*题目：POJ 2449
  思路：A*算法，估值函数为某一点到t的最短路长度，最短路可以通过建反图
  获得t到各点的最短路，即各点到t的最短路。若s到t的距离为∞，则不用继续
  直接输出-1，若s=t，则k++即可（自己到自己的路不是第一短的路）。
  */



#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#define INF 0x3F3F3F3F
#define MAXN 100005
#define LL long long

using namespace std;

int tot, head[MAXN], rhead[MAXN], x, y, z, cnt[MAXN], dis[MAXN];
bool vis[MAXN];

struct Edge
{
    int to, next, w;
}edge[MAXN],redge[MAXN];

void add_edge(int u,int v,int w)
{
	edge[tot].to = v;
	edge[tot].next = head[u];
	edge[tot].w = w;
	head[u] = tot;
	redge[tot].to = u;
	redge[tot].next = rhead[v];
	redge[tot].w = w;
	rhead[v] = tot++;
}

struct Node {
	int x, dis;
	friend bool operator < (const Node &a, const Node &b) {
		return a.dis > b.dis;
	}
};

priority_queue<Node>q;
queue<int>que;

bool spfa(int s, int n) {
	memset(vis, false, sizeof(vis));
	for (int i = 1; i <= n; i++) dis[i] = INF;
	vis[s] = true;
	dis[s] = 0;
	while (!que.empty()) que.pop();
	que.push(s);
	memset(cnt, 0, sizeof(cnt));
	cnt[s] = 1;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		vis[u] = false;
		for (int i = rhead[u]; i != -1; i = redge[i].next) {
			int v = redge[i].to;
			if (dis[v] > dis[u] + redge[i].w) {
				dis[v] = dis[u] + redge[i].w;
				if (!vis[v]) {
					vis[v] = true;
					que.push(v);
					if (++cnt[v] > n) return false;
				}
			}
		}
	}
	return true;
}
int main()
{
	int n, m, s, t, k;
	while (~scanf("%d%d", &n, &m)) {
		tot = 0;
		memset(head, -1, sizeof(head));
		memset(rhead, -1, sizeof(rhead));
		while (m--) {
			cin >> x >> y >> z;
			add_edge(x, y, z);
		}
		cin >> s >> t >> k;
		spfa(t, n);
		if (dis[s] == INF) {
			cout << "-1" << endl;
			continue;
		}
		while (!q.empty()) q.pop();
		Node N1;
		N1.x = s;
		N1.dis = dis[s];
		q.push(N1);
		int ans = -1, num = 0;
		if (s == t) k++;
		while (!q.empty()) { 
			Node temp = q.top();
			Node p1;
			q.pop();
			if (temp.x == t) {
				num++;
				if (num == k) {
					ans = temp.dis;
					break;
				}
			}
			for (int i = head[temp.x]; i != -1; i = edge[i].next) {
				int v = edge[i].to;
				p1.x = v;
				p1.dis = temp.dis - dis[temp.x] + dis[v] + edge[i].w;
				q.push(p1);
			}
		}
		cout << ans << endl;
	}
	return 0;
}

