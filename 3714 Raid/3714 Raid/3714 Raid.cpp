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

bool cmp_x(const Point &a, const Point &b) {
	return a.x < b.x;
}

bool cmp_y(const Point &a, const Point &b) {
	return a.y < b.y;
}

double dist(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double slove(int l,int r) {
	if (l == r) return 0;
	if (l + 1 == r) return dist(p[l], p[r]);
	int mid = (l + r) >> 1;
	double ans = 0;
	for (int i = l; i < mid; ++i) {
		for (int j = mid; j < r; ++j) {
			ans = max(ans, dist(p[i], p[j]));
		}
	}
	return max(ans, max(slove(l, mid), slove(mid, r)));
}


int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin>> n;
		for (int i = 0; i < n; i++) {
			cin >> p[i].x >> p[i].y;
			p[i].flag = 0;
		}
		for (int i = 0; i < n; i++) {
			cin >> q[i].x >> q[i].y;
			q[i].flag = 1;
		}
		printf("%.3f\n", slove(1,2*n));
	}
	return 0;
}