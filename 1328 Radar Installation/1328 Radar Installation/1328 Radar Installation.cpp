/*题目：POJ 1328
  思路：典型的贪心策略题，以雷达布设范围线段的右端进行从小到大排序。
  得到了一些存储有序的线段，假设已经对最左侧的岛屿进行了监测，雷达布置在
  最左侧岛屿的雷达布设线段的最右端，如果下一座岛屿的雷达布设线段的最左端
  小于等于上一座岛屿的雷达布设线段的最右端，那么他们就出现了重合，
  这时不必再添加新的雷达，即可以把这座岛屿忽略，然后取下一座小岛，
  做为第二座小岛，如此重复，直到遇到下一座岛屿的雷达布设线段的最左端
  大于上一座岛屿的雷达布设线段的最右端，这种情况就说明，需要新安装一台雷达
  遍历所有岛屿得到最小雷达数目
  */

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


