#include <cstdio>
#include <iostream>

using namespace std;

int direction[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
int n, m;
int high[110][110];
int max_l[110][110];

int judge(int x, int y) {
    if (x >= 0 && y >= 0 && x <= n-1 && y <= n-1) {
        return 1;
    }
    else return 0;
}

int DFS(int x, int y) {
    if (max_l[x][y] != 0) {  //该点已经搜索过或为边界
        return max_l[x][y];
    }
    max_l[x][y] = 1;
    for (int i = 0; i <= 4; i++) {  //上下左右分别搜索
        int a = x + direction[i][0];
        int b = y + direction[i][1];
        if (judge(a, b) && high[a][b] < high[x][y]) {  //可以下滑
            max_l[x][y] = max(DFS(a, b) + 1, max_l[x][y]);
        }
    }
    return max_l[x][y];
}
int main()
{
    cin >> n >> m;
    int ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> high[i][j];
            max_l[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans = max(ans, DFS(i, j));
        }
    }
    cout << ans << endl;
    return 0;
}


