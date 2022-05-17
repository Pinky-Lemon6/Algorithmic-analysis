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



