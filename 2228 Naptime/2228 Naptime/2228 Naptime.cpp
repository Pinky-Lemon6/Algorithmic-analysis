/*题目：POJ 2228
  思路：由于要考虑跨越一天的情况，故可为环形DP问题。
  令dp[i][j][k]代表前i个时间片，睡了j个时间片得到的最大值，而第i个时间片
  能否起作用取决于第i-1个时间片是否选择，故状态转移方程：
 不选第i个时间片: 
  前一个时间片没选：dp[i][j][0] = max(dp[i-1][j][0] + 0, dp[i][j][0]); 
  前一个时间片选了：dp[i][j][0] = max(dp[i-1][j][1] + 0, dp[i][j][0]);
 选第i个时间片
  前一个时间片没选：dp[i][j][1] = max(dp[i-1][j - 1][0] + 0, dp[i][j][1]);
  前一个时间片选了：dp[i][j][1] = max(dp[i-1][j - 1][1] + util[i], dp[i][j][1]);
  重点是把环形DP转变成两个线性DP，当时间片1睡着时，下一次DP时把时间片n和1设置成
 同一个状态，这样就可以让时间片1和时间片n同时睡着，更新答案的时候只更dp[n&1][b][1]。
  */


#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 4e3;
const int INF = 0x3f3f3f3f;
int n, b;
int dp[2][N][2], u[N];

int main()
{
    cin >> n >> b;

    for (int i = 1; i <= n; ++i) {
        cin >> u[i];
    }
    memset(dp, -INF, sizeof(dp));
    dp[0][0][0] = dp[1][1][1] = dp[1][0][0] = 0;
    for (int i = 2; i <= n; ++i) {
        int k = i & 1;
        for (int j = 1; j <= i; ++j) {
            dp[k][j][0] = max(dp[k ^ 1][j][0], dp[k ^ 1][j][1]);
            dp[k][j][1] = max(dp[k ^ 1][j - 1][0], dp[k ^ 1][j - 1][1] + u[i]);
        }
    }
    int ans = 0;
    ans = max(dp[n & 1][b][0], dp[n & 1][b][1]);
    memset(dp, -INF, sizeof(dp));
    dp[1][1][1] = u[1];
    dp[0][0][0] = dp[1][0][0] = 0;
    for (int i = 2; i <= n; ++i) {
        int k = i & 1;
        for (int j = 1; j <= i; ++j) {
            dp[k][j][0] = max(dp[k ^ 1][j][0], dp[k ^ 1][j][1]);
            dp[k][j][1] = max(dp[k ^ 1][j - 1][0], dp[k ^ 1][j - 1][1] + u[i]);
        }
    }
    ans = max(ans, dp[n & 1][b][1]);
    cout << ans << endl;
    return 0;
}

