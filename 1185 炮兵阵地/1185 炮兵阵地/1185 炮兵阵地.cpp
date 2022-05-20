#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define me(a) memset(a, 0, sizeof(a))
using namespace std;
int dp[115][70][70], maze[105], status[70], num[70], m, n, len;
char str[111];
int main()
{

    while (~scanf("%d%d", &n, &m))
    {
        me(dp);
        me(num);
        me(maze);
        me(status);
        for (int i = 1; i <= n; i++)  //计算原始地图的状态数
        {
            cin >> str;
            for (int j = 0; j < m; j++)
            {
                if (str[j] == 'H')
                {
                    maze[i] += (1 << j);
                }
            }
        }
        len = 1;
        for (int i = 0; i < (1 << m); i++)//仅当两个炮兵不互相攻击的条件下计算所有状态
        {
            if (!(i & (i << 1)) && !(i & (i << 2)))
            {
                int k = i, sum = 0;
                while (k)  //计算状态i的二进制形式有多少个1，即有多少个炮兵
                {
                    if (k & 1)
                        sum++;
                    k >>= 1;
                }
                num[len] = sum;
                status[len++] = i;//保存合法状态
            }
        }

        for (int i = 1; i < len; i++)
        {
            if (!(maze[1] & status[i]))
            {
                dp[1][i][1] = num[i];
            }
        }
        for (int i = 2; i <= n; i++) //第3行开始DP直到最后
        {
            for (int j = 1; j < len; j++)//枚举第i行状态
            {
                if (status[j] & maze[i]) continue;
                for (int k = 1; k < len; k++)//枚举i-1行状态
                {
                    if (status[j] & status[k]) continue;
                    if (status[k] & maze[i - 1]) continue;
					//第i行和i-1行炮兵互相攻击
                    for (int t = 1; t < len; t++)//枚举i-2行状态
                    {
                        if (status[t] & status[j]) continue;
                        if (status[t] & status[k]) continue;
                        if (status[t] & maze[i - 2]) continue;
                        dp[i][j][k] = max(dp[i][j][k], dp[i - 1][k][t] + num[j]);
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 1; i < len; i++)
            for (int j = 1; j < len; j++) //枚举第n行状态
                ans = max(ans, dp[n][i][j]);
        cout << ans << endl;
    }
    return 0;
}