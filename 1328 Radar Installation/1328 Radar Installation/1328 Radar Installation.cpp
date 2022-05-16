#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

struct Point {
	double left;
	double right;
} s[1001];

bool cmp(Point a, Point b) {
	return a.right < b.right;
}

int main()
{
	int i, n, d, x, y, sum;
	int num = 1;
	double l;
	while (cin >> n >> d && n && d)
	{
		sum = 1;
		for (i = 0; i < n; i++) {
			cin >> x >> y;
			if (y > d) {
				sum = -1;
			}
			l = sqrt(pow((float)d, 2) - pow((float)y, 2));
			s[i].left = x - l;
			s[i].right = x + l;
		}
		if (sum == -1) {
			cout << "Case " << num++ << ": " << sum << endl;
			continue;
		}
		sort(s, s + n, cmp);
		double tmp = s[0].right;
		for (i = 1; i < n; i++) {
			if (s[i].left > tmp) {
				sum++;
				tmp = s[i].right;
			}
			else {
				continue;
			}
		}
		cout << "Case " << num++ << ": " << sum << endl;
	}
}


