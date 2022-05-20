/*题目：POJ 1077
  思路：使用A*算法来对此题进行求解，但是对于这个题目来说，由于使用
  深度优先搜索寻找最佳方案的时间开销较大，故可以采用IDA*算法。
  将初始的曼哈顿距离作为假定最优解，从假定最优解开始算起，若搜索不出
  来结果，则对假定最优解进行加一并重新搜索，直到搜索到与当前假定
  最优解相同的结果。同时在搜索的过程中根据估值函数：当前的曼哈顿距离
  +已经走过的深度<=当前的假定最优解，对搜索过程进行剪枝操作，减少开销。
  */



#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

int Map[4][4];
int max1, min1, start_x, start_y;
bool flag;
int d[4][2] = { -1, 0, 0, 1, 0, -1, 1 ,0 };
int path[10005];
int goal[10], start[10];

int Haman_dis() {
	int sum = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!Map[i][j]) continue;
			else sum += abs((Map[i][j] - 1) / 3 - i) + abs((Map[i][j] - 1) % 3 - j);
		}
	}
	return sum;
}

void start_xyz() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!Map[i][j]) {
				start_x = i;
				start_y = j;
				return;
			}
		}
	}
}

void swap(int *a,int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void dfs(int x, int y, int s, int last_step) {
	if (flag) return;
	if (s == max1) {
		int l = Haman_dis();
		if (!l) {
			min1 = s;
			flag = true;
		}
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (last_step + i == 3 && s > 0) continue;
		int dx = x + d[i][0];
		int dy = y + d[i][1];
		if (dx < 0 || dy < 0 || dx >= 3 || dy >= 3) continue;
		swap(&Map[dx][dy], &Map[x][y]);
		if (Haman_dis() + s <= max1 && !flag) {
			path[s] = i;
			dfs(dx, dy, s + 1, i);
			if (flag) return;
		}
		swap(&Map[dx][dy], &Map[x][y]);
	}
}

int check() {
	int num1 = 0, num2;
	for (int i = 0; i < 8; i++) {
		for (int j = i + 1; j < 8; j++) {
			if (start[j] < start[i]) num1++;
		}
	}
	if (num1 % 2) return 0;
	else return 1;
}
int main()
{
	char str[10];
	char dis[4] = { 'u','r','l','d' };
	cin >> str;
	int k = 0, sum = -1;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == ' ') continue;
		sum++;
		if (str[i] == 'x') {
			Map[sum / 3][sum % 3] = 0;
		}
		if (str[i] >= '1' && str[i] <= '8') {
			Map[sum / 3][sum % 3] = start[k++] = str[i] - '0';
		}
	}
	start_xyz();
	int ans = check();
	if (!ans) {
		cout << "unsolvable" << endl;
		return 0;
	}
	max1 = Haman_dis();
	if (!max1) {
		cout << endl;
		return 0;
	}
	flag = false;
	while (!flag) {
		dfs(start_x, start_y, 0, 0);
		if (!flag) max1++;
	}
	for (int i = 0; i < min1; i++) {
		cout << dis[path[i]];
	}
	cout << endl;
	return 0;
}

