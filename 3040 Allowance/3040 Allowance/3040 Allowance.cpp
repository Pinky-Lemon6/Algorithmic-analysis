#include <iostream>
#include <algorithm>
#include <cstring>
#include <functional>
#define INF 0x3f3f3f3f

using namespace std;

typedef pair<int, int> P;

P coin[25];
int use[25];//当前的硬币最多取用的个数
int n, c, sum=0;
void init() {
    for (int i = 0; i < n; i++) {
        cin >> coin[i].first >> coin[i].second;
        if (coin[i].first >= c) {
            sum += coin[i].second;
            coin[i].second = 0;
        }
    }
}
int main()
{
    cin >> n >> c;
    init();
    sort(coin, coin + n, greater<P>());//从大到小排
    while (true) {
        int cost = c;
        int flag = 0;
        memset(use, 0, sizeof(use));
        for (int i = 0; i < n; i++) { //从大到小
            if (coin[i].second) {
                use[i] = min(coin[i].second, cost / coin[i].first);
                cost -= use[i] * coin[i].first;
                if (!cost) {
                    flag = 1;
                    break;
                }
            }
        }
        if (cost > 0) {  //从小到大
            for (int i = n - 1; i >= 0; i--) {
                if (coin[i].second > use[i]) {
                    while (coin[i].second > use[i]) {
                        cost -= coin[i].first;
                        use[i]++;
                        if (cost <= 0) {
                            flag = 1;
                            break;
                        }
                    }
                }
                if (flag) {
                    break;
                }
            }
        }
        if (!flag) break;
        int maxn = INF;
        for (int i = 0; i < n; i++) {
            if (use[i]) maxn = min(coin[i].second / use[i], maxn);
        }
        sum += maxn;
        for (int i = 0; i < n; i++) {
            if (use[i]) coin[i].second -= maxn * use[i];
        }
    }
    cout << sum << endl;
}

