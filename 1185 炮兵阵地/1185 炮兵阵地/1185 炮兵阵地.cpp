#include <cstdio>
#include <iostream>
#include <cstring>

using  namespace std;

int r, l, nums;
int base[110];
int state[70];
int soilder[70];
int dp[110][70][70];
char g[110][15];

void init() {
    memset(base,0,sizeof(base));
    memset(base, 0, sizeof(state));
    memset(base, 0, sizeof(soilder));
    memset(base, 0, sizeof(dp));
    nums = 0;
}

int main()
{
    init();
    cin >> r >> l;
    for (int i = 0; i < r; i++) {
        cin >> g[i];
        for (int j = 0; j < l; j++) {
            if (g[i][j] == 'H') base[i] += 1 << j;
        }
    }

    for (int i = 0; i < (1 << l); i++) {
        if ((i & i << 1) || (i & i << 2)) continue;
        int k = i;
        while (k) {
            soilder[nums] += k & 1;
            k = k >> 1;
        }
        state[nums++] = i;
    }

    for (int i = 0; i < nums; i++) {
        if (state[i] & base[0]) continue;
        dp[0][i][0] = soilder[i];
    }

    for (int r1 = 1; r1 < r; r1++) {
        for (int i = 0; i < nums; i++) {
            if (state[i] & base[r1]) continue;
            for (int j = 0; j < nums; j++) {
                if (state[j] & base[r1 - 1]) continue;
                if (state[i] & state[j]) continue;
                for (int k = 0; k < nums; k++) {
                    if (state[k] & base[r1 - 2]) continue;
                    if (state[j] & state[k]) continue;
                    if (state[i] & state[k]) continue;
                    dp[r1][i][j] = max(dp[r1][i][j], dp[r1 - 1][j][k] + soilder[i]);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < nums; i++) {
        for (int j = 0; j < nums; j++) {
            ans = max(ans, dp[r - 1][i][j]);
        }

    }
    cout << ans << endl;
    return 0;
}

