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

