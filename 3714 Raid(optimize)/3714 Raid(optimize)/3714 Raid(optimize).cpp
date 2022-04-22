#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;


struct Point {
	double x, y;
	int flag;
};

Point p[maxn];
Point q[maxn];

bool cmp_x(const Point& a, const Point& b) {
	return a.x < b.x;
}

bool cmp_y(const Point& a, const Point& b) {
	return a.y < b.y;
}

double dist(const Point& a, const Point& b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double slove(int l, int r) {
	if (l == r) return INF;
	if (l + 1 == r) {
		if (p[l].flag != p[r].flag) return dist(p[l], p[r]);
		return INF;
	}
	int mid = (l + r) >> 1;
	double ans = min(slove(l, mid), slove(mid + 1, r));
	int temp = 0;
	for (int i = l; i <= r; i++) {
		if (fabs(p[i].x - p[mid].y) <= ans) q[++temp] = p[i];
	}
	sort(q + 1, q + temp + 1, cmp_y);
	for(int i=1;i<=temp;i++){
		for (int j = i+1; j <=temp; j++) {
			if (q[j].y - q[i].y >= ans) break;
			if(q[i].flag!=q[j].flag)
			ans = min(ans, dist(q[i], q[j]));
		}
	}
	return ans;
}


int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 1; i <=n; i++) {
			cin >> p[i].x >> p[i].y;
			p[i].flag = 0;
		}
		for (int i = n+1; i <=2*n; i++) {
			cin >> p[i].x >> p[i].y;
			p[i].flag = 1;
		}
		sort(p + 1, p + 1 + 2 * n, cmp_x);
		printf("%.3f\n", slove(1, 2 * n));
	}
	return 0;
}