/*题目：POJ 1201
  思路：题目所给意思可以用以下不等式条件表示：
  1、Si >= Si - 1 ，从1 到 i 中选的数必定不会比从1 到 i -1中选的数少。
  2、Si - Si-1 <= 1 =>> Si-1 >= Si - 1, 相邻之间选的数的个数差不会超过1个数。
  3、Sb - Sa-1 >= c =>> Sb >= Sa-1 + c, [a,b] 中至少选c个数
  由于ai，bi从0开始，故使用0作为源点，在建图的时候把a和b都加1，求一遍
  最长路即可，答案保存在dis[50001]。
  */


#include <iostream>
#include <cstring>
#include <algorithm>
#define N 50010
#define M 150010

using namespace std;

int n;
int h[N],q[N],w[M],e[M],ne[M],idx;
int dis[N];
bool st[N];

void add(int a,int b,int c)
{
	e[++idx]=b;
	ne[idx]=h[a];
	h[a]=idx;
	w[idx]=c;
}

void spfa() {
	memset(dis, -0x3f, sizeof(dis));
	int h1 = 0, t1 = 1;
	dis[0] = q[0] = 0;
	st[0]= true;
	while (h1 != t1) {
		int u = q[h1++];
		if (h1 == N) h1 = 0;
		st[u] = false;
		for (int i = h[u]; ~i; i = ne[i]) {
			int v = e[i];
			if (dis[v] < dis[u] + w[i]) {
				dis[v] = dis[u] + w[i];
				if (!st[v]) {
					q[t1++] = v;
					if (t1 == N) t1 = 0;
					st[v] = true;
				}
			}
		}
	}
}
int main()
{
	cin >> n;
	memset(h, -1, sizeof(h));
	for (int i = 1; i <= 50001; i++) {
		add(i - 1, i, 0);
		add(i, i - 1, -1);
	}
	for (int i = 0; i < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a++;
		b++;
		add(a - 1, b, c);
	}
	spfa();
	cout << dis[50001]<<endl;
	return 0;
}



